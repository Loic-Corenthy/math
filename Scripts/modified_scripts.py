import logging
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

    if not path.is_file():
        logger.error("cmake \"reply\" file not found")
        return 1

    # Test outputs
    # logger.debug("This is a debug message.")
    # logger.info("This is an info message.")
    # logger.warning("This is a warning message.")
    # logger.error("This is an error message.")
    # logger.critical("This is a critical error message!")


ModifiedFiles(sys.argv[1])
