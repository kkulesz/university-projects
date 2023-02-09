#include "graph_manager_interface.h"


int main(){
    Interface graph_manager;
    Graph<std::string> string_graph;

    graph_manager.manageGraph(string_graph);

    return 0;
}
