from enum import Enum, auto, unique


@unique
class TokenType(Enum):
    UNDEFINED = auto()

    EOF = auto()
    IDENTIFIER = auto()
    SEMICOLON = auto()
    START_SINGLE_LINE_COMMENT = auto()
    START_MULTI_LINE_COMMENT = auto()
    END_MULTI_LINE_COMMENT = auto()
    SINGLE_LINE_COMMENT = auto()
    MULTI_LINE_COMMENT = auto()
    COMA = auto()

    # brackets
    OP_BRACKET = auto()
    CL_BRACKET = auto()
    OP_CURLY_BRACKET = auto()
    CL_CURLY_BRACKET = auto()

    # arithmetic operators
    PLUS = auto()
    MINUS = auto()
    STAR = auto()
    FORWARD_SLASH = auto()

    # logical operators
    AND = auto()
    OR = auto()
    NOT = auto()

    # comparison operators
    LESS = auto()
    LESS_EQUAL = auto()
    EQUAL = auto()
    NOT_EQUAL = auto()
    GREATER = auto()
    GREATER_EQUAL = auto()

    ASSIGN = auto()
    STREAM_OPERATOR = auto()  # '<<'

    # literals
    INT_LITERAL = auto()
    STRING_LITERAL = auto()

    # keywords
    RETURN_KW = auto()
    WHILE_KW = auto()
    IF_KW = auto()
    ELSE_KW = auto()
    STD_KW = auto()
    COUT_KW = auto()
    ENDL_KW = auto()
    INT_KW = auto()
    STRING_KW = auto()
    BOOL_KW = auto()
    TRUE_KW = auto()
    FALSE_KW = auto()


class Token:
    def __init__(self, token_type: TokenType, value="", line: int = 0, column: int = 0):
        self.type = token_type
        self.line = line
        self.column = column
        self.value = value

    def get_position(self):
        return self.line, self.column

    def get_type(self):
        return self.type

    def get_value(self):
        return self.value

    def __repr__(self):
        return f'{self.type.name} \t {self.value} \t pos({self.line}, {self.column})'


class TokenDicts:
    acceptable_keywords = {
        'return': TokenType.RETURN_KW,
        'while': TokenType.WHILE_KW,
        'if': TokenType.IF_KW,
        'else': TokenType.ELSE_KW,
        'int': TokenType.INT_KW,
        'bool': TokenType.BOOL_KW,
        'true': TokenType.TRUE_KW,
        'false': TokenType.FALSE_KW
    }

    double_char_tokens = {
        '<<': TokenType.STREAM_OPERATOR,
        '<=': TokenType.LESS_EQUAL,
        '>=': TokenType.GREATER_EQUAL,
        '==': TokenType.EQUAL,
        '!=': TokenType.NOT_EQUAL,
        '//': TokenType.START_SINGLE_LINE_COMMENT,
        '/*': TokenType.START_MULTI_LINE_COMMENT,
        '*/': TokenType.END_MULTI_LINE_COMMENT,
        '&&': TokenType.AND,
        '||': TokenType.OR,
    }

    single_char_tokens = {
        '=': TokenType.ASSIGN,
        '+': TokenType.PLUS,
        '-': TokenType.MINUS,
        '*': TokenType.STAR,
        '/': TokenType.FORWARD_SLASH,
        '!': TokenType.NOT,
        '(': TokenType.OP_BRACKET,
        ')': TokenType.CL_BRACKET,
        '{': TokenType.OP_CURLY_BRACKET,
        '}': TokenType.CL_CURLY_BRACKET,
        ';': TokenType.SEMICOLON,
        '>': TokenType.GREATER,
        '<': TokenType.LESS,
        ',': TokenType.COMA
    }
