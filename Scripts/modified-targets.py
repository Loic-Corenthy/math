import jq
import json
import logging
import re
import subprocess
import sys
from pathlib import Path

import ColorFormatter

def RunRequest(request : str ) -> list(str): 
    """Helper function to run a command in the cli"""
    elements = request.split(" ")
    result = subprocess.run(elements, capture_output=True, text=True, check=True)

    return result.stdout.splitlines()


def GetJSONFileContent(path : Path):
    """Helper function to get the content of a json file"""
    with open(path, "r") as file:
        data = json.load(file)

    return data


def GetModifiedFiles(base : str, target : str) -> list(str):
    """Get the list of modified files in the commits between base and target

    This essentially emulates the following cli command:
    git rev-list main..HEAD | xargs -n 1 git diff-tree --no-commit-id --name-only -r --diff-filter=ACMR | sort -u

    (Filters for Added, Copied, Modified, and Renamed files)
    """
    commit_list = RunRequest(f"git rev-list {base}..{target}")

    result = set()
    for commit in commit_list:
        files_per_commit = RunRequest(f"git diff-tree --no-commit-id --name-only -r --diff-filter=ACMR {commit}")
        for file in files_per_commit:
            if file.endswith((".hpp", ".h", ".cpp", ".c")):
                result.add(file)

    return list(result)


def CreateLogger():
    """Setup logger for messages"""
    logger = logging.getLogger("MyLogger")
    logger.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(ColorFormatter.ColorFormatter())
    logger.addHandler(handler)

    return logger


def ModifiedFiles(build_dir : str, base : str, target : str) -> list(str):
    """Get a list of targets corresponding to the files edited in the mentioned commits"""
    logger = CreateLogger()

    # Keep a variable of the root directory for all the requests in this function
    root_dir = Path(build_dir)

    # 1. Check if the reply file from cmake exists
    path_reply_dir = root_dir / ".cmake/api/v1/reply"

    if not path_reply_dir.is_dir():
        logger.error("cmake's \"reply\" directory not found")
        return 1

    # 2. Get the list of modified files
    modified_files = GetModifiedFiles(base, target)

    if len(modified_files) == 0:
        logger.warning("No files modified in this pull request. Nothing to do")
        return
    else:
        logger.info(f"Modified files for this pull request: {modified_files}")

    # 3. Find the latest codemodel JSON reply file
    codemodel_json = [str(p) for p in path_reply_dir.rglob("codemodel-v2-*.json") if p.is_file()]

    # 4. Extract target JSON references from the codemodel
    data = GetJSONFileContent(codemodel_json[0])
    # Remove directoryIndex = 0 because we use FetchContent_Declare from the root directory and we don't want to take these targets into account
    target_json = jq.all('.configurations[0] | (.targets[], .abstractTargets[]?) | select(.directoryIndex != 0) | .jsonFile', data)

    # 5. Map files to targets
    edited_targets = []

    for target in target_json:
        # Get the full path of the json file for a target
        target_path = path_reply_dir / target

        target_data = GetJSONFileContent(target_path)

        target_name = jq.all('.name', target_data)

        # Extract all source files for this target
        source_dir = jq.all('.paths.source', target_data)

        # Adjust dot prefix if source is at root
        if source_dir[0] == ".":
            source_dir[0] = ""
        else:
            source_dir[0] += "/"

        for file in modified_files:
            request = jq.compile('.sources[]?, .interfaceSources[]? | select(.path == $f)', args={"f": file})

            match = request.input_value(target_data).all()

            if match:
                logger.info(f"This target was modified: {target_name}")
                edited_targets += target_name

    return edited_targets


def FilterTargets(targets : list(str)) -> list(str):
    valid = ["test*"]


    # strings = ["apple123", "banana_456", "cherry", "date", "elderberry"]
    # patterns = [r"^a", r"\d+"]  # Starts with 'a' OR contains digits

    # Combine into a single pattern: (?:^a)|(?:\d+)
    combined_regex = re.compile("|".join(f"(?:{p})" for p in valid))

    filtered_targets = [t for t in targets if combined_regex.search(t)]

    return set(filtered_targets)


def main() -> None:
    if len(sys.argv) < 4:
        logger = CreateLogger()

        logger.error("modified-targets must be called with 3 arguments, e.g. \"python modified-targets.py build/linux_release main HEAD\"")
        return

    target_candiates = ModifiedFiles(sys.argv[1], sys.argv[2], sys.argv[3])
    targets_to_test = FilterTargets(target_candiates)
    print(targets_to_test)


if __name__ == "__main__":
    main()

