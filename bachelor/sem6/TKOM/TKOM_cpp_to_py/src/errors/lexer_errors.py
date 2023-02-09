from src.errors.error import *


class LexerError(GenericError):
    def __init__(self, position, message):
        line, col = position
        self.message = f"Lexer: line:{line} column:{col} -- {message}!"
        super().__init__(self.message)


class LexerNoEndOfStringProvidedError(LexerError):
    def __init__(self, position):
        self.message = "no end of string provided"
        super().__init__(position, self.message)


class LexerNoEndOfMultilineCommentProvidedError(LexerError):
    def __init__(self, position):
        self.message = "no end of multi-line comment"
        super().__init__(position, self.message)


class LexerUndefinedTokenError(LexerError):
    def __init__(self, position):
        self.message = "undefined token"
        super().__init__(position, self.message)


class LexerInvalidStdTokenError(LexerError):
    def __init__(self, position):
        self.message = "invalid std token"
        super().__init__(position, self.message)



