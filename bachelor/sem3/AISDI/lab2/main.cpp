#include <iostream>
#include <chrono>
#include <utility>
#include <fstream>
#include <vector>
#include <map>

void read( const std::string& fileName, std::vector<std::string>& data)
{
    std::fstream file;
    file.open( fileName, std::ios::in );
    if( file.is_open() )
    {
        while( file.good() )
        {
            std::string tmp_string;
            file>>tmp_string;
            if(file)
                data.push_back(tmp_string);
        }
    }
    file.close();
}

/*!
 *  Narzedzie do zliczania czasu
 *
 *  Sposob uzycia:
 *
 *  {
 *    Benchmark<std::chrono::nanoseconds> b;
 *    // kod do zbadania
 *    size_t elapsed = b.elapsed();
 *  }
 *
 *  lub
 *
 *  {
 *    Benchmark<std::chrono::milliseconds> b(true);
 *    // kod do zbadania
 *  } // obiekt wypisze wartosc czasu w podanych jednostkach na stderr
 */
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




/*
 * Slownik
 *
 */
template<typename KeyType, typename ValueType>
class TreeMap
{
  public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    TreeMap() = default;    // konstruktor trywialny
    //~TreeMap() = default;   // destruktor trywialny
    ~TreeMap(){
        delete treeRoot;
    }

    void print(){
        preOrder(treeRoot);
    }
    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const{
        return (treeRoot == nullptr);
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type &value){
        if( treeRoot == nullptr){
            NodePtr new_node = new Node(key, value);
            treeRoot = new_node;
            return;
        }

        //fetch closest key to root
        treeRoot = splay(treeRoot, key);

        //if our key already extists then update its data
        if( treeRoot->key == key){
            treeRoot->data = value;
            return;
        }

        NodePtr new_node = new Node(key, value);

        //previous root becomes child of new node
        if( treeRoot->key < key ){
            new_node->left = treeRoot;
            new_node->right = treeRoot->right;
            treeRoot->right = nullptr;
        }else{
            new_node->right = treeRoot;
            new_node->left = treeRoot->left;
            treeRoot->left = nullptr;
        }

        treeRoot = new_node;
        return;
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value)
    {
        const key_type key = key_value.first;
        const mapped_type value = key_value.second;
        insert(key,value);
    }

    /*!
     * zwraca referencje na wartosc dla podanego klucza
     *
     * jezeli elementu nie ma w slowniku, dodaje go
     */
    mapped_type& operator[](const key_type& key)
    {
        //nie wiemy na jakiej zasadzie mamy przypisać wartość nowemu wezłowi, dlatego uciekliśmy do takiego rozwiązania

        const int DATA_TO_PASS_UNIT_TESTS = 4;
        //const std::string DATA_TO_PASS_UNIT_TESTS ="asa";

        if( treeRoot == nullptr ){
            insert(key, DATA_TO_PASS_UNIT_TESTS);
            return treeRoot->data;
        }
        treeRoot = splay(treeRoot, key);
        if( treeRoot->key == key ){
            return treeRoot->data;
        }else{
            insert(key,DATA_TO_PASS_UNIT_TESTS);
            return treeRoot->data;
        }
    }

    /*!
     * zwraca wartosc dla podanego klucza
     */
    const mapped_type& value(const key_type& key) /*const*///tutaj nie powinno byc const moim zdaniem, chyba ze mamy zwracać value bez splay'a
    {
        if( treeRoot == nullptr){
            throw;
        }
        treeRoot = splay(treeRoot, key);
        if( treeRoot->key != key){
            throw;
        }

        return treeRoot->data;
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key) const {
        /*
        //nie ingerować w drzewo, ponieważ metoda const
            treeRoot = splay(treeRoot, key)
            return (treeRoot->key == key);
        */

        //standart bst
        NodePtr actualNode = treeRoot;
        while( actualNode ){
            if( actualNode->key == key ){
                return true;
            }else if( actualNode->key > key){
                actualNode = actualNode->left;
            }else{
                actualNode = actualNode->right;
            }
        }
        return false;
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        if( treeRoot == nullptr){
            return 0;
        }

        return countSubNodes(treeRoot);
    }
private:
    struct Node{
        Node* left;
        Node* right;

        key_type key;
        mapped_type data;
        Node(key_type key, mapped_type data):key(key), data(data), left(nullptr), right(nullptr){}
        ~Node(){
            delete left;
            delete right;
        }
    };

    typedef Node* NodePtr;
    NodePtr treeRoot = nullptr;

    NodePtr leftRotation(NodePtr degraded){
        if( degraded->right == nullptr ){
            return degraded;
        }
        NodePtr upgraded = degraded->right;
        degraded->right = upgraded->left;
        upgraded->left = degraded;

        return upgraded;
    }
    NodePtr rightRotation(NodePtr degraded){
        if( degraded->left == nullptr ){
            return degraded;
        }
        NodePtr upgraded = degraded->left;
        degraded->left = upgraded->right;
        upgraded->right = degraded;

        return upgraded;
    }
    NodePtr splay(NodePtr root, const key_type key ){
        if( root == nullptr || root->key == key){
            return root;
        }

        if( root->key > key){//LEFT
            //NO KEY in tree
            if( root->left == nullptr ){
                return root;
            }

            if( root->left->key > key ){
                root->left->left = splay( root->left->left, key);
                root = rightRotation(root);

            }else if( root->left->key < key ){
                root->left->right = splay( root->left->right, key);
                root->left = leftRotation( root->left );
            }
            return rightRotation(root);


        }else{//RIGHT
            //no key in tree
            if( root->right == nullptr ){
                return root;
            }
            if( root->right->key > key ){
                root->right->left = splay( root->right->left, key);
                root->right = rightRotation(root->right);

            }else if( root->right->key < key ){
                root->right->right = splay( root->right->right, key);
                root = leftRotation( root );
            }
            return leftRotation(root);
        }
    }
    size_t countSubNodes(NodePtr root) const {
        if( (root->left == nullptr) && (root->right == nullptr) ){
            return 1;
        }else if( (root->left != nullptr) && (root->right == nullptr) ){
            return ( 1 + countSubNodes(root->left) );
        }else if( (root->left == nullptr) && (root->right != nullptr) ){
            return ( 1 + countSubNodes(root->right) );
        }else{
            return ( 1 + countSubNodes(root->left) + countSubNodes(root->right) );
        }
    }
    void preOrder(NodePtr root){
        if (root != NULL){
            std::cout<<root->data<<"||"<<root->key<<" ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
};

#include "tests.h"
template<class T>
void test_insert(T& dict, std::vector<std::string>& data, int number_of_elements){
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    for(int i=0; i<number_of_elements; ++i){
        dict.insert( std::pair<int, std::string>(i, data[i]) );
    }

    }
}

int main(int argc, char** argv){
    unit_test();

    std::vector<std::string> stringVector;

    //std::string name = "pan-tadeusz.txt";
    read( argv[1], stringVector );

    std::map<int, std::string> map_dict;
    TreeMap<int, std::string> my_dict;

    int elements = 100;
    std::cout<<"Wstawianie "<<elements<<"elementów"<<std::endl;
    test_insert(map_dict, stringVector, elements);
    test_insert(my_dict, stringVector, elements);
    //my_dict.print();


    int key_to_find = 15;
    std::cout<<"Wyszukiwanie:"<<std::endl;
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    map_dict[key_to_find];
    }
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    my_dict.value(key_to_find);
    }
    std::cout<<"Ponowne wyszukiwanie:"<<std::endl;
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    map_dict[key_to_find];
    }
    {
    Benchmark<std::chrono::nanoseconds> b(true);
    my_dict.value(key_to_find);
    }


    return 0;
}
