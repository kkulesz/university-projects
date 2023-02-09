#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue> //fifo
#include <vector>
#include <chrono>

#include "../include/utilities.h"
#include "../include/bruteForce.h"
#include "../include/creatingGroupsWithLast.h"
#include "../include/startFromBeg.h"
#include "../include/fast4Create.h"
#include "../include/popl.hpp"

using namespace std;
using namespace popl;

bool DEBUG;

typedef std::chrono::high_resolution_clock::time_point type_point;
int switchCase(int algorithm, std::vector<int>& data, type_point& begin, type_point& end){
    typedef enum ALGS{CREATING_GROUPS_WITH_LAST=1, FAST_4_CREATE, START_FROM_BEG, BRUTE_FORCE } ALGS;
    int numberOfMoves;
    int bestNumOfMoves;//for bruteForce
    switch (algorithm) {
        case CREATING_GROUPS_WITH_LAST:
            begin = chrono::high_resolution_clock::now();
            numberOfMoves = creatingGroupsWithLast(data, true);
            end = chrono::high_resolution_clock::now();
            break;
        case FAST_4_CREATE:
            begin = chrono::high_resolution_clock::now();
            numberOfMoves = fast4Create(data, true);
            end = chrono::high_resolution_clock::now();
            break;
        case START_FROM_BEG:
            begin = chrono::high_resolution_clock::now();
            numberOfMoves = startFromBeg(data);
            end = chrono::high_resolution_clock::now();
            break;
        case BRUTE_FORCE:
            begin = chrono::high_resolution_clock::now();
            numberOfMoves = bruteForce(data,bestNumOfMoves);
            end = chrono::high_resolution_clock::now();
            std::cout<<"Best possible number of moves: "<<bestNumOfMoves<<"\n";
            break;
        default:
            cout << "Wrong algorithm! Try -a{1,2,3,4}\n";
            return -1;
    }
    return numberOfMoves;
}

void runMode1(int algorithm){

	string input;
	getline(cin, input);

	std::vector<int> data = convertToData( input.c_str(), input.size() );

	auto begin = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
    int numberOfMoves = switchCase(algorithm, data, begin, end);
    if( numberOfMoves < 0){
        return;
    }
	auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Number of moves: " << numberOfMoves << "\n";
	cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
	cout << vToStr(data) << "\n";
}

void runMode2(int algorithm, int problemSize, float generatorParam){

	std::vector<int> data;
	generateData(data, problemSize, (int)(generatorParam*100));

	cout << "Generated input: \n" << vToStr(data) << "\n";

	auto begin = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
    int numberOfMoves = switchCase(algorithm, data, begin, end);
    if( numberOfMoves < 0){
        return;
    }

	auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Number of moves: " << numberOfMoves << "\n";
	cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
	cout << vToStr(data) << "\n";
}

void runMode3(int algorithm, int problemSize, int numberOfStepIterations, int step, int numberOfRuns, float generatorParam){

	std::vector<int> data;

	int maxSize = problemSize + step*numberOfStepIterations + 1;
	for(int size = problemSize; size < maxSize; size+=step){

		for(int run=0; run<numberOfRuns; run++){
			data.clear();
			generateData(data, size, (int)(generatorParam*100));

			auto begin = chrono::high_resolution_clock::now();
			auto end = chrono::high_resolution_clock::now();
			cout << "Size: " << size << "\n";
			int numberOfMoves = switchCase(algorithm, data, begin, end);
            if( numberOfMoves < 0){
                return;
            }

			auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

			cout << "Number of moves: " << numberOfMoves << "\n";
			cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
			cout << vToStr(data) << "\n\n";
		}
	}
}

int main(int argc, char **argv) {
    /*
     * -m 1,2,3
     * -n int
     * -r int
     * -s int
     * -k int
     * -d float
     * -a 1,2,3,4
     * -d int
     * */
    srand(time(nullptr)) ;
	int mode;
	int problemSize;
	int numberOfRuns;
	int step;
	int numberOfStepIterations;
	float generatorParam;
	int algorithm;
	int debug;

	OptionParser op("Allowed options");
	auto help_option = op.add<Switch>
	        ("h", "help", "produce help message");
	auto mode_option = op.add<Value<int>>
	        ("m", "mode", "program mode", 1, &mode);
	auto problemSize_option = op.add<Value<int>>
	        ("n", "size", "problem size", 100, &problemSize);
	auto numberOfStepIterations_option = op.add<Value<int>>
	        ("k", "iterations", "number of step iterations", 5, &numberOfStepIterations);
	auto step_option = op.add<Value<int>>
	        ("s", "step", "step size, increasing problem size", 100, &step);
	auto numberOfRuns_option = op.add<Value<int>>
	        ("r", "runs", "number of problem runs", 25, &numberOfRuns);
	auto generatorParam_option = op.add<Value<float>>
	        ("d", "generator", "generator param", 0.5f, &generatorParam);
	auto algorithm_option = op.add<Value<int>>
	        ("a", "algorithm", "1 - creatingGroupsWithLast,2 - fast4Create", 1, &algorithm);
	auto debug_option = op.add<Value<int>>
	        ("b", "debug","debug mode: 0 - non-debug, other -debug", 0, &debug);

	op.parse(argc, argv);

	if (help_option->count() == 1)
		cout << op << "\n\n";

	if(!algorithm_option->is_set()){
		cout << "This program needs option: -a. Defaulting to -a1\n";
	}

	if(debug){
	    cout<<"Start debug mode!\n";
	    DEBUG=true;
	}

	switch (mode){
		case 1:

			cout << "\n";
			runMode1(algorithm);
			break;

		case 2:
			if(!problemSize_option->is_set()){
				cout << "This mode needs options: -n. Defaulting to -n100\n";
			}
			if(!generatorParam_option->is_set()){
				cout << "This mode needs options: -d. Defaulting to -d0.5\n";
			}

			cout << "\n";
			runMode2(algorithm, problemSize, generatorParam);
			break;

		case 3:
			if(!problemSize_option->is_set()){
				cout << "This mode needs options: -n. Defaulting to -n100\n";
			}
			if(!numberOfStepIterations_option->is_set()){
				cout << "This mode needs options: -k. Defaulting to -k5\n";
			}
			if(!step_option->is_set()){
				cout << "This mode needs options: -step. Defaulting to -step100\n";
			}
			if(!numberOfRuns_option->is_set()){
				cout << "This mode needs options: -r. Defaulting to -r25\n";
			}
			if(!generatorParam_option->is_set()){
				cout << "This mode needs options: -d. Defaulting to -d0.5\n";
			}

			cout << "\n";
			runMode3(algorithm, problemSize, numberOfStepIterations, step, numberOfRuns, generatorParam);
			break;
		default:
			cout << "Wrong mode! Try -m{1,2,3}\n";
			return 1;
	}
    return 0;
}
