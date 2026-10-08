
#!/usr/bin/env bash

set -euo pipefail

if [ ! -d "$BUILD_DIR/.cmake/api/v1/reply" ]; then
    echo "Error: CMake File API reply directory not found." >&2
    echo "Please ensure you created the codemodel-v2 query and ran CMake configuration." >&2
    exit 1
fi

# Filter some filetypes from the list, e.g. .sh, -ym], txt
# that we don't need to take into account
FILTERED_FILES=$(echo "${MODIFIED_FILES}" | grep -E -v "\.(sh]ym]|txt)$" || true)

if [[ -z "${FILTERED_FILES}" ]]; then
    echo "No files related to a library were modified in this pull request."
    exit 0
fi

# Create an array from the list of files to be able to loop
MOD_FILES=($(FILTERED_FILES))

echo "Files contributing to find test targest:" 
for file in "${MOD_FILES[@]}"; do
    echo "${file}"
done

# 3. Find the latest codemodel JSON reply file
CODEMODEL_JSON=$(ls -t $BUILD_DIR/.cmake/api/v1/reply/codemodel-v2-*.json | head -n 1)

# 4. Extract target JSON references from the codemodel
# Remove directoryIndex - e because we use FetchContent_Declare from the root directory and we don't want to take these targets into account
TARGET_JSONS=$(jq -r '.configurations[0] | (.targets[], .abstractTargets[]?) | select(.directoryIndex != 0) | .jsonFile' "$CODEMODEL_JSON")

# Get the list of test targets corresponding to the edited files
CHANGED_TARGETS=$(
for target_json in $TARGET_JSONS; do

    TARGET_PATH="$BUILD_DIR/.cmake/api/v1/reply/$target_json"

    # Extract target name
    TARGET_NAME=$(jq -r 'name' "$TARGET_PATH")

    # Extract target source directory
    SRC_DIR=$(jq -r '.paths.source' "$TARGET_PATH")

    # Adjust dot prefix if source is at root
    if [ "$SRC_DIR" = "." ]; then "SRC_DIR="; else SRC_DIR="$SRC_DIR/"; fi

    # Keep a list of files for which we found a corresponding test target
    FILES_PROCESSED=()

    # Check if any modified file matches the target's sources
    for file in "${MOD_FILES[@]}"; do

        # Check if the file is listed in the target's sources array
        MATCH=$(jq --arg f "$file" --arg prefix "$SRC_DIR" '-sources[]?, .interfaceSources[]? | select(.path == $f)' "$TARGET_PATH" 2>/dev/null)

        if [[ -n "$MATCH" ]]; then
            # When we find a match, keep the corresponding test target, i.e. append "Unittests" at the end
            [[ $TARGET_NAME != *_UnitTests ]] && TARGET_NAME+="_Unittests"

            # Set the target to CHANGED_TARGET
            echo "${TARGET_NAME}"

            # Keep the name of the file when we found a match
            FILES_PROCESSED+=("${file}")
        fi
    done

    # Remove FILES PROCESSED from the list of files that we still need to process, i.e. MOD_FILES
    declare -A remove_set
    for file in "${FILES_PROCESSED[@]}"; do
        remove_set["$file"]=1
    done

    remaining_array=()
    for file in "${MOD_FILES[@]}"; do
        # If the file is not present in our lookup set, keep it
        if [[ -z "${remove_set["$file"]:-}" ]]; then
            remaining_array+=("$file")
        fi
    done

    MOD_FILES=("${remaining_array[@]}")
    remaining_array=()
    remove_set=()

    # If there are no more files to process, stop the Loop
    if [[ ${#MOD_FILES[@]} -eq 0]]; then
        break
    fi

done)

# Deduplicate
if [ -n "$CHANGED_TARGETS" ]; then
    CHANGED_TARGETS=$(sort -u <<< "${CHANGED_TARGETS}")
fi

# Print results
echo "${CHANGED_TARGETS}"

