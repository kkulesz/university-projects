import unittest
import os

from src.translator.translator import Translator

str_with_includes = """#include <iostream>
#include <string>
"""


class TranslatorTest(unittest.TestCase):
    def assert_outputs(self, input_cpp_str):
        cpp_file_name = 'file.cpp'
        py_file_name = 'file.py'

        cpp_exec_file_name = 'cpp.exec'

        cpp_output_file = 'cpp_output.txt'
        py_output_file = 'py_output.txt'

        # generate cpp source file
        file = open(cpp_file_name, "w")
        file.write(input_cpp_str)
        file.close()

        # generate py source file
        Translator.translate(cpp_file_name, with_main=True)

        # generate output files
        os.system(f"g++ {cpp_file_name} -o {cpp_exec_file_name}")
        os.system(f"{cpp_exec_file_name} > {cpp_output_file}")
        os.system(f"python {py_file_name} > {py_output_file}")

        # read outputs of both files
        file = open(cpp_output_file, "r")
        cpp_output = file.read()
        file.close()

        file = open(py_output_file, "r")
        py_output = file.read()
        file.close()

        # tidy up generated files
        os.system(f"del {cpp_output_file} {py_output_file}")
        os.system(f"del {cpp_exec_file_name} {cpp_file_name} {py_file_name}")

        self.assertTrue(cpp_output == py_output)

    def test_print_new_line(self):
        input_cpp_str = str_with_includes + """
int main(){
    std::cout<<"test_print"<<std::endl;
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_print_no_new_line(self):
        input_cpp_str = str_with_includes + """
int main(){
    std::cout<<"test_print";
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_if_without_else(self):
        input_cpp_str = str_with_includes + """
int main(){
    if(true){
        std::cout<<"test_if_without_else"<<std::endl;
    }
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_if_with_else(self):
        input_cpp_str = str_with_includes + """
int main(){
    if(false){
        std::cout<<"test_if_without_else"<<std::endl;
    }else{
        std::cout<<"test_if_with_else"<<std::endl;
    }
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_while_with_variable(self):
        input_cpp_str = str_with_includes + """
int main(){
    int i = 0;
    while(i<10){
        std::cout<<i<<std::endl;
        i = i+1;
    }
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_var_assignments(self):
        input_cpp_str = str_with_includes + """
int main(){
    int number = 2*(2+2);
    std::string str = "nananan";
    bool trueLiteral = true;
    if(trueLiteral){
        std::cout<<number;
        std::cout<<str<<std::endl;
    }
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_function_no_args(self):
        input_cpp_str = str_with_includes + """
int fun(){
    std::cout<<"fun"<<std::endl;
    return 0;
}

int main(){
    fun();
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_function_one_arg(self):
        input_cpp_str = str_with_includes + """
std::string fun(std::string str){
    std::cout<<str<<std::endl;
    return "str";
}

int main(){
    fun("test_string_fun");
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_complex(self):
        input_cpp_str = str_with_includes + """
std::string fun(std::string str){
    std::cout<<str<<std::endl;
    return "str";
}

bool fun2(int integer){
    bool bVar = true;
    int i = 21;
    while(bVar){
        if(i == 25){
            return bVar;
        }
        std::cout<<i<<std::endl;
        i = i+1;
    }
    
    return false;
}

int main(){
    fun("test_string_fun");
    fun2(1);
    return 0;
}"""
        self.assert_outputs(input_cpp_str)

    def test_even_more_complex(self):
        input_cpp_str = str_with_includes + """
std::string fun(std::string str){
    std::cout<<str<<std::endl;
    return "str";
}

bool fun2(int integer){
    bool bVar = true;
    int i = 21;
    while(bVar){
        int j = 23;
        while(j < 25){
            j = j+1;
            std::cout<<j<<std::endl;
            if(true){
                std::cout<<j;
                if(true){
                    std::cout<<j;
                    if(true){
                        std::cout<<j;
                        if(true){
                            std::cout<<j;
                        }
                    }
                }
            }
        }
        if(i == 25){
            return bVar;
        }
        std::cout<<i<<std::endl;
        i = i+1;
    }

    return false;
}

int main(){
    fun("test_string_fun");
    fun2(1);
    return 0;
}"""
        self.assert_outputs(input_cpp_str)
