import io
import unittest

from src.lexer.code_provider import CodeProvider
from src.lexer.lexer import Lexer
from src.lexer.token import TokenType, Token


class LexerTest(unittest.TestCase):
    def test_eof(self):
        lexer = init_lexer_for_test("")
        token = lexer.build_and_get_token()
        self.assertEqual(token.get_type(), TokenType.EOF)

    def assert_expected_tokens(self, string_input, expected_sequence_of_tokens):
        """
        Generic method for lexer testing. Takes input and expected result as arguments.
        Produces every possible token from given input and compares collection's items one by one.

        :param string_input:
        :param expected_sequence_of_tokens:
        :return:
        """
        lexer = init_lexer_for_test(string_input)
        tokens = []
        token = lexer.build_and_get_token()
        while token.type != TokenType.EOF:
            tokens.append(token)
            token = lexer.build_and_get_token()

        for i in range(0, len(expected_sequence_of_tokens)):
            self.assertEqual(tokens[i].get_type(), expected_sequence_of_tokens[i].get_type())
            self.assertEqual(tokens[i].get_value(), expected_sequence_of_tokens[i].get_value())

    def test_single_identifier(self):
        input_str = """main"""
        expected_tokens = [
            Token(TokenType.IDENTIFIER, "main")
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_multiple_identifiers(self):
        input_str = """main fun foo"""
        expected_tokens = [
            Token(TokenType.IDENTIFIER, "main"),
            Token(TokenType.IDENTIFIER, "fun"),
            Token(TokenType.IDENTIFIER, "foo")
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_return_keyword(self):
        input_str = """return"""
        expected_tokens = [
            Token(TokenType.RETURN_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_while_keyword(self):
        input_str = """while"""
        expected_tokens = [
            Token(TokenType.WHILE_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_if_keyword(self):
        input_str = """if"""
        expected_tokens = [
            Token(TokenType.IF_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_else_keyword(self):
        input_str = """else"""
        expected_tokens = [
            Token(TokenType.ELSE_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_cout_keyword(self):
        input_str = """std::cout"""
        expected_tokens = [
            Token(TokenType.COUT_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_endl_keyword(self):
        input_str = """std::endl"""
        expected_tokens = [
            Token(TokenType.ENDL_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_string_keyword(self):
        input_str = """std::string"""
        expected_tokens = [
            Token(TokenType.STRING_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_int_keyword(self):
        input_str = """int"""
        expected_tokens = [
            Token(TokenType.INT_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_bool_keyword(self):
        input_str = """bool"""
        expected_tokens = [
            Token(TokenType.BOOL_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_true_keyword(self):
        input_str = """true"""
        expected_tokens = [
            Token(TokenType.TRUE_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_false_keyword(self):
        input_str = """false"""
        expected_tokens = [
            Token(TokenType.FALSE_KW)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_plus(self):
        input_str = """+"""
        expected_tokens = [
            Token(TokenType.PLUS)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_minus(self):
        input_str = """-"""
        expected_tokens = [
            Token(TokenType.MINUS)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_assign(self):
        input_str = """="""
        expected_tokens = [
            Token(TokenType.ASSIGN)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_semicolon(self):
        input_str = """;"""
        expected_tokens = [
            Token(TokenType.SEMICOLON)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_star(self):
        input_str = """*"""
        expected_tokens = [
            Token(TokenType.STAR)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_forward_slash(self):
        input_str = """/"""
        expected_tokens = [
            Token(TokenType.FORWARD_SLASH)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_not(self):
        input_str = """!"""
        expected_tokens = [
            Token(TokenType.NOT)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_open_bracket(self):
        input_str = """("""
        expected_tokens = [
            Token(TokenType.OP_BRACKET)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_close_bracket(self):
        input_str = """)"""
        expected_tokens = [
            Token(TokenType.CL_BRACKET)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_open_curly_bracket(self):
        input_str = """{"""
        expected_tokens = [
            Token(TokenType.OP_CURLY_BRACKET)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_close_curly_bracket(self):
        input_str = """}"""
        expected_tokens = [
            Token(TokenType.CL_CURLY_BRACKET)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_or(self):
        input_str = """||"""
        expected_tokens = [
            Token(TokenType.OR)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_and(self):
        input_str = """&&"""
        expected_tokens = [
            Token(TokenType.AND)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_greater_equal(self):
        input_str = """>="""
        expected_tokens = [
            Token(TokenType.GREATER_EQUAL)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_less_equal(self):
        input_str = """<="""
        expected_tokens = [
            Token(TokenType.LESS_EQUAL)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_greater(self):
        input_str = """>"""
        expected_tokens = [
            Token(TokenType.GREATER)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_less(self):
        input_str = """<"""
        expected_tokens = [
            Token(TokenType.LESS)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_stream_operator(self):
        input_str = """<<"""
        expected_tokens = [
            Token(TokenType.STREAM_OPERATOR)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_integer_literal(self):
        input_str = """123"""
        expected_tokens = [
            Token(TokenType.INT_LITERAL, 123)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_string_literal(self):
        input_str = '''"essa"'''
        expected_tokens = [
            Token(TokenType.STRING_LITERAL, "essa")
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_string_literal_when_quotes_inside(self):
        input_str = '''"es\\\"sa"'''
        expected_tokens = [
            Token(TokenType.STRING_LITERAL, '''es\\\"sa''')
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    ##################################
    # tests when comments are not tokens
    # def test_start_single_line_comment(self):
    #     input_str = """//"""
    #     expected_tokens = [
    #         Token(TokenType.START_SINGLE_LINE_COMMENT)
    #     ]
    #     self.assert_expected_tokens(input_str, expected_tokens)
    #
    # def test_start_multi_line_comment(self):
    #     input_str = """/*"""
    #     expected_tokens = [
    #         Token(TokenType.START_MULTI_LINE_COMMENT)
    #     ]
    #     self.assert_expected_tokens(input_str, expected_tokens)
    #
    # def test_end_multi_line_comment(self):
    #     input_str = """*/"""
    #     expected_tokens = [
    #         Token(TokenType.END_MULTI_LINE_COMMENT)
    #     ]
    #     self.assert_expected_tokens(input_str, expected_tokens)
    ##################################
    def test_single_line_comment(self):
        input_str = """//comment"""
        expected_tokens = [
            Token(TokenType.SINGLE_LINE_COMMENT, "comment")
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_multi_line_comment(self):
        input_str = """/*
        comment
        */"""
        expected_tokens = [
            Token(TokenType.MULTI_LINE_COMMENT, """
        comment
        """)
        ]
        self.assert_expected_tokens(input_str, expected_tokens)

    def test_simple_main(self):
        input_str = """
        int main(){
            std::cout<<"Hello world!"<<std::endl;
        }"""
        expected_tokens = [
            Token(TokenType.INT_KW),
            Token(TokenType.IDENTIFIER, "main"),
            Token(TokenType.OP_BRACKET),
            Token(TokenType.CL_BRACKET),
            Token(TokenType.OP_CURLY_BRACKET),
            Token(TokenType.COUT_KW),
            Token(TokenType.STREAM_OPERATOR),
            Token(TokenType.STRING_LITERAL, "Hello world!"),
            Token(TokenType.STREAM_OPERATOR),
            Token(TokenType.ENDL_KW),
            Token(TokenType.SEMICOLON),
            Token(TokenType.CL_CURLY_BRACKET),
        ]
        self.assert_expected_tokens(input_str, expected_tokens)


if __name__ == '__main__':
    unittest.main()


def init_lexer_for_test(test_string):
    code_provider = CodeProvider(io.StringIO(test_string))
    return Lexer(code_provider)
