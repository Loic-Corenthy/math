#!/usr/bin/env bash

set -euo pipefail

# 1. Get the commit hash from argument, default to HEAD
COMMIT="${1:-HEAD}"

# TODO Add a comment about this script expecting BUILD_DIR as environment variable argument

if [ ! -d "$BUILD_DIR/.cmake/api/v1/reply" ]; then
    echo "Error: CMake File API reply directory not found." >&2
    echo "Please ensure you created the codemodel-v2 query and ran CMake configuration." >&2
    exit 1
fi

# 2. Get list of modified files relative to repo root
# Filters for Added, Copied, Modified, and Renamed files
mapfile -t MODIFIED_FILES < <(git diff-tree --no-commit-id --name-only -r "$COMMIT" --diff-filter=ACMR)

if [ ${#MODIFIED_FILES[@]} -eq 0 ]; then
    echo "No files modified in this commit."
    exit 0
fi

# 3. Find the latest codemodel JSON reply file
CODEMODEL_JSON=$(ls -t $BUILD_DIR/.cmake/api/v1/reply/codemodel-v2-*.json | head -n 1)

# 4. Extract target JSON references from the codemodel
# Remove directoryIndex = 0 because we use FetchContent_Declare from the root directory and we don't want to take these targets into account
TARGET_JSONS=$(jq -r '.configurations[0] | (.targets[], .abstractTargets[]?) | select(.directoryIndex != 0) | .jsonFile' "$CODEMODEL_JSON")

# 5. Map files to targets
CHANGED_TARGETS=$(
for target_json in $TARGET_JSONS; do

    TARGET_PATH="$BUILD_DIR/.cmake/api/v1/reply/$target_json"

    # Extract target name
    TARGET_NAME=$(jq -r '.name' "$TARGET_PATH")

    # Extract all source files for this target
    # CMake paths are often relative to the target's source directory,
    # so we resolve them relative to the repository root.
    SRC_DIR=$(jq -r '.paths.source' "$TARGET_PATH")

    # Adjust dot prefix if source is at root
    if [ "$SRC_DIR" = "." ]; then SRC_DIR=""; else SRC_DIR="$SRC_DIR/"; fi

    # Check if any modified file matches the target's sources
    for file in "${MODIFIED_FILES[@]}"; do

        # Check if the file is listed in the target's sources array
        # MATCH=$(jq --arg f "$file" --arg prefix "$SRC_DIR" '.sources[]?, .interfaceSources[]? | select(($prefix + .path) == $f)' "$TARGET_PATH" 2>/dev/null)
        MATCH=$(jq --arg f "$file" --arg prefix "$SRC_DIR" '.sources[]?, .interfaceSources[]? | select(.path == $f)' "$TARGET_PATH" 2>/dev/null)

        #echo "Match is ${MATCH} for target ${TARGET_NAME}"


        if [[ -n "$MATCH" ]]; then
            echo "${TARGET_NAME}"
            break
        fi
    done
done)

# Deduplicate and print the results
if [ -n "$CHANGED_TARGETS" ]; then
    CHANGED_TARGETS=$(sort -u <<< "${CHANGED_TARGETS}")
fi


FINAL_RESULT=${CHANGED_TARGETS}

for changed_target in ${CHANGED_TARGETS}; do
    for target in ${TARGET_JSONS}; do
        TARGET_PATH="$BUILD_DIR/.cmake/api/v1/reply/$target"

        # Extract target name
        TARGET_NAME=$(jq -r '.name' "$TARGET_PATH")

        # Extract all source files for this target
        # CMake paths are often relative to the target's source directory,
        # so we resolve them relative to the repository root.
        SRC_DIR=$(jq -r '.paths.source' "$TARGET_PATH")

        # Adjust dot prefix if source is at root
        if [ "$SRC_DIR" = "." ]; then SRC_DIR=""; else SRC_DIR="$SRC_DIR/"; fi


        FINAL_MATCH=$(jq --arg ct ${changed_target} --arg prefix "$SRC_DIR" '.linkLibraries[]? | select(.id? | contains("lcnsAlgebra")) | .id' "$TARGET_PATH")

        if [[ -n "${FINAL_MATCH}" ]]; then
            FINAL_RESULT+=$(jq -r '.name' ${TARGET_PATH})
            FINAL_RESULT+=$'\n'
        fi
    done
done

PREFIX="test"
FILTERED_TESTS=$(grep "^$PREFIX" <<< "$FINAL_RESULT")

echo "${FILTERED_TESTS}"

