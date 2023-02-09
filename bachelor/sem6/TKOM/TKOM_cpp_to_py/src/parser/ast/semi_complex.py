# semi_complex - they consists of primitives and other semi_complex, but do not introduce new scope
from src.parser.ast.ast_node import AstNode
from src.parser.ast.ast_utils import *
from src.parser.ast.primitives import *


class Literal(AstNode):
    def __init__(self, literal_token):
        self.type, self.value = Literal.init_literal(literal_token)

    def __repr__(self):
        return f"literal={self.value}"

    @staticmethod
    def init_literal(literal_token):
        literal_type = literal_token.get_type()
        value = literal_token.get_value()
        if literal_type == TokenType.INT_LITERAL and isinstance(value, int):
            return Type(Token(TokenType.INT_KW)), value
        elif literal_type == TokenType.STRING_LITERAL and isinstance(value, str):
            return Type(Token(TokenType.STRING_KW)), value
        elif literal_type == TokenType.TRUE_KW or literal_type == TokenType.FALSE_KW:
            return Type(Token(TokenType.BOOL_KW)), literal_type == TokenType.TRUE_KW
        else:
            ParserDevelopmentError(literal_token.get_position(), "bad token in literal!").fatal()


class VariableDeclaration(AstNode):
    def __init__(self, type_token, id_token, value=None):
        self.type = Type(type_token)
        self.id = Id(id_token)
        if value is None:
            self.value = Literal(Type.get_default_value(self.type))
        else:
            self.value = value

    def __repr__(self):
        return f"VarDecl: {self.type} {self.id} = {self.value};"


class VariableAssignment(AstNode):
    def __init__(self, id_token, value):
        self.id = Id(id_token)
        self.value = value

    def __repr__(self):
        return f"VarAssign: {self.id} = {self.value};"


class FunctionArgument(AstNode):
    def __init__(self, type_token, id_token):
        self.type = Type(type_token)
        self.id = Id(id_token)

    def __repr__(self):
        return f"FunArg:({self.type}-{self.id})"


class FunctionInvocation(AstNode):
    def __init__(self, id_token, arguments):
        self.id = Id(id_token)
        self.arguments = arguments

    def __repr__(self):
        arg_str = str(self.arguments)
        if len(self.arguments) == 0:
            arg_str = ""
        return f"FunInvocation: {self.id}({arg_str})"


class Comparison(AstNode):
    def __init__(self, left, operator_token, right):
        self.left = left
        self.operator = ComparisonOperator(operator_token)
        self.right = right

    def __repr__(self):
        return f"SingleCond: ({self.left}{self.operator}{self.right})"


class ArithmeticExpression(AstNode):
    def __init__(self, left_operand, operator, right_operand, has_brackets):
        self.left_operand = left_operand
        self.operator = operator
        self.right_operand = right_operand
        self.has_brackets = has_brackets

    def __repr__(self):
        return f"ArithExpr: ({self.left_operand}{self.operator}{self.right_operand})"


class PrintStatement(AstNode):
    def __init__(self, to_print, with_new_line):
        self.to_print = to_print
        self.with_new_line = with_new_line

    def __repr__(self):
        return f"PrintStmt: {self.to_print};"


class ReturnExpression(AstNode):
    def __init__(self, value=None):
        self.value = value

    def __repr__(self):
        return f"Return: {self.value};"
