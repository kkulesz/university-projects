#include "../include/client/linda.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

void lindaMultiplexer(std::string &);
void lindaReadOrInput(std::string&,std::string&, bool isRead);
void lindaOutput(std::string &);

void fileInput(const std::string&);
void userInput();


void printCommandPrompt(){
    std::cout << "Pass instruction:\n" ;
}

void printInstruction(){
    std::cout<<
    "Possible instructions:\n"
    "read <tuplePattern> <timeoutInSeconds>\n"
    "input <tuplePattern> <timeoutInSeconds>\n"
    "output <tuple>\n\n"
    "<tuplePattern> example: \"string:==abc;integer:>=15;float:*\"\n"
    "<tuple> example: \"string:abc;integer:1000:float:-123.45\"\n"
    "press <q> to quit program\n"
    "==============================================================\n";
}


int main(int argc, char** argv){
    if(argc==1){
        userInput();
    }else{
        fileInput(argv[1]);
    }
}

void lindaMultiplexer(std::string &line){
    std::stringstream ss;
    std::vector<std::string> wordsInLine;
    ss << line;
    for(std::string s; ss >>s;){
        wordsInLine.push_back(s);
    }

    std::string instructionStr = wordsInLine[0];
    wordsInLine.erase(wordsInLine.begin()); //no longer needed

    std::string lastElem = wordsInLine.back();//may be last element of tuple if output OR timeout if input/read
    wordsInLine.pop_back();

    std::string patternOrTupleStr;
    for(const auto& str: wordsInLine){
        patternOrTupleStr += str;
    }

    if(instructionStr == "output"){
        std::string tupleStr = patternOrTupleStr + lastElem;
        lindaOutput(tupleStr);
    }else if(instructionStr == "read"){
        lindaReadOrInput(patternOrTupleStr, lastElem, true);
    }else if(instructionStr == "input"){
        lindaReadOrInput(patternOrTupleStr, lastElem, false);
    }else {
        throw;
    }
}

void lindaOutput(std::string &tupleStr) {
    Tuple tuple = Tuple(true, tupleStr);
    linda_output(tuple);
    std::cout<<"User passed:\n";
    tuple.print();
}

void lindaReadOrInput(std::string &tuplePatternStr, std::string &timeoutStr, bool isRead) {
    time_t timeout = std::stoi(timeoutStr) * 1000;
    TuplePattern pattern = TuplePattern(tuplePatternStr);
    std::optional<Tuple> maybeTuple;
    if(isRead){
        maybeTuple = linda_read(pattern, timeout);
    }else{
        maybeTuple = linda_input(pattern, timeout);
    }

    if(maybeTuple){
        std::cout<<"Received from server: \n";
        maybeTuple->print();
    }else{
        std::cout<<"TIMEOUT!\n";
    }
}

void fileInput(const std::string& fileName){
    int i = 0;
    std::fstream file;
    file.open(fileName, std::ios::in);
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            if(line == ""){
                continue;
            }
            ++i;
            std::cout<<i<<": ";
            lindaMultiplexer(line);
            std::cout<<"==============================================================\n";
        }
    }else{
        throw std::runtime_error("Unable to open file");
    }
    std::cout<<"End of work\n";
}

void userInput(){
    std::string line;
    printInstruction();

    while(line != "q"){
        printCommandPrompt();
        std::getline(std::cin, line);
        try {
            lindaMultiplexer(line);
        }catch(const std::exception& e){
            std::cout << "Invalid instruction string!\n";
//            std::cout<< e.what()<<std::endl;
        }
        std::cout<<"==============================================================\n";
    }
}