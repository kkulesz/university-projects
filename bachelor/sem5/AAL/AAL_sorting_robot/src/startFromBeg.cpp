//
// Created by Konrad Kulesza on 1/4/2021.
//

#include <iostream>
#include <cmath> //pow()
#include "../include/startFromBeg.h"
#include "../include/utilities.h"

static int Cs = 0, Ms = 0, Ys = 0, Ks = 0;
static int SIZE;

int getNext(std::vector<int>& data, int howManySorted) {
    if(howManySorted<0){
        throw;
    }else if(howManySorted < Cs){
        return C;
    }else if(howManySorted < Cs+Ms){
        return M;
    }else if(howManySorted < Cs+Ms+Ys){
        return Y;
    }else if(howManySorted < Cs+Ms+Ys+Ks){
        return K;
    }else if(howManySorted == Cs+Ms+Ys+Ks){
        return -1;
    }else{
        throw;
    }
}
int getHowManySorted(std::vector<int>& data, int howManySorted){
    //int size = data.size();
    for(int i = howManySorted; i<SIZE; ++i){
        int expectedNext = getNext(data, i);
        if(expectedNext != data[i]){
            return i;
        }
    }
    return SIZE;
}
int find4thPlus1(std::vector<int>& data, int howManySorted, int next){
    int max_iter = (SIZE-howManySorted)/4;
    for(int i = 0; i<max_iter; ++i){
        if( next == data[howManySorted + 4*i]){
            return i;//how many moves we need to make to get this element to the sorted position
        }
    }
    return -1;//we cannot find such element
}
int findPositionOfNext(std::vector<int>& data,int howManySorted,int next){
    int size = SIZE;
    for(int i=howManySorted; i<size;++i){
        if( data[i] == next){
            return i;
        }
    }
    return -1;//0
}
int manipulateEnd(std::vector<int>& data,int howManySorted, int indexOfNext, int& numberOfMoves){
    //int size = data.size();

    while( SIZE-indexOfNext<4 ){
        if(SIZE-1 == indexOfNext){//last
            move4chars(data, indexOfNext-4, numberOfMoves);
            indexOfNext = SIZE-5;
        }else if(SIZE-2 == indexOfNext){
            move4chars(data, indexOfNext-3, numberOfMoves);
            indexOfNext = SIZE-4;
        }else if(SIZE-3 == indexOfNext){
            move4chars(data, indexOfNext-2, numberOfMoves);
            indexOfNext = SIZE-3;
        }else if(SIZE-4 == indexOfNext){
            move4chars(data, indexOfNext-1, numberOfMoves);
            indexOfNext = SIZE-2;
        }

        //little break of the rules

        //in each iteration, it is possible that we will destroy our settlement
        //and that we will find correct position
        howManySorted = getHowManySorted(data, 0);
        int next = getNext(data, howManySorted);
        indexOfNext = findPositionOfNext(data, howManySorted, next);
        int neededMoves = find4thPlus1(data, howManySorted, next);
        if(neededMoves > 0){
            return neededMoves;
        }
    }
    return -1;
}
int manipulateUntil4thPlus1(std::vector<int>& data, int howManySorted, int next, int& numberOfMoves){
    //find position of next element
    int indexOfNext = findPositionOfNext(data, howManySorted, next);

    if(howManySorted == data.size() - 4){
        //heurystyka
        //move4chars(data, indexOfNext - 3 - (rand())%4);
        std::cout<<"manipulateUntil(), niemozliwe dalej posortowac, przy zalozeniu, ze nie przesuwamy posortowanych "<<std::endl;
        return -2;
        //throw;
    }

    if(SIZE - indexOfNext < 4){
        int neededMoves = manipulateEnd(data,howManySorted, indexOfNext, numberOfMoves);
        if(neededMoves>0){
            return neededMoves;
        }
    }

    //after end manipulation, everything could have changed
    howManySorted = getHowManySorted(data, 0);
    next = getNext(data, howManySorted);
    indexOfNext = findPositionOfNext(data, howManySorted, next);

    int offsetEnd = (SIZE - howManySorted)%4;
    int offsetStart = (indexOfNext - howManySorted);//how many elements between sorted element and the one we need to be sorted
    if(offsetStart < 0){
        return -1;//already sorted
    }
    if(offsetEnd == 0){
        move4chars(data, indexOfNext, numberOfMoves);
        return (SIZE-4-howManySorted)/4;
    }else if(offsetEnd == 3){//offsetStart always >0
        move4chars(data, indexOfNext-1, numberOfMoves);
        return (SIZE-3-howManySorted)/4;
    }else if(offsetEnd == 2 && offsetStart>1){
        move4chars(data, indexOfNext-2, numberOfMoves);
        return (SIZE-2-howManySorted)/4;
    }else if(offsetEnd == 1 && offsetStart>2){
        move4chars(data, indexOfNext-3, numberOfMoves);
        return (SIZE-1-howManySorted)/4;
    }

    //if we are there, it means that we are in one of these positions:
    //1st {sorted}| _x__,...,__
    //2nd {sorted}| __x_,...,_
    //3rd {sorted}| _x__,...,_

    //1st takeover
    if(offsetEnd == 2){
        move4chars(data, indexOfNext, numberOfMoves);
        return -1;
    }
    //2nd takeover
    if(offsetEnd==1 && offsetStart==1) {
        move4chars(data, indexOfNext - 1, numberOfMoves);
        return -1;
    }

    //3rd takeover
    if(offsetEnd==1 && offsetStart==2){
        move4chars(data, indexOfNext-2,numberOfMoves);
        return -1;
    }

    std::cout<<"manipulateUntil4thPlus1() throw"<<std::endl;
    throw;
}

int startFromBeg(std::vector<int>& data){
    // count colors
    SIZE = data.size();
    for(int color: data){
        if(color == C){
            ++Cs;
        }else if(color == M) {
            ++Ms;
        }else if(color == Y){
            ++Ys;
        }else if(color == K){
            ++Ks;
        }else{
            throw;
        }
    }
    int howManySorted = getHowManySorted(data, 0);
    int next = getNext(data, howManySorted);
    int numberOfMoves = 0;

    int maxNumOfIterations = pow(data.size(), 1);
    while(--maxNumOfIterations){
        //look for next(should be on (4n+1)th place after howManySorted)
        int neededMoves = find4thPlus1(data, howManySorted, next);

        //if he isn't on (4n+1)th place, then think of how to make him be there
        if(neededMoves < 0){
            neededMoves = manipulateUntil4thPlus1(data, howManySorted, next, numberOfMoves);
        }


        //if he is, then move him to the beginning
        for(int i = 0; i<neededMoves; ++i){
            move4chars(data, howManySorted,numberOfMoves);
        }

        // sorted or impossible to continue
        if(isSorted(data) || neededMoves==-2){
            return numberOfMoves;
        }


        howManySorted = getHowManySorted(data, 0);
        next = getNext(data, howManySorted);

    }
    std::cout<<"Too long, probably inf loop"<<std::endl;
    return -1;
}

