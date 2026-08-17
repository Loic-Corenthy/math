import logging
import subprocess
import sys
from pathlib import Path

import ColorFormatter

file_path = Path("example.txt")


def ModifiedFiles(build_dir : str):
    # Setup logger and handler

    logger = logging.getLogger("MyLogger")
    logger.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(ColorFormatter.ColorFormatter())
    logger.addHandler(handler)

    # Check if the reply file from cmake exists
    path = Path(f"{build_dir}/.cmake/api/v1/reply")

    if not path.is_dir():
        logger.error("cmake's \"reply\" directory not found")
        return 1

    modified_files = subprocess.run(["git", "diff-tree", "--no-commit-id", "--name-only", "-r", "--diff-filter=ACMR",  "HEAD"], capture_output=True, text=True, check=True)

    logger.info(f"The list of modified files is:\n{modified_files.stdout}")
    # Test outputs
    # logger.debug("This is a debug message.")
    # logger.info("This is an info message.")
    # logger.warning("This is a warning message.")
    # logger.error("This is an error message.")
    # logger.critical("This is a critical error message!")


ModifiedFiles(sys.argv[1])
