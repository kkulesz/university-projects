#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>

#define ALPHABET_SIZE 2
#define TEXT_LENGTH 100
#define PATTERN_LENGTH 4


template<typename D = std::chrono::microseconds>
class Benchmark {
public:

    Benchmark(bool printOnExit = false) : m_print(printOnExit) {
        start = std::chrono::high_resolution_clock::now();
    }
    typename D::rep elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto result = std::chrono::duration_cast<D>(end-start);
        return result.count();
    }
    ~Benchmark() {
        auto result = elapsed();
        if (m_print)
        {
            std::cerr << "Czas: " << result << "\n";
        }
    }
private:
    std::chrono::high_resolution_clock::time_point start;
    bool m_print = true;
};



std::vector<int>find(std::string const & str,// szukany napis
                    std::string const & text);// przeszukiwany tekst
                    // Wynik: wszystkie pozycje w 'text' (w kolejności rosnącej),od których zaczyna się 'str

std::vector<int>naive(std::string const & str, std::string const & text);
std::vector<int>KMP(std::string const & str, std::string const & text);
void getKMParray(int array[], std::string const pattern, int array_length);




char randomChar(){
    return 'a'+ rand() % ALPHABET_SIZE;
}

int main(int argc, char** argv){
    srand(time(NULL));
    std::string text;
    std::string pattern;

    for(int i = 0; i<TEXT_LENGTH; ++i){
        text += randomChar();
    }
    for(int i = 0; i<PATTERN_LENGTH; ++i){
        pattern += randomChar();
    }
    std::cout<<text<<std::endl;
    std::cout<<pattern<<std::endl;
/*
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    std::vector<int> found = naive(pattern, text);
    }

    {
    Benchmark<std::chrono::nanoseconds> b(true);
    std::vector<int> found = KMP(pattern, text);
    }
*/
    std::vector<int> found = naive(pattern, text);
    for(int i: found){
        std::cout<<i<<"\t";
    }
    std::cout<<std::endl;
    std::vector<int> found2 = KMP(pattern, text);
    for(int i: found2){
        std::cout<<i<<"\t";
    }
    return 0;


}

std::vector<int>naive(std::string const& pattern, std::string const& text){
    std::vector<int> found_indexes;

    int pattern_length = pattern.size();
    int text_length = text.size();

    if( pattern_length == 0 || text_length == 0){
        return std::move(found_indexes);
    }
    if( pattern_length>text_length){
        return std::move(found_indexes);
    }

    
    for(int i=0; i<text_length-pattern_length+1; ++i){
        int num_of_char_matching =0;
        for(int j=0; j<pattern_length; ++j){

            if(text[i+j] == pattern[j]){
                ++num_of_char_matching;
                if(num_of_char_matching == pattern_length){
                    found_indexes.push_back(i);
                }
            }else{
                break;
            }
        }
    }


    return std::move(found_indexes);
}
std::vector<int>KMP(std::string const & pattern, std::string const & text){
    std::vector<int> found_indexes;
    int pattern_length = pattern.size();
    int text_length = text.size();
    if( pattern_length == 0 || text_length == 0){
        return std::move(found_indexes);
    }
    if( pattern_length>text_length){
        return std::move(found_indexes);
    }

    int kmp_array[pattern_length];
    getKMParray(kmp_array, pattern, pattern_length);

    int i=0, j=0;
    while(i<text_length){
        if( pattern[j] == text[i] ){
            ++i;
            ++j;
        }
        if(j==pattern_length){
            found_indexes.push_back(i-j);
            j = kmp_array[j-1];
        }else if(i<text_length && pattern[j] != text[i]){
            if( j!=0 ){
                j = kmp_array[j-1];
            }else{
                ++i;
            }
        }

    }
    return std::move(found_indexes);
}


void getKMParray(int array[], std::string const pattern, int array_length){
    array[0] = 0;
    //int arrayLength = sizeof(array)/sizeof(array[0]);
    //std::cout<<array_length<<"\t"<<arrayLength<<std::endl;
    int suffix_length = 0;
    for(int i = 1; i<array_length; ++i){
        if(pattern[i] == pattern[suffix_length]){
            ++suffix_length;
            array[i] = suffix_length;
        }else{
            if( suffix_length != 0){
                suffix_length = array[suffix_length-1];
                --i;
            }else{
                array[i] = 0;
            }
        }
    }
}





