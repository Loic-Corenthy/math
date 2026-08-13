from pathlib import Path

import ColorFormatter

file_path = Path("example.txt")

# Check if the path exists AND is a file (not a directory)
if file_path.is_file():
    print("File exists!")
else:
    print("File does not exist.")


def ModifiedFiles(build_dir : str):
    # Setup logger and handler

    logger = logging.getLogger("MyLogger")
    logger.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stderr)
    handler.setFormatter(ColorFormatter())
    logger.addHandler(handler)



    # Check if the reply file from cmake exists
    Path(f"{build_dir}/.cmake/api/v1/reply")

    if not Path.is_file():
        print("reply file not found!")
        return 1


    # Test outputs
    logger.debug("This is a debug message.")
    logger.info("This is an info message.")
    logger.warning("This is a warning message.")
    logger.error("This is an error message.")
    logger.critical("This is a critical error message!")



