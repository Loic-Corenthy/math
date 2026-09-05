import jq
import json
import logging
import subprocess
import sys
from pathlib import Path

import ColorFormatter

def RunRequest(request : str ):
    elements = request.split(" ")
    result = subprocess.run(elements, capture_output=True, text=True, check=True)

    return result.stdout.splitlines()

def ModifiedFiles(build_dir : str):
    # Setup logger and handler

    logger = logging.getLogger("MyLogger")
    logger.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(ColorFormatter.ColorFormatter())
    logger.addHandler(handler)

    # Keep a variable of the root directory for all the requests in this function
    root_dir = Path(build_dir)

    # 1. Check if the reply file from cmake exists
    path_reply_dir = root_dir / ".cmake/api/v1/reply"

    logger.debug(f"Path to reply is: {path_reply_dir}")

    if not path_reply_dir.is_dir():
        logger.error("cmake's \"reply\" directory not found")
        return 1

    # 2. Get the list of modified files
    # Filters for Added, Copied, Modified, and Renamed files
    modified_files = RunRequest("git diff-tree --no-commit-id --name-only -r --diff-filter=ACMR HEAD")

    if len(modified_files) == 0:
        logger.warning("No files modified in this pull request. Nothing to do")
        return
    else:
        logger.info(f"Modified files for this pull request: {modified_files}")


    # 3. Find the latest codemodel JSON reply file
    codemodel_json = [str(p) for p in path_reply_dir.rglob("codemodel-v2-*.json") if p.is_file()]

    logger.info(f"Local codemodel_json file is {codemodel_json[0]}")

    # 4. Extract target JSON references from the codemodel
    # Remove directoryIndex = 0 because we use FetchContent_Declare from the root directory and we don't want to take these targets into account

    with open(codemodel_json[0], "r") as f:
        data = json.load(f)

    target_json = jq.all('.configurations[0] | (.targets[], .abstractTargets[]?) | select(.directoryIndex != 0) | .jsonFile', data)


    # 5. Map files to targets
    for target in target_json:
        logger.info(f"Now processing target {target}")

        target_path = path_reply_dir / target

        with open(target_path, "r") as target_file:
            target_data = json.load(target_file)

            target_name = jq.all('.name', target_data)

            logger.warning(f"The target name is {target_name[0]}")


    # Test outputs
    # logger.debug("This is a debug message.")
    # logger.info("This is an info message.")
    # logger.warning("This is a warning message.")
    # logger.error("This is an error message.")
    # logger.critical("This is a critical error message!")


ModifiedFiles(sys.argv[1])
