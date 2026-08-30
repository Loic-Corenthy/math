import logging
import subprocess
import sys
from pathlib import Path

import ColorFormatter

file_path = Path("example.txt")

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


    root_dir = Path(build_dir)

    # Check if the reply file from cmake exists
    path = root_dir / ".cmake/api/v1/reply"


    logger.debug(f"Path to reply is: {path}")


    if not path.is_dir():
        logger.error("cmake's \"reply\" directory not found")
        return 1

    modified_files = RunRequest("git diff-tree --no-commit-id --name-only -r --diff-filter=ACMR HEAD")

    if len(modified_files) == 0:
        logger.warning("No files modified in this pull request. Nothing to do")
        return
    else:
        logger.info(f"Modified files for this pull request: {modified_files}")

    path_to_codemodel = root_dir / ".cmake/api/v1/reply/"

    codemodel_json = [str(p) for p in path_to_codemodel.rglob("codemodel-v2-*.json") if p.is_file()]

    # logger.info(f"Da result is {codemodel_json[0]}")





    # Test outputs
    # logger.debug("This is a debug message.")
    # logger.info("This is an info message.")
    # logger.warning("This is a warning message.")
    # logger.error("This is an error message.")
    # logger.critical("This is a critical error message!")


ModifiedFiles(sys.argv[1])
