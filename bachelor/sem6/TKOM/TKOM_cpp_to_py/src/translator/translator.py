from src.lexer.code_provider import CodeProvider
from src.lexer.lexer import Lexer
from src.parser.parser import Parser
from src.semantic_analyzer.semantic_analyzer import SemanticAnalyzer
from src.code_generator.code_generator import CodeGenerator

cpp_extension = "cpp"
python_extension = "py"


class Translator:
    def __init__(self):
        pass

    @staticmethod
    def translate(input_file, with_main=True):
        file = open(input_file, "rt")

        #  init all components
        code_provider = CodeProvider(file)
        lexer = Lexer(code_provider)
        parser = Parser(lexer)
        semantic_analyzer = SemanticAnalyzer()
        code_generator = CodeGenerator()

        #  pipeline of translation
        program = parser.parse_program()
        analyzed_program = semantic_analyzer.start_analysis(program)
        python_program = ""
        if with_main:
            python_program = code_generator.generate_program_with_main(analyzed_program)
        else:
            python_program = code_generator.generate_program(analyzed_program)

        #  generate .py output file
        output_file = "generated.py"  # default
        if input_file.endswith(cpp_extension):
            output_file = input_file[:-len(cpp_extension)] + python_extension
        file.close()
        file = open(output_file, "w")
        file.write(python_program)
        file.close()
