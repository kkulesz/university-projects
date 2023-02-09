from src.errors.parser_errors import *
from src.parser.ast.complex import *
from src.parser.ast.semi_complex import *
from src.parser.ast.primitives import *
from src.parser.parser_utils import ParserUtils


class Parser:
    def __init__(self, lexer):
        self.__lexer = lexer
        self.__current_token = None
        self.__get_next_token()

    def parse_program(self):
        program = []
        while self.__get_current_token().get_type() != TokenType.EOF:
            new_ins = self.__parse_instruction()
            program.append(new_ins)

        return program

    def __parse_instruction(self):
        # instead of if-else everywhere
        maybe_instruction = self.__parse_declaration() or \
                            self.__parse_id_starting() or \
                            self.__parse_print() or \
                            self.__parse_return() or \
                            self.__parse_while() or \
                            self.__parse_comments() or \
                            self.__parse_if()

        if not maybe_instruction:
            ParserUnknownInstructionError(self.__get_position()).warning()
        return maybe_instruction

    def __parse_declaration(self):
        maybe_type_token = self.__check_if_one_of_tokens(ParserUtils.type_tokens)
        if not maybe_type_token:
            return None

        id_token = self.__demand_token(TokenType.IDENTIFIER)

        maybe_function_declaration = self.__parse_function_declaration(maybe_type_token, id_token)
        if maybe_function_declaration:
            return maybe_function_declaration

        maybe_variable_declaration = self.__parse_variable_declaration(maybe_type_token, id_token)
        if maybe_variable_declaration:
            return maybe_variable_declaration

        self.__demand_token(TokenType.SEMICOLON)
        ParserVariableNotInitializedError(self.__get_position(), id_token.value).warning()
        return VariableDeclaration(maybe_type_token, id_token)

    def __parse_function_declaration(self, type_token, id_token):
        if not self.__check_token(TokenType.OP_BRACKET):
            return None

        arguments = self.__parse_function_declaration_arguments()
        self.__demand_token(TokenType.CL_BRACKET)
        self.__demand_token(TokenType.OP_CURLY_BRACKET)
        instructions = []
        while not self.__check_token(TokenType.CL_CURLY_BRACKET):
            instructions.append(self.__parse_instruction())

        return FunctionDeclaration(type_token, id_token, arguments, instructions)

    def __parse_function_declaration_arguments(self):
        maybe_type_token = self.__check_if_one_of_tokens(ParserUtils.type_tokens)
        if not maybe_type_token:
            return []

        id_token = self.__demand_token(TokenType.IDENTIFIER)
        arguments_fo_far = [FunctionArgument(maybe_type_token, id_token)]
        while self.__check_token(TokenType.COMA):
            type_token = self.__demand_one_of_tokens(ParserUtils.type_tokens, "type token")
            id_token = self.__demand_token(TokenType.IDENTIFIER)
            arguments_fo_far.append(FunctionArgument(type_token, id_token))

        return arguments_fo_far

    def __parse_variable_declaration(self, maybe_type_token, id_token):
        if not self.__check_token(TokenType.ASSIGN):
            return None

        self.__check_if_not_overwriting_keywords(id_token)

        value = self.__parse_r_value()

        self.__demand_token(TokenType.SEMICOLON)
        return VariableDeclaration(maybe_type_token, id_token, value)

    def __parse_id_starting(self):
        maybe_id_token = self.__check_token(TokenType.IDENTIFIER)
        if not maybe_id_token:
            return None

        maybe_assignment = self.__parse_assignment(maybe_id_token)
        if maybe_assignment:
            return maybe_assignment

        maybe_function_invocation = self.__parse_function_invocation(maybe_id_token)
        if maybe_function_invocation:
            return maybe_function_invocation

        ParserInvalidTokenAfterIdentifierError(self.__get_position(), self.__get_current_token()).fatal()

    def __parse_assignment(self, id_token):
        if not self.__check_token(TokenType.ASSIGN):
            return None

        self.__check_if_not_overwriting_keywords(id_token)

        value = self.__parse_r_value()
        self.__demand_token(TokenType.SEMICOLON)

        return VariableAssignment(id_token, value)

    def __check_if_not_overwriting_keywords(self, id_token):
        var_name = id_token.value
        if var_name in ParserUtils.python_forbidden_keywords:
            ParserOverwrittenPythonKeywordError(self.__get_position(), var_name).fatal()
        if var_name in ParserUtils.cpp_forbidden_keywords:
            ParserOverwrittenCppKeywordError(self.__get_position(), var_name).warning()

    def __parse_r_value(self):  # literal, id or whole arithmetic_expression are possible
        return self.__parse_arithmetic_expression(has_brackets=False)

    def __parse_arithmetic_expression(self, has_brackets):
        result = self.__parse_multiplicative_factor()

        if result:
            additive_token = self.__check_if_one_of_tokens(ParserUtils.additive_operator_tokens)
            while additive_token:
                result = ArithmeticExpression(result,
                                              ArithmeticOperator(additive_token),
                                              self.__parse_multiplicative_factor(),
                                              has_brackets)
                additive_token = self.__check_if_one_of_tokens(ParserUtils.additive_operator_tokens)

        return result

    def __parse_multiplicative_factor(self, has_brackets=False):
        multiplicative_factor = self.__parse_additive_factor()

        if multiplicative_factor:
            maybe_multiplicative_token = self.__check_if_one_of_tokens(ParserUtils.multiplicative_operator_tokens)
            while maybe_multiplicative_token:
                multiplicative_factor = ArithmeticExpression(multiplicative_factor,
                                                             ArithmeticOperator(maybe_multiplicative_token),
                                                             self.__parse_additive_factor(), has_brackets)
                maybe_multiplicative_token = self.__check_if_one_of_tokens(
                    ParserUtils.multiplicative_operator_tokens)

        return multiplicative_factor

    def __parse_additive_factor(self):
        additive_factor = self.__parse_id_or_literal()

        if not additive_factor and self.__check_token(TokenType.OP_BRACKET):
            additive_factor = self.__parse_arithmetic_expression(has_brackets=True)
            self.__demand_token(TokenType.CL_BRACKET)

        return additive_factor

    def __parse_condition(self):
        maybe_left_id_or_literal = self.__parse_id_or_literal()
        if not maybe_left_id_or_literal:
            return None

        maybe_comparison_token = self.__check_if_one_of_tokens(ParserUtils.comparison_tokens)
        if maybe_comparison_token:
            maybe_right_id_or_literal = self.__parse_id_or_literal()
            if not maybe_right_id_or_literal:
                ParserExpectedLiteralOrIdentifierError(self.__get_position(), self.__get_current_token()).fatal()
            return Comparison(maybe_left_id_or_literal, maybe_comparison_token, maybe_right_id_or_literal)
        return maybe_left_id_or_literal

    def __parse_function_invocation(self, id_token):
        if not self.__check_token(TokenType.OP_BRACKET):
            return None

        arguments = self.__parse_function_invocation_arguments()
        self.__demand_token(TokenType.CL_BRACKET)
        self.__demand_token(TokenType.SEMICOLON)

        return FunctionInvocation(id_token, arguments)

    def __parse_function_invocation_arguments(self):
        maybe_argument = self.__parse_arithmetic_expression(has_brackets=False)
        if not maybe_argument:
            return []

        arguments_so_far = [maybe_argument]
        while self.__check_token(TokenType.COMA):
            arguments_so_far.append(self.__parse_arithmetic_expression(has_brackets=False))

        return arguments_so_far

    def __parse_id_or_literal(self):
        maybe_id = self.__check_token(TokenType.IDENTIFIER)
        if maybe_id:
            return Id(maybe_id)

        maybe_minus_token = self.__check_token(TokenType.MINUS)
        if maybe_minus_token:
            int_token = self.__demand_token(TokenType.INT_LITERAL)
            col = maybe_minus_token.column
            line = maybe_minus_token.line
            new_value = -int_token.value
            return Literal(Token(TokenType.INT_LITERAL, new_value, line, col))

        maybe_literal = self.__check_if_one_of_tokens(ParserUtils.literal_tokens)
        if maybe_literal:
            return Literal(maybe_literal)

        return None

    def __parse_return(self):
        if not self.__check_token(TokenType.RETURN_KW):
            return None

        maybe_return_value = self.__parse_r_value()
        self.__demand_token(TokenType.SEMICOLON)

        return ReturnExpression(maybe_return_value)

    def __parse_if(self):
        if not self.__check_token(TokenType.IF_KW):
            return None

        self.__demand_token(TokenType.OP_BRACKET)
        condition = self.__parse_condition()
        if condition is None:
            ParserNoConditionError(self.__get_position(), 'if-statement').fatal()
        self.__demand_token(TokenType.CL_BRACKET)
        self.__demand_token(TokenType.OP_CURLY_BRACKET)
        if_instructions = self.__parse_scope()
        self.__demand_at_least_one_instruction(if_instructions, 'if-statement', self.__get_position())

        else_instructions = []
        if self.__check_token(TokenType.ELSE_KW):
            self.__demand_token(TokenType.OP_CURLY_BRACKET)
            else_instructions = self.__parse_scope()
            self.__demand_at_least_one_instruction(else_instructions, 'else-statement', self.__get_position())

        return IfStatement(condition, if_instructions, else_instructions)

    def __parse_while(self):
        if not self.__check_token(TokenType.WHILE_KW):
            return None

        self.__demand_token(TokenType.OP_BRACKET)
        condition = self.__parse_condition()
        if condition is None:
            ParserNoConditionError(self.__get_position(), 'while-statement').fatal()
        self.__demand_token(TokenType.CL_BRACKET)
        self.__demand_token(TokenType.OP_CURLY_BRACKET)
        instructions = self.__parse_scope()
        self.__demand_at_least_one_instruction(instructions, 'while-statement', self.__get_position())
        return WhileStatement(condition, instructions)

    def __parse_scope(self):
        scope = []
        while not self.__check_token(TokenType.CL_CURLY_BRACKET):
            new_instruction = self.__parse_instruction()
            scope.append(new_instruction)

        return scope

    def __parse_print(self):
        if not self.__check_token(TokenType.COUT_KW):
            return None
        self.__demand_token(TokenType.STREAM_OPERATOR)
        statement_to_print = self.__parse_r_value()
        with_new_line = False
        if self.__check_token(TokenType.STREAM_OPERATOR):
            self.__demand_token(TokenType.ENDL_KW)
            with_new_line = True
        self.__demand_token(TokenType.SEMICOLON)
        return PrintStatement(statement_to_print, with_new_line)

    def __parse_comments(self):
        maybe_single_line = self.__check_token(TokenType.SINGLE_LINE_COMMENT)
        if maybe_single_line:
            return SingleLineComment(maybe_single_line)

        maybe_multi_line = self.__check_token(TokenType.MULTI_LINE_COMMENT)
        if maybe_multi_line:
            return MultiLineComment(maybe_multi_line)

        return None

    def __demand_at_least_one_instruction(self, instruction_list, stmt_name, position):
        no_of_instruction = 0
        for ins in instruction_list:
            if not isinstance(ins, SingleLineComment) and not isinstance(ins, MultiLineComment):
                no_of_instruction += 1
        if no_of_instruction < 1:
            ParserBodyWithCoContentError(position, stmt_name).fatal()

    #################################
    # UTILS
    def __demand_token(self, expected_token_type):
        token = self.__check_token(expected_token_type)
        if token:
            return token

        ParserSyntaxError(self.__current_token.get_position(),
                          expected_token_type,
                          self.__current_token.get_type()
                          ).fatal()

    def __check_token(self, expected_token_type):
        if self.__current_token.get_type() == expected_token_type:
            token = self.__current_token
            self.__get_next_token()
            return token
        return None

    def __check_if_one_of_tokens(self, list_of_tokens_types):
        for token_type in list_of_tokens_types:
            maybe_token = self.__check_token(token_type)
            if maybe_token:
                return maybe_token
        return None

    def __demand_one_of_tokens(self, list_of_tokens_types, expected_message):
        maybe_token = self.__check_if_one_of_tokens(list_of_tokens_types)
        if maybe_token:
            return maybe_token

        ParserSyntaxError(self.__current_token.get_position(),
                          self.__current_token.get_type(),
                          expected_message).fatal()

    # get functions
    def __get_current_token(self):
        return self.__current_token

    def __get_next_token(self):
        self.__current_token = self.__lexer.build_and_get_token()
        return self.__current_token

    def __get_position(self):
        return self.__current_token.get_position()
