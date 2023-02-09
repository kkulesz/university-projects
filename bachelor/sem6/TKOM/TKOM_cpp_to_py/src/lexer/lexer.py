from src.errors.lexer_errors import *
from src.lexer.token import *


class Lexer:
    def __init__(self, code_provider):
        self.__code_provider = code_provider
        self.token = None
        self.__ignore_whites()
        self.__ignore_hash_starting()  # ignore includes and other macros

    def get_token(self):
        return self.token

    def build_and_get_token(self):
        self.__ignore_whites()
        line, col = self.__get_position()
        token = self.__try_match()
        token.column = col
        token.line = line

        self.token = token
        return self.token

    def __ignore_whites(self):
        curr_char = self.__get_char()
        while curr_char in [' ', '\t', '\n']:
            curr_char = self.__move_and_get_char()

    def __try_match(self):
        # instead of 'if else' everywhere
        return self.__try_eof() or \
               self.__try_id_or_keyword() or \
               self.__try_number() or \
               self.__try_string() or \
               self.__try_operators_or_comments() or \
               self.__get_undefined_and_move()

    ################################
    # try methods
    def __try_eof(self):
        if self.__get_char() == '':
            return Token(TokenType.EOF)
        return None

    def __try_id_or_keyword(self):
        candidate = self.__read_word()
        if candidate in TokenDicts.acceptable_keywords:
            token_type = TokenDicts.acceptable_keywords[candidate]
            return Token(token_type)
        elif candidate != "":
            maybe_std_keyword = self.__try_std_keywords(candidate)
            if maybe_std_keyword:
                self.__move_pointer()
                return maybe_std_keyword
            return Token(TokenType.IDENTIFIER, candidate)

        return None

    def __try_std_keywords(self, candidate):
        if candidate != "std":
            return None
        maybe_namespace_operator = self.__get_char() + self.__move_and_get_char()
        if maybe_namespace_operator != "::":
            LexerInvalidStdTokenError(self.__get_position()).fatal()

        rest_of_word = ''
        for i in range(0, 4):
            rest_of_word += self.__move_and_get_char()

        if rest_of_word == "cout":
            return Token(TokenType.COUT_KW)
        elif rest_of_word == "endl":
            return Token(TokenType.ENDL_KW)
        elif rest_of_word == "stri":
            rest_of_word += self.__move_and_get_char()
            rest_of_word += self.__move_and_get_char()
            if rest_of_word == "string":
                return Token(TokenType.STRING_KW)
        LexerInvalidStdTokenError(self.__get_position()).fatal()

    def __try_number(self):
        value_so_far = 0
        digit_candidate = self.__get_char()
        if digit_candidate.isdigit():
            if digit_candidate == '0':
                self.__move_pointer()
                return Token(TokenType.INT_LITERAL, value_so_far)

            value_so_far = ord(digit_candidate) - ord('0')
            digit_candidate = self.__move_and_get_char()
            while digit_candidate.isdigit():
                value_so_far *= 10
                value_so_far += ord(digit_candidate) - ord('0')
                digit_candidate = self.__move_and_get_char()
            return Token(TokenType.INT_LITERAL, value_so_far)

        return None

    def __try_string(self):
        curr_character = self.__get_char()
        if curr_character == '"':
            string = ''
            prev_character = curr_character
            curr_character = self.__move_and_get_char()
            while not (curr_character == '"' and prev_character != "\\"):
                string += curr_character
                prev_character = curr_character
                curr_character = self.__move_and_get_char()
                if curr_character == "":
                    LexerNoEndOfStringProvidedError(self.__get_position()).warning()
                    break

            self.__move_pointer()  # move so next char will not be quote
            return Token(TokenType.STRING_LITERAL, string)
        return None

    def __try_operators_or_comments(self):
        tmp_token = None
        candidate = self.__get_char()
        if candidate in TokenDicts.single_char_tokens:
            tmp_token_type = TokenDicts.single_char_tokens[candidate]
            tmp_token = Token(tmp_token_type)

        candidate += self.__move_and_get_char()
        if candidate in TokenDicts.double_char_tokens:
            tmp_token_type = TokenDicts.double_char_tokens[candidate]

            if tmp_token_type == TokenType.START_SINGLE_LINE_COMMENT:
                comment_value = self.__get_characters_to_new_line()
                tmp_token = Token(TokenType.SINGLE_LINE_COMMENT, comment_value)

            elif tmp_token_type == TokenType.START_MULTI_LINE_COMMENT:
                comment_value = self.__get_characters_to_end_of_multiline()
                tmp_token = Token(TokenType.MULTI_LINE_COMMENT, comment_value)

            else:
                tmp_token = Token(tmp_token_type)

            self.__move_pointer()
        return tmp_token

    def __get_undefined_and_move(self):
        char = self.__get_char()
        self.__move_pointer()  # move so we can continue after undefined
        LexerUndefinedTokenError(self.__get_position()).warning()
        return Token(TokenType.UNDEFINED, char)

    def __read_word(self):
        word_so_far = ""
        new_char = self.__get_char()
        if new_char.isalpha():
            while new_char.isalpha() or new_char.isdigit():
                word_so_far += new_char
                new_char = self.__move_and_get_char()
        return word_so_far

    def __get_characters_to_new_line(self):
        string_of_chars = ""
        character = self.__move_and_get_char()
        while character != '\n' and character != '':
            string_of_chars += character
            character = self.__move_and_get_char()
        return string_of_chars

    def __get_characters_to_end_of_multiline(self):
        string_of_chars = ""
        character = self.__move_and_get_char()
        next_character = self.__move_and_get_char()
        maybe_end_of_comment = character + next_character
        while maybe_end_of_comment != '*/':
            if maybe_end_of_comment == "":
                LexerNoEndOfMultilineCommentProvidedError(self.__get_position()).warning()
                return string_of_chars
            string_of_chars += character
            character = next_character
            next_character = self.__move_and_get_char()
            maybe_end_of_comment = character + next_character
        return string_of_chars

    def __ignore_hash_starting(self):
        char = self.__get_char()
        while char == '#':
            while char != '\n':
                char = self.__move_and_get_char()
            char = self.__move_and_get_char()

    def __move_pointer(self):
        _ = self.__code_provider.move_and_get_char()

    def __move_and_get_char(self):
        return self.__code_provider.move_and_get_char()

    def __get_char(self):
        return self.__code_provider.get_char()

    def __get_position(self):
        return self.__code_provider.get_position()
