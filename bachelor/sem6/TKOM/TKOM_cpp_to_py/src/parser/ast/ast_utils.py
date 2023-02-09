from enum import Enum, auto, unique
from src.lexer.token import TokenType, Token


@unique
class Types(Enum):
    INT = auto()
    STRING = auto()
    BOOLEAN = auto()


@unique
class ArithmeticOperatorTypes(Enum):
    PLUS = auto()
    MINUS = auto()
    MULTIPLY = auto()
    DIVIDE = auto()


@unique
class ComparisonOperatorTypes(Enum):
    EQUAL = auto()
    NOT_EQUAL = auto()
    GREATER = auto()
    GREATER_EQUAL = auto()
    LESS = auto()
    LESS_EQUAL = auto()


@unique
class LogicalOperatorTypes(Enum):
    NOT = auto()
    OR = auto()
    AND = auto()


class Dictionaries:
    default_values = {
        Types.INT: Token(TokenType.INT_LITERAL, 0),
        Types.STRING: Token(TokenType.STRING_LITERAL, ''),
        Types.BOOLEAN: Token(TokenType.FALSE_KW)
    }

    token_to_types = {
        TokenType.INT_KW: Types.INT,
        TokenType.STRING_KW: Types.STRING,
        TokenType.BOOL_KW: Types.BOOLEAN
    }

    token_to_arithmetic_operator = {
        TokenType.PLUS: ArithmeticOperatorTypes.PLUS,
        TokenType.MINUS: ArithmeticOperatorTypes.MINUS,
        TokenType.STAR: ArithmeticOperatorTypes.MULTIPLY,
        TokenType.FORWARD_SLASH: ArithmeticOperatorTypes.DIVIDE
    }

    token_to_comparison_operator = {
        TokenType.EQUAL: ComparisonOperatorTypes.EQUAL,
        TokenType.NOT_EQUAL: ComparisonOperatorTypes.NOT_EQUAL,
        TokenType.GREATER: ComparisonOperatorTypes.GREATER,
        TokenType.GREATER_EQUAL: ComparisonOperatorTypes.GREATER_EQUAL,
        TokenType.LESS: ComparisonOperatorTypes.LESS,
        TokenType.LESS_EQUAL: ComparisonOperatorTypes.LESS_EQUAL
    }

    token_to_logical_operator = {
        TokenType.NOT: LogicalOperatorTypes.NOT,
        TokenType.OR: LogicalOperatorTypes.OR,
        TokenType.AND: LogicalOperatorTypes.AND
    }

    primitive_to_string = {
        ArithmeticOperatorTypes.PLUS: '+',
        ArithmeticOperatorTypes.MINUS: '-',
        ArithmeticOperatorTypes.DIVIDE: '/',
        ArithmeticOperatorTypes.MULTIPLY: '*',

        ComparisonOperatorTypes.EQUAL: '==',
        ComparisonOperatorTypes.NOT_EQUAL: '!=',
        ComparisonOperatorTypes.GREATER: '>',
        ComparisonOperatorTypes.GREATER_EQUAL: '>=',
        ComparisonOperatorTypes.LESS: '<',
        ComparisonOperatorTypes.LESS_EQUAL: '<=',

        LogicalOperatorTypes.NOT: 'not',
        LogicalOperatorTypes.OR: 'or',
        LogicalOperatorTypes.AND: 'and',

        Types.INT: 'int',
        Types.STRING: 'string',
        Types.BOOLEAN: 'bool'
    }
