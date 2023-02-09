class GenericError(Exception):
    def __init__(self, message):
        self.message = f"{message}!"
        super().__init__(self.message)

    def fatal(self):
        print("Error! " + self.message)
        exit(-1)

    def warning(self):
        print("Warning! " + self.message)

