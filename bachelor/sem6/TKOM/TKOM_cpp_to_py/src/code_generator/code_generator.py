from src.parser.ast.primitives import *
from src.parser.ast.semi_complex import *
from src.parser.ast.complex import *


class CodeGenerator:
    def __init__(self):
        pass

    def generate_program(self, program):
        return self.__translate_scope(program, nest_level=0)

    def generate_program_with_main(self, program):
        return self.generate_program(program) + '''\nif __name__ == "__main__":\n    main()'''

    def __translate_scope(self, list_of_instructions, nest_level):
        scope_str = ""
        for ins in list_of_instructions:
            scope_str += self.__translate_instruction(ins, nest_level)

        return scope_str

    def __translate_instruction(self, ins, nest_level):
        return self.__translate_var_decl_or_assign(ins, nest_level) or \
               self.__translate_if_stmt(ins, nest_level) or \
               self.__translate_while_stmt(ins, nest_level) or \
               self.__translate_fun_decl(ins, nest_level) or \
               self.__translate_print(ins, nest_level) or \
               self.__translate_return(ins, nest_level) or \
               self.__translate_fun_invocation(ins, nest_level) or \
               self.__translate_single_line_comment(ins, nest_level) or \
               self.__translate_multi_line_comment(ins, nest_level)

    def __translate_var_decl_or_assign(self, ins, nest_level):
        if not isinstance(ins, VariableAssignment) and not isinstance(ins, VariableDeclaration):
            return None

        indent = self.__get_indent(nest_level)
        str_name = ins.id.name
        val_str = self.__get_r_value_str(ins.value)
        return f"{indent}{str_name} = {val_str}\n"

    def __translate_if_stmt(self, ins, nest_level):
        if not isinstance(ins, IfStatement):
            return None
        indent = self.__get_indent(nest_level)
        condition = self.__get_condition_str(ins.condition)
        if_instructions_str = self.__translate_scope(ins.if_instructions, nest_level + 1)
        else_instructions_str = self.__translate_scope(ins.else_instructions, nest_level + 1)

        if_str = f"{indent}if {condition}:\n{if_instructions_str}"
        else_str = f"{indent}else:\n{else_instructions_str}" if else_instructions_str != "" else ""
        return f"{if_str}{else_str}"

    def __translate_while_stmt(self, ins, nest_level):
        if not isinstance(ins, WhileStatement):
            return None
        indent = self.__get_indent(nest_level)
        condition = self.__get_condition_str(ins.condition)
        instructions_str = self.__translate_scope(ins.instructions, nest_level + 1)
        return f"{indent}while {condition}:\n{instructions_str}"

    def __translate_fun_decl(self, ins, nest_level):
        if not isinstance(ins, FunctionDeclaration):
            return None

        indent = self.__get_indent(nest_level)
        fun_name = ins.id.name
        args = self.__translate_fun_decl_args(ins.arguments)
        body = self.__translate_scope(ins.instructions, nest_level + 1)
        return f"{indent}def {fun_name}({args}):\n{body}\n"

    def __get_indent(self, nest_level):
        return " " * 4 * nest_level

    def __translate_fun_decl_args(self, args):
        args_str = ""

        no_of_args = len(args)
        for i in range(no_of_args - 1):
            args_str += self.__get_id_str(args[i].id) + ', '

        if no_of_args > 0:
            args_str += self.__get_id_str(args[no_of_args - 1].id)

        return args_str

    def __translate_print(self, ins, nest_level):
        if not isinstance(ins, PrintStatement):
            return None

        indent = self.__get_indent(nest_level)
        val_to_print = self.__get_r_value_str(ins.to_print)
        new_line = ''
        if not ins.with_new_line:
            new_line = ', end=""'
        return f"{indent}print({val_to_print}{new_line})\n"

    def __translate_return(self, ins, nest_level):
        if not isinstance(ins, ReturnExpression):
            return None

        indent = self.__get_indent(nest_level)
        return_value = self.__get_r_value_str(ins.value)
        return f"{indent}return {return_value}\n"

    def __translate_fun_invocation(self, ins, nest_level):
        if not isinstance(ins, FunctionInvocation):
            return None

        indent = self.__get_indent(nest_level)
        fun_name = ins.id.name
        args_str = self.__get_fun_invocation_args_str(ins.arguments)

        return f"{indent}{fun_name}({args_str})\n"

    def __get_fun_invocation_args_str(self, args):
        no_of_args = len(args)

        args_str = ""
        for i in range(no_of_args - 1):
            args_str += self.__get_r_value_str(args[i]) + ', '

        if no_of_args > 0:
            args_str += self.__get_r_value_str(args[no_of_args - 1])

        return args_str

    def __translate_single_line_comment(self, ins, nest_level):
        if not isinstance(ins, SingleLineComment):
            return None

        indent = self.__get_indent(nest_level)
        comment = ins.comment
        return f"{indent}#{comment}\n"

    def __translate_multi_line_comment(self, ins, nest_level):
        if not isinstance(ins, MultiLineComment):
            return None

        indent = self.__get_indent(nest_level)
        comment = ins.comment
        return f"{indent}'''\n{comment}\n{indent}'''\n"

    def __get_r_value_str(self, value):
        return self.__get_literal_str(value) or \
               self.__get_id_str(value) or \
               self.__get_arth_expr_str(value)

    def __get_condition_str(self, cond):
        return self.__get_literal_str(cond) or \
               self.__get_id_str(cond) or \
               self.__get_cond_str(cond)

    def __get_literal_str(self, literal):
        if isinstance(literal, Literal):
            if literal.type == Type(Token(TokenType.STRING_KW)):
                return f"\"{literal.value}\""
            return str(literal.value)

    def __get_id_str(self, id):
        if isinstance(id, Id):
            return id.name

    def __get_arth_expr_str(self, arth_expr):
        if isinstance(arth_expr, ArithmeticExpression):
            left = arth_expr.left_operand
            op = arth_expr.operator
            right = arth_expr.right_operand
            left_str = self.__get_r_value_str(left)
            op_str = self.__get_operator_str(op)
            right_str = self.__get_r_value_str(right)
            expr_str = f"{left_str} {op_str} {right_str}"
            if arth_expr.has_brackets:
                return f"({expr_str})"
            else:
                return expr_str

    def __get_cond_str(self, cond):
        if isinstance(cond, Comparison):
            left = cond.left
            op = cond.operator
            right = cond.right
            left_str = self.__get_r_value_str(left)
            op_str = self.__get_operator_str(op)
            right_str = self.__get_r_value_str(right)
            return f"{left_str} {op_str} {right_str}"

    def __get_operator_str(self, op):
        return str(op)
