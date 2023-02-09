from src.errors.semantic_errors import *
from src.parser.ast.semi_complex import *
from src.parser.ast.complex import *
from src.semantic_analyzer.symbol import *

# helper
INT_TYPE = Type(Token(TokenType.INT_KW))


class SemanticAnalyzer:
    def __init__(self):
        pass

    def start_analysis(self, program):
        return self.__analyze_scope(program, {}, {}, False, None)

    def __check_fun_declaration(self, fun_decl, var_symbols, fun_symbols):
        return_type = fun_decl.type
        fun_name = fun_decl.id.name
        args = fun_decl.arguments
        body = fun_decl.instructions

        arg_types = []
        for arg in args:
            arg_name = arg.id.name
            arg_type = arg.type
            new_var_symbol = VariableSymbol(arg_type, arg_name)
            var_symbols[arg_name] = new_var_symbol
            arg_types.append(arg_type)

        new_fun_symbol = FunctionSymbol(return_type, fun_name, arg_types)
        fun_symbols[fun_name] = new_fun_symbol
        self.__analyze_scope(body, var_symbols, fun_symbols, is_inside_fun=True, return_type=return_type)
        if not self.__check_if_return_in_fun_body(body, fun_name):
            SemanticNoReturnExpressionInFunBodyError(fun_name).warning()

    def __check_if_return_in_fun_body(self, list_of_instruction, fun_name):
        for ins in list_of_instruction:
            if isinstance(ins, ReturnExpression):
                return True
            elif isinstance(ins, IfStatement):
                if self.__check_if_return_in_fun_body(ins.if_instructions, fun_name):
                    return True
                if self.__check_if_return_in_fun_body(ins.else_instructions, fun_name):
                    return True
            elif isinstance(ins, WhileStatement):
                if self.__check_if_return_in_fun_body(ins.instructions, fun_name):
                    return True
        return False

    def __check_var_declaration(self, var_decl, var_symbols, fun_symbols):
        var_name = var_decl.id.name
        if var_name in var_symbols:
            SemanticVariableRedeclarationError(var_name).warning()
        self.__check_r_value(var_decl.value, var_symbols, fun_symbols, var_decl.type)

        new_var_symbol = VariableSymbol(var_decl.type, var_name)
        var_symbols[var_name] = new_var_symbol

    def __check_var_assignment(self, var_assignment, var_symbols, fun_symbols):
        var_name = var_assignment.id.name
        if var_name not in var_symbols:
            # if variable is not declared earlier then we warn user and try to guess what type is given value
            SemanticAssignmentWithoutDeclarationError(var_name).warning()  # TODO: zastanwoic się nad tym
            putative_type = self.__get_type_of_r_value(var_assignment.value, var_symbols)
            var_symbols[var_name] = VariableSymbol(putative_type, var_name)
        else:
            var_type = var_symbols[var_name].get_type()
            self.__check_r_value(var_assignment.value, var_symbols, fun_symbols, var_type)

    def __check_if_stmt(self, if_stmt, var_symbols, fun_symbols, is_inside_fun, return_type):
        condition = if_stmt.condition
        self.__check_condition(condition, var_symbols, fun_symbols)
        if_instructions = if_stmt.if_instructions
        else_instructions = if_stmt.else_instructions
        self.__analyze_scope(if_instructions, var_symbols.copy(), fun_symbols.copy(), is_inside_fun, return_type)
        self.__analyze_scope(else_instructions, var_symbols.copy(), fun_symbols.copy(), is_inside_fun, return_type)

    def __check_while_stmt(self, while_stmt, var_symbols, fun_symbols, is_inside_fun, return_type):
        condition = while_stmt.condition
        self.__check_condition(condition, var_symbols, fun_symbols)
        instructions = while_stmt.instructions
        self.__analyze_scope(instructions, var_symbols.copy(), fun_symbols.copy(), is_inside_fun, return_type)

    def __check_return_expr(self, return_expr, var_symbols, fun_symbols, is_inside_fun, return_type):
        if not is_inside_fun:
            SemanticReturnNotInsideFunctionBodyError().fatal()

        self.__check_r_value(return_expr.value, var_symbols, fun_symbols, return_type)

    def __check_arithmetic_expr(self, arithmetic_expr, var_symbols, fun_symbols):
        left = arithmetic_expr.left_operand
        right = arithmetic_expr.right_operand
        self.__check_r_value(left, var_symbols, fun_symbols, INT_TYPE)
        self.__check_r_value(right, var_symbols, fun_symbols, INT_TYPE)

    def __check_fun_invocation(self, fun_invocation, var_symbols, fun_symbols):
        fun_name = fun_invocation.id.name
        if fun_name not in fun_symbols:
            SemanticNoSuchFunctionError(fun_name).fatal()

        args = fun_invocation.arguments
        expected_types = fun_symbols[fun_name].arg_types

        if len(args) != len(expected_types):
            SemanticInvalidNumberOfArgsError(len(args), len(expected_types)).fatal()

        invoke_arg_types = []
        for arg in args:
            invoke_arg_types.append(self.__get_fun_invocation_argument_type(arg, var_symbols))

        for i in range(len(args)):
            if invoke_arg_types[i] != expected_types[i]:
                SemanticTypesOfArgsInFunInvocationError(fun_name, expected_types, invoke_arg_types).fatal()

    def __get_fun_invocation_argument_type(self, arg, var_symbols):
        if isinstance(arg, Literal):
            return arg.type
        elif isinstance(arg, Id):
            return var_symbols[arg.name].get_type()
        elif isinstance(arg, ArithmeticExpression):
            return INT_TYPE
        else:
            SemanticAnalyzerDevelopmentError(f"invalid function arg! - {arg}").fatal()

    def __check_print_stmt(self, print_stmt, var_symbols, fun_symbols):
        self.__check_r_value(print_stmt.to_print, var_symbols, fun_symbols, expected_type=None)

    def __check_condition(self, condition, var_symbols, fun_symbols):
        if isinstance(condition, Literal):
            self.__check_literal(condition, expected_type=None)
        elif isinstance(condition, Id):
            self.__check_var_id(condition, var_symbols, expected_type=None)
        elif isinstance(condition, Comparison):
            self.__check_comparison(condition, var_symbols)
        else:
            SemanticAnalyzerDevelopmentError(f"unknown condition! - {condition}").fatal()

    def __check_comparison(self, comparison, var_symbols):
        self.__check_r_value(comparison.left, var_symbols, fun_symbols=None, expected_type=INT_TYPE)
        self.__check_r_value(comparison.right, var_symbols, fun_symbols=None, expected_type=INT_TYPE)

    def __check_r_value(self, r_value, var_symbols, fun_symbols, expected_type):
        if isinstance(r_value, Literal):
            self.__check_literal(r_value, expected_type)
        elif isinstance(r_value, Id):
            self.__check_var_id(r_value, var_symbols, expected_type)
        elif isinstance(r_value, ArithmeticExpression):
            if expected_type == INT_TYPE:
                self.__check_arithmetic_expr(r_value, var_symbols, fun_symbols)
            else:
                SemanticNotNumberInArithmeticExprError(expected_type).fatal()
        else:
            SemanticAnalyzerDevelopmentError(f"unknown right value! - {r_value}").fatal()

    def __get_type_of_r_value(self, r_value, var_symbols):
        if isinstance(r_value, Literal):
            return r_value.type
        elif isinstance(r_value, Id):
            return var_symbols[r_value.name].get_type()
        elif isinstance(r_value, ArithmeticExpression):
            return INT_TYPE

    def __check_var_id(self, var_id, var_symbols, expected_type):
        var_name = var_id.name
        if var_name not in var_symbols:
            SemanticUnknownSymbolError(var_name).fatal()
        if expected_type is not None and expected_type != var_symbols[var_name].type:
            SemanticInvalidTypeError(expected_type, var_symbols[var_name].type).fatal()

    def __check_literal(self, literal, expected_type):
        if expected_type is not None and literal.type != expected_type:
            SemanticInvalidTypeError(expected_type, literal.type).fatal()

    def __analyze_scope(self, list_of_instructions, var_symbols, fun_symbols, is_inside_fun, return_type):
        for ins in list_of_instructions:
            if isinstance(ins, FunctionDeclaration):
                self.__check_fun_declaration(ins, var_symbols.copy(), fun_symbols)
            elif isinstance(ins, VariableDeclaration):
                self.__check_var_declaration(ins, var_symbols, fun_symbols)
            elif isinstance(ins, VariableAssignment):
                self.__check_var_assignment(ins, var_symbols, fun_symbols)
            elif isinstance(ins, IfStatement):
                self.__check_if_stmt(ins, var_symbols.copy(), fun_symbols.copy(), is_inside_fun, return_type)
            elif isinstance(ins, WhileStatement):
                self.__check_while_stmt(ins, var_symbols.copy(), fun_symbols.copy(), is_inside_fun, return_type)
            elif isinstance(ins, FunctionInvocation):
                self.__check_fun_invocation(ins, var_symbols, fun_symbols)
            elif isinstance(ins, ReturnExpression):
                self.__check_return_expr(ins, var_symbols, fun_symbols, is_inside_fun, return_type)
            elif isinstance(ins, PrintStatement):
                self.__check_print_stmt(ins, var_symbols, fun_symbols)
            elif isinstance(ins, SingleLineComment) or isinstance(ins, MultiLineComment):
                pass  # if comment then do nothing
            else:
                SemanticAnalyzerDevelopmentError(f"unknown instruction in scope: {ins}!").fatal()

        return list_of_instructions  # if everything is correct then function is 'transparent'
