import io
import unittest

from src.lexer.code_provider import CodeProvider
from src.lexer.lexer import Lexer
from src.parser.parser import Parser
from src.parser.ast.semi_complex import *
from src.parser.ast.complex import *


class ParserTest(unittest.TestCase):
    def assert_instructions(self, list_of_instructions, list_of_expected):
        for i in range(0, len(list_of_expected)):
            curr_ins = list_of_instructions[i]
            curr_exp = list_of_expected[i]
            self.assertTrue(isinstance(curr_ins, curr_exp))

    def test_single_comment(self):
        input_str = """
        //comment
        """
        list_of_expected = [SingleLineComment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_multi_comment(self):
        input_str = """/*
        ....
        komentarz
        ....
        */"""
        list_of_expected = [MultiLineComment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_int_variable_declaration_without_init(self):
        input_str = """
        int i;
        """
        list_of_expected = [VariableDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_type_in_int_variable_declaration(self):
        input_str = """
        int i;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_type = program[0].type
        self.assertTrue(isinstance(var_type, Type))

    def test_type_in_bool_variable_declaration(self):
        input_str = """
        bool b;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_type = program[0].type
        self.assertTrue(isinstance(var_type, Type))

    def test_type_in_string_variable_declaration(self):
        input_str = """
        std::string b;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_type = program[0].type
        self.assertTrue(isinstance(var_type, Type))

    def test_default_value_in_int_variable_declaration(self):
        input_str = """
        int i;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_value = program[0].value.value
        self.assertEqual(var_value, 0)

    def test_default_value_in_bool_variable_declaration(self):
        input_str = """
        bool i;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_value = program[0].value.value
        self.assertEqual(var_value, False)

    def test_default_value_in_string_variable_declaration(self):
        input_str = """
        std::string i;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        var_value = program[0].value.value
        self.assertEqual(var_value, "")

    def test_int_variable_declaration_with_init(self):
        input_str = """
        int i = 11;
        """
        list_of_expected = [VariableDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_int_value_in_variable_declaration_with_init(self):
        input_str = """
        int i = 11;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        literal = program[0].value
        self.assertTrue(isinstance(literal, Literal))
        literal_value = literal.value
        self.assertEqual(literal_value, 11)

    def test_bool_value_in_variable_declaration_with_init(self):
        input_str = """
        bool i = true;
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        literal = program[0].value
        self.assertTrue(isinstance(literal, Literal))
        literal_value = literal.value
        self.assertEqual(literal_value, True)

    def test_string_value_in_variable_declaration_with_init(self):
        input_str = """
        std::string i = "napis";
        """
        parser = init_parser(input_str)
        program = parser.parse_program()
        literal = program[0].value
        self.assertTrue(isinstance(literal, Literal))
        literal_value = literal.value
        self.assertEqual(literal_value, "napis")

    def test_boolean_variable_declaration_with_init(self):
        input_str = """
        bool i = true;
        """
        list_of_expected = [VariableDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_string_variable_declaration_with_init(self):
        input_str = """
        std::string i = "napis";
        """
        list_of_expected = [VariableDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_variable_assignment_with_int(self):
        input_str = """
        i = 11;
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_variable_assignment_with_string(self):
        input_str = """
        i = "text";
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_variable_assignment_with_boolean(self):
        input_str = """
        i = false;
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_arithmetic_nomultiplication_nobrackets(self):
        input_str = """
        i = a+b+c;
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_arithmetic_multiplication_nobrackets(self):
        input_str = """
        i = a+b*c;
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_arithmetic_multiplication_brackets(self):
        input_str = """
        i = d*(a+(b*c));
        """
        list_of_expected = [VariableAssignment]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_function_declaration_noargs_nobody(self):
        input_str = """
        int fun(){
        }
        """
        list_of_expected = [FunctionDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_function_declaration_args_nobody(self):
        input_str = """
        int fun(int a, int b){
        }
        """
        list_of_expected = [FunctionDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_function_declaration_args_body(self):
        input_str = """
        int fun(int a, int b){
            return a;
        }"""
        list_of_expected = [FunctionDeclaration]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_function_invocation_noargs(self):
        input_str = """
        fun();
        """
        list_of_expected = [FunctionInvocation]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_function_invocation_args(self):
        input_str = """
        fun(a, b, "essa", true);
        """
        list_of_expected = [FunctionInvocation]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_print(self):
        input_str = """
        std::cout<<"napis"<<std::endl;
        """
        list_of_expected = [PrintStatement]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_return_no_value(self):
        input_str = """
        return;
        """
        list_of_expected = [ReturnExpression]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_return_value(self):
        input_str = """
        return true;
        """
        list_of_expected = [ReturnExpression]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_while_body(self):
        input_str = """
        while(i<10){
            int i = i+1;
        }"""
        list_of_expected = [WhileStatement]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_if_body_noelse(self):
        input_str = """
        if(true){
            std::cout<<"dziala"<<std::endl;
        }"""
        list_of_expected = [IfStatement]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_if_body_else_body(self):
        input_str = """
        if(true){
            std::cout<<"dziala"<<std::endl;
        }else{
            std::cout<<"to tez"<<std::endl;
        }
        """
        list_of_expected = [IfStatement]
        parser = init_parser(input_str)
        program = parser.parse_program()
        self.assert_instructions(program, list_of_expected)

    def test_nested_instructions(self):
        input_str = """
        int fun(int a, int b, int c){
            return a+b+c;
        }

        int i = 1;
        while(true){
            if(i<10){
                i = i+10;
                std::string str = "napis";
            }else{
                fun(1,2,3);
            }
        }
        std::cout<<"dziala"<<std::endl;
        return 1;
        """
        parser = init_parser(input_str)

        first_level = parser.parse_program()
        first_level_expected = [FunctionDeclaration, VariableDeclaration, WhileStatement, PrintStatement,
                                ReturnExpression]

        fun_decl = first_level[0].instructions
        fun_decl_expected = [ReturnExpression]

        while_stmt = first_level[2].instructions
        while_stmt_expected = [IfStatement]

        nested_if_stmt = while_stmt[0].if_instructions
        nested_if_stmt_expected = [VariableAssignment, VariableDeclaration]
        nested_else_stmt = while_stmt[0].else_instructions
        nested_else_stmt_expected = [FunctionInvocation]

        self.assert_instructions(first_level, first_level_expected)
        self.assert_instructions(fun_decl, fun_decl_expected)
        self.assert_instructions(while_stmt, while_stmt_expected)
        self.assert_instructions(nested_if_stmt, nested_if_stmt_expected)
        self.assert_instructions(nested_else_stmt, nested_else_stmt_expected)


if __name__ == '__main__':
    unittest.main()


def init_parser(test_string):
    code_provider = CodeProvider(io.StringIO(test_string))
    lexer = Lexer(code_provider)
    return Parser(lexer)
