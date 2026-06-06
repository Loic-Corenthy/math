import logging


class ColorFormatter(logging.Formatter):
    def __init__(self):
        # ANSI escape sequences for colors
        self.GREY = "\x1b[38;20m"
        self.GREEN = "\x1b[32;20m"
        self.YELLOW = "\x1b[33;20m"
        self.RED = "\x1b[31;20m"
        self.BOLD_RED = "\x1b[31;1m"
        self.RESET = "\x1b[0m"

        # Base log message format
        self.log_format = "%(asctime)s - %(levelname)s - %(message)s (%(filename)s:%(lineno)d)"

        # Mapping log levels to colors
        self.FORMATS = {
            logging.DEBUG: self.GREY + self.log_format + self.RESET,
            logging.INFO: self.GREEN + self.log_format + self.RESET,
            logging.WARNING: self.YELLOW + self.log_format + self.RESET,
            logging.ERROR: self.RED + self.log_format + self.RESET,
            logging.CRITICAL: self.BOLD_RED + self.log_format + self.RESET,
        }

    def format(self, record):
        log_fmt = self.FORMATS.get(record.levelno, self.log_format)
        formatter = logging.Formatter(log_fmt, datefmt="%Y-%m-%d %H:%M:%S")
        return formatter.format(record)


