#include <iostream>
#include <vector>
#include <fstream>
#include <string>
//#include <queue>
#include <climits>


#define ROW_NUMBER 6
#define COLUMN_NUMBER 6 

void read( const std::string& fileName, std::vector<std::string>& data){
    std::fstream file;
    file.open( fileName, std::ios::in );
    if( file.is_open() ){
        while( file.good() ){
            std::string tmp_string;
            file>>tmp_string;
            if(file)
                data.push_back(tmp_string);
        }
    }
    file.close();
}

void convertToGrid( int grid[ROW_NUMBER][COLUMN_NUMBER], std::vector<std::string>& input){
    for(int i=0; i < ROW_NUMBER; i++){
        for(int j=0; j < COLUMN_NUMBER; j++){
            grid[i][j] = (int)(input[i][j])-48;
        }
    }

}


typedef std::pair<int, int> pair;

/*
first: where the vertex lies in the grid
second: its value by which it is sorted
*/
typedef std::pair< std::pair<int,int>, int > funnyPair;

class MyPriorityQueue{
public:
    ~MyPriorityQueue(){
        Node* tmp = head;
        while(tmp){
            head = head->next;
            delete tmp;
            tmp = head;
        }
    }
    bool isEmpty(){
        return (head == nullptr);
    }
    funnyPair pop(){
        if( isEmpty() ){
            throw;
        }

        funnyPair value = head->value;
        Node* tmp = head;
        head = head->next;

        delete tmp;
        return std::move(value);
    }

    void insert( const funnyPair new_pair){
        Node* newNode = new Node(new_pair);
        if( isEmpty() ){
            head = newNode;
            return;
        }

        //new node has highest priority, add to the beggining
        if( new_pair.second < head->value.second){
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* prev = head;
        Node* curr = head->next;
        while( curr ){

            if( new_pair.second < curr->value.second ){//somewhere in the middle
                prev->next = newNode;
                newNode->next = curr;
                return;
            }
            prev = prev->next;
            curr = curr->next;
        }

        //new node has lowest priority, add to the end
        prev->next = newNode;
    }


    /*
    it will always be called with REALLY updated priority, meaning its priority should be higher
    */
    void updatePriority( const funnyPair updated_pair){
        if( isEmpty() ){
            throw;
        }
        //if head is updated, then just switch its distance(priority)
        if( head->value.first.first == updated_pair.first.first && head->value.first.second == updated_pair.first.second){
            head->value.second = updated_pair.second;
            return;
        }

        int found = false;
        Node* prev = head;
        Node* curr = head->next;

        while ( curr ){

            //if found, then remove its from the current queue and insert it again but with the new(higher) priority
            if( curr->value.first.first == updated_pair.first.first && curr->value.first.second == updated_pair.first.second){
                curr->value.second = updated_pair.second;
                prev->next = curr->next;
                found = true;

                found ? insert(curr->value) : throw;
                delete curr;
                return;
            }

            prev = prev->next;
            curr = curr->next;
        }
    }

private:
    struct Node{
        Node( const funnyPair newPair):next(nullptr), value(newPair){}
        Node* next;
        funnyPair value;
    };


    Node* head = nullptr;
};

bool checkVertex( pair vertex){
    if( vertex.first < 0 || vertex.first >= ROW_NUMBER ){
        return false;
    }
    if( vertex.second < 0 || vertex.second >= COLUMN_NUMBER ){
        return false;
    }

    return true;
}
/*
    updates priority_queue and distane_grid with the new data of the given vertex 
*/
void updateNeighbour(pair neighbour, funnyPair current, int distance_gird[ROW_NUMBER][COLUMN_NUMBER],
                            int grid[ROW_NUMBER][COLUMN_NUMBER], MyPriorityQueue& priority_queue,pair predecessor[ROW_NUMBER][COLUMN_NUMBER]){
    
    int row = current.first.first;
    int col = current.first.second;

    if( checkVertex(neighbour) ){

        if( distance_gird[neighbour.first][neighbour.second] > distance_gird[row][col] + grid[neighbour.first][neighbour.second] ){
                
            distance_gird[neighbour.first][neighbour.second] = distance_gird[row][col] + grid[neighbour.first][neighbour.second];
            predecessor[neighbour.first][neighbour.second] = pair(row,col);
            funnyPair updated_pair ( pair (neighbour.first,neighbour.second), distance_gird[neighbour.first][neighbour.second]);
            priority_queue.updatePriority( updated_pair );    
        }
    }
}



void dijkstra( int grid[ROW_NUMBER][COLUMN_NUMBER], pair source, pair destination, char output[ROW_NUMBER][COLUMN_NUMBER] ){

    if( !checkVertex(source) || !checkVertex(destination) ){
        return;
    }


    int distance_gird[ROW_NUMBER][COLUMN_NUMBER];
    pair predecessor[ROW_NUMBER][COLUMN_NUMBER];
    MyPriorityQueue priority_queue;

    //filling priority queue
    for( int i=0; i< ROW_NUMBER; ++i ){

        for(int j=0; j< COLUMN_NUMBER; j++){
            
            if( i!=0 || j!=0 ){//TUTAJ POPRAWIC
                distance_gird[i][j] = INT_MAX;
            }
            funnyPair fp (pair(i,j), distance_gird[i][j] );
            priority_queue.insert(fp);
        }
    }
    while( !priority_queue.isEmpty() ){

        funnyPair current = priority_queue.pop();
        int row = current.first.first;
        int col = current.first.second;
        if( row == destination.first && col == destination.second ){ //dest found

            int curr_row = row;
            int curr_col = col;
            while( curr_row != source.first || curr_col != source.second ){//fill the output with the path

                int tmp = curr_row;
                curr_row = predecessor[tmp][curr_col].first;
                curr_col = predecessor[tmp][curr_col].second;
                output[curr_row][curr_col] = '1';
            }
            return; //destination found, no need to continue
        }

        pair left (row, col-1 );
        pair right(row, col+1 );
        pair up   (row-1, col );
        pair down (row+1, col );

        updateNeighbour(left,   current, distance_gird, grid, priority_queue, predecessor);
        updateNeighbour(right,  current, distance_gird, grid, priority_queue, predecessor);
        updateNeighbour(up,     current, distance_gird, grid, priority_queue, predecessor);
        updateNeighbour(down,   current, distance_gird, grid, priority_queue, predecessor);

    }
}

int main(int argc, char** argv){
    /*
    MyPriorityQueue queue;
    
    funnyPair fp1 ( std::pair<int,int> (0,0), 4);
    funnyPair fp2 ( std::pair<int,int> (0,1), 2);
    funnyPair fp3 ( std::pair<int,int> (1,1), 0);
    funnyPair fp1_v2 ( std::pair<int,int> (0,0), -1);

    queue.insert(fp1);
    queue.insert(fp2);
    queue.insert(fp3);

    queue.updatePriority( fp1_v2 );

    funnyPair test1 = queue.pop();
    funnyPair test2 = queue.pop();
    funnyPair test3 = queue.pop();
    
    std::cout<< test1.second<<std::endl;
    std::cout<< test2.second<<std::endl;
    std::cout<< test3.second<<std::endl;
    if( queue.isEmpty() ){
        std::cout<<"dupa"<<std::endl;
    }
*/


    //std::cout<<INT_MAX<<std::endl;
    //std::cout<<__TIME__<<std::endl;
    //std::cout<<__STDC__<<std::endl;


    int grid[ROW_NUMBER][COLUMN_NUMBER] = {0};

    std::vector<std::string> input;
    read( argv[1], input );


    convertToGrid(grid, input);
    pair src(0,0);
    pair dest( ROW_NUMBER-1, COLUMN_NUMBER-1);

    char output[ROW_NUMBER][COLUMN_NUMBER];
    for( int i=0; i<ROW_NUMBER; ++i){
        for( int j=0; j<COLUMN_NUMBER;++j){
            output[i][j] = ' ';
        }
    }

    dijkstra(grid, src, dest, output);
    
    output[src.first][src.second] = '0';
    output[dest.first][dest.second] = '0';

    for( int i=0; i<ROW_NUMBER; ++i){
        for( int j=0; j<COLUMN_NUMBER;++j){
            std::cout<<output[i][j];
        }
        std::cout<<std::endl;
    }
    return 0;
}