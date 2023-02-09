from src.errors.error import *


class ParserError(GenericError):
    def __init__(self, position, message):
        line, col = position
        self.message = f"Parser: line:{line} column:{col} -- {message}"
        super().__init__(self.message)


class ParserInvalidTokenAfterIdentifierError(ParserError):
    def __init__(self, position, token):
        self.message = f"invalid token after id: {token.get_type()}"
        super().__init__(position, self.message)


class ParserExpectedLiteralOrIdentifierError(ParserError):
    def __init__(self, position, token):
        self.message = f"expected literal or id, but got {token.get_type()}"
        super().__init__(position, self.message)


class ParserNoConditionError(ParserError):
    def __init__(self, position, stmt_name):
        self.message = f"condition is required in '{stmt_name}'"
        super().__init__(position, self.message)


class ParserBodyWithCoContentError(ParserError):
    def __init__(self, position, stmt_name):
        self.message = f"at least one instruction is required in '{stmt_name}'"
        super().__init__(position, self.message)


class ParserSyntaxError(ParserError):
    def __init__(self, position, expected_token, got_token):
        self.message = f"Expected: {expected_token}, but got: {got_token}"
        super().__init__(position, self.message)


class ParserUnknownInstructionError(ParserError):
    def __init__(self, position):
        self.message = f"unknown instruction"
        super().__init__(position, self.message)


class ParserOverwrittenPythonKeywordError(ParserError):
    def __init__(self, position, keyword):
        self.message = f"overwritten Python keyword-{keyword}"
        super().__init__(position, self.message)


class ParserOverwrittenCppKeywordError(ParserError):
    def __init__(self, position, keyword):
        self.message = f"overwritten C++ keyword: {keyword} - input cpp file is not able to compile"
        super().__init__(position, self.message)


class ParserVariableNotInitializedError(ParserError):
    def __init__(self, position, var_id):
        self.message = f"uninitialized variable: {var_id} - inserting default value"
        super().__init__(position, self.message)


class ParserDevelopmentError(ParserError):  # for debug
    def __init__(self, position, message):
        self.message = f"PARSER DEVELOPMENT ERROR: {message}"
        super().__init__(position, self.message)
