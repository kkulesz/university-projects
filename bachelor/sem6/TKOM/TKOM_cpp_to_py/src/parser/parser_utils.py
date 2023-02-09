from src.lexer.token import TokenType


class ParserUtils:
    python_forbidden_keywords = ['and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else',
                                 'expect', 'False', 'finally', 'for', 'from', 'global', 'if', 'import', 'in',
                                 'is', 'lambda', 'None', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'True',
                                 'try', 'while', 'with', 'yield']
    cpp_forbidden_keywords = ['auto', 'bool', 'break', 'case', 'catch', 'char', 'class', 'const', 'continue',
                              'default', 'do', 'double', 'else', 'enum', 'false', 'float', 'for', 'goto',
                              'if', 'int', 'long', 'namespace', 'new', 'not', 'nullptr', 'or', 'private', 'public',
                              'return', 'short', 'signed', 'sizeof', 'static', 'switch', 'this', 'throw', 'true',
                              'try', 'typedef', 'union', 'unsigned', 'using', 'void', 'while']

    forbidden_ids = python_forbidden_keywords + cpp_forbidden_keywords

    type_tokens = \
        [TokenType.INT_KW, TokenType.BOOL_KW, TokenType.STRING_KW]

    literal_tokens = \
        [TokenType.INT_LITERAL, TokenType.STRING_LITERAL, TokenType.TRUE_KW, TokenType.FALSE_KW]

    function_invocation_tokens = \
        literal_tokens + [TokenType.IDENTIFIER]

    multiplicative_operator_tokens = \
        [TokenType.STAR, TokenType.FORWARD_SLASH]

    additive_operator_tokens = \
        [TokenType.PLUS, TokenType.MINUS]

    comparison_tokens = \
        [TokenType.EQUAL,
         TokenType.NOT_EQUAL,
         TokenType.GREATER_EQUAL,
         TokenType.GREATER,
         TokenType.LESS_EQUAL,
         TokenType.LESS]

    boolean_tokens = \
        [TokenType.AND, TokenType.OR]
