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

    # Check if the reply file from cmake exists
    path = root_dir / ".cmake/api/v1/reply"

    logger.debug(f"Path to reply is: {path}")

    if not path.is_dir():
        logger.error("cmake's \"reply\" directory not found")
        return 1

    # Get the list of modified files
    # Filters for Added, Copied, Modified, and Renamed files
    modified_files = RunRequest("git diff-tree --no-commit-id --name-only -r --diff-filter=ACMR HEAD")

    if len(modified_files) == 0:
        logger.warning("No files modified in this pull request. Nothing to do")
        return
    else:
        logger.info(f"Modified files for this pull request: {modified_files}")


    # 3. Find the latest codemodel JSON reply file
    path_to_codemodel = root_dir / ".cmake/api/v1/reply/"
    codemodel_json = [str(p) for p in path_to_codemodel.rglob("codemodel-v2-*.json") if p.is_file()]

    # logger.info(f"Da result is {codemodel_json[0]}")

    # Get all matching elements as a list

    logger.debug("=======================================================================")
    logger.debug("=======================================================================")
    logger.debug(codemodel_json[0])
    logger.debug("=======================================================================")
    logger.debug("=======================================================================")

    with open(codemodel_json[0], "r") as f:
        data = json.load(f)

    # results = jq.all('.configurations[0] | (.targets[],.abstractTargets[]?) | select(.directoryIndex!=0) | .jsonFile', codemodel_json[0])
    results = jq.all('.[]', data)
    print(results)
    # Output: [{'name': 'production-db', 'type': 'database'}, {'name': 'production-web', 'type': 'server'}]

    # Get only the first matching element
    # first_match = jq.first('.[] | select(.type == "server")', data)
    # print(first_match)
    # Output: {'name': 'staging-web', 'type': 'server'}



    # 4. Extract target JSON references from the codemodel
    # Remove directoryIndex = 0 because we use FetchContent_Declare from the root directory and we don't want to take these targets into account
    # targets_request = f"jq -r '.configurations[0] | (.targets[],.abstractTargets[]?) | select(.directoryIndex!=0) | .jsonFile' {codemodel_json[0]}"
    # target_json = RunRequest(targets_request)
    #
    # logger.debug(f"The json targets are {target_json}")

    # Test outputs
    # logger.debug("This is a debug message.")
    # logger.info("This is an info message.")
    # logger.warning("This is a warning message.")
    # logger.error("This is an error message.")
    # logger.critical("This is a critical error message!")


ModifiedFiles(sys.argv[1])
