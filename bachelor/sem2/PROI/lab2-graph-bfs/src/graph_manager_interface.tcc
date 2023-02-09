#include <iostream>
#include <fstream>

void Interface::printOptions(){
    std::cout
            <<"["<<Interface::ADD_VERTEX_<<"] dodaj wierzchołek"<<std::endl
            <<"["<<Interface::ADD_EDGE_<<"] dodaj krawędź"<<std::endl
            <<"["<<Interface::PRINT_VERTEXES_<<"] wypisz wierzchołki"<<std::endl
            <<"["<<Interface::ARE_CONNECTED_<<"] sprawdź czy są połączone"<<std::endl
            <<"["<<Interface::REMOVE_EDGE_<<"] usuń krawędź"<<std::endl
            <<"["<<Interface::READ_FROM_FILE_<<"] wczytaj z pliku"<<std::endl
            <<"["<<Interface::GET_NEIGHBOURS_<<"] wypisz sasiadów"<<std::endl
            <<"["<<Interface::LEAVE_<<"] zakończ"<<std::endl;
}

template<class DataType>
void Interface::manageGraph( Graph<DataType>& graph ){
    int firstIndex, secondIndex;
    printOptions();
    while(true){
        std::cout<<"-----------------"<<std::endl;
        int option = userInputInt_();
        switch(option){
        case Interface::ADD_VERTEX_:{
        //works for graphs containing string only
            std::string input = userInputString_();
            graph.addVertex( input );
        }break;
        case Interface::ADD_EDGE_:{
            userIndexesInput_(firstIndex, secondIndex);
            graph.addEdge(firstIndex, secondIndex);
        }break;
        case Interface::PRINT_VERTEXES_:{
            printVertexes_(graph);
        }break;
        case Interface::ARE_CONNECTED_:{
            userIndexesInput_(firstIndex, secondIndex);
            if( graph.areConnected(firstIndex, secondIndex) )
                std::cout<<"TAK"<<std::endl;
            else
                std::cout<<"NIE"<<std::endl;
        }break;
        case Interface::REMOVE_EDGE_:{
            userIndexesInput_(firstIndex, secondIndex);
            graph.removeEdge(firstIndex, secondIndex);
        }break;
        case Interface::READ_FROM_FILE_:{
        //works for graphs containing string only
            readVertexesFromFile_(graph);
        }break;
        case Interface::GET_NEIGHBOURS_:{
            printNeighbours_(graph);
        }break;
        case Interface::LEAVE_:{
            return;
        }
        default:{
        }break;
        }
    }
}

int Interface::userInputInt_(){
	int input;
	std::cin>>input;

	while(std::cin.fail()){
		std::cin.clear();
		std::cin.ignore();
		std::cin>>input;
	}
	std::cin.clear();

	return input;
}

std::string Interface::userInputString_(){
    std::string input;
    std::cin>>input;

    return input;
}

void Interface::userIndexesInput_(int& firstIndex, int& secondIndex){
    std::cout<<"Podaj pierwszy index:"<<std::endl;
    firstIndex = userInputInt_();
    std::cout<<"Podaj drugi index:"<<std::endl;
    secondIndex = userInputInt_();
}
template<class DataType>
void Interface::printVertexes_( const Graph<DataType> graph){

    int graph_size = graph.getSize();
    if( graph_size == 0){
        return;
    }
    std::cout<<"index: zawarość"<<std::endl;
    for( int i = 0; i<graph_size; ++i){
    std::cout<<i<<": "<<graph[i]<<std::endl;
    }
}

template<class DataType>
void Interface::readVertexesFromFile_( Graph<DataType>& graph ){
    std::cout<<"podaj nazwe pliku:"<<std::endl;
    std::string fileNAme = userInputString_();
    std::ifstream readFile;
    readFile.open( fileNAme );
    if( readFile.is_open() ){
        std::string new_vertex_value;
        while( true ){
            getline( readFile,new_vertex_value );
            if( readFile.eof() ){
                break;
            }
            graph.addVertex(new_vertex_value);
        }

    }else{
        std::cout<<"błąd podczas otwierania pliku"<<std::endl;
    }
    readFile.close();
}

template<class DataType>
void Interface::printNeighbours_( Graph<DataType> graph ){
    std::cout<<"podaj index wierzchołka"<<std::endl;
    int vertexIndex = userInputInt_();
    std::vector<int> graph_neighbours;
    graph.getNeighbours(vertexIndex, graph_neighbours);
    int graph_size = graph_neighbours.size();
    for( int i = 0; i<graph_size; ++i ){
        std::cout<<graph_neighbours[i]<<": "<<graph[graph_neighbours[i]]<<std::endl;
    }
}
