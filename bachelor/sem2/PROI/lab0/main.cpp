#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Word{
public:
    Word();
    Word(string pol, string ger): polish(pol), german(ger), knowledge_of_the_word(1) {};
    const string getTranslation(){ return this->polish + " - " + this->german; }
    const string getPolish(){ return this->polish; }
    const string getGerman(){ return this->german; }
    void correctAnswer() { this->knowledge_of_the_word++; }
    void wrongAsnwer() { this->knowledge_of_the_word -= 5; }
private:
    string polish;
    string german;
    int knowledge_of_the_word;
};

class Dictionary{
public:
    void addWord();
    void printDictionary();
    void learn();
    void freeDictionary();
private:
    vector<Word*> list_of_words;
};

void writeDictionary( vector<Word*>& );
void addWord( vector<Word*>& );
void showMenu();
void menu( Dictionary* );

int main()
{
    srand(time(NULL));

    Dictionary* dic = new Dictionary();
    menu(dic);
    //dic->freeDictionary();
    //delete dic;


    return 0;
}

Word::Word(): knowledge_of_the_word(1){
    cout<<"Podaj polskie tlumaczenie:"<<endl;
    cin>>polish;
//nie powtarzac
    cout<<"Podaj niemieckie tlumaczenie:"<<endl;
    cin>>german;
}

void Dictionary::printDictionary(){
    int length = this->list_of_words.size();
    if( length==0 ){
        cout<<"brak slow"<<endl;
        return;
    }
    for( int i=0; i<length; ++i){
        cout<<i+1<<':'<<this->list_of_words[i]->getTranslation()<<endl;
    }
}

void Dictionary::addWord(){
    Word* new_word = new Word();
    this->list_of_words.push_back(new_word);
}

void showMenu(){
    cout<<"Wybierz opcje:"<<endl
    <<"[1]Ucz sie"<<endl
    <<"[2]Dodaj slowo"<<endl
    <<"[3]Wypisz caly slownik"<<endl
    <<"[4]Wyczysc slownik"<<endl
    <<"[0]Wyjdz"<<endl;
}

void menu( Dictionary* dic){
    while(true){
        showMenu();
        int option;
        cin>>option;
        switch(option){
        case 1:
            dic->learn();
            break;
        case 2:
            dic->addWord();
            break;
        case 3:
            dic->printDictionary();
            break;
        case 4:
            dic->freeDictionary();
            break;
        case 0:
            return;

        }
    }
}

void Dictionary::freeDictionary(){
    int length = this->list_of_words.size();
    for(int i = length; i>0; ++i){//blad do gdb
        Word* tmp = list_of_words.back();
        delete tmp;
        list_of_words.pop_back();
    }
}

void Dictionary::learn(){
    int number_of_words = this->list_of_words.size();
    if( !number_of_words ){
        cout<<"Brak slow do nauki"<<endl;
        return;
    }
    string answer;
    cout<<"Tryb uczenia sie, jezeli chcesz zakonczyc to wybierz '0'"<<endl;
    while(true){
        int index = std::rand()%number_of_words;
        cout<<"Podaj tlumaczenie: "<<this->list_of_words[index]->getPolish()<<endl;
        cin>>answer;
        if( answer == "0" ){
        return;
        }
        else if( answer == this->list_of_words[index]->getGerman()){
            cout<<"Prawidlowa odpowiedz!"<<endl;
            this->list_of_words[index]->correctAnswer();
        }
        else{
            cout<<"Blad, poprawna odpowiedz to: "<<this->list_of_words[index]->getGerman()<<endl;
            this->list_of_words[index]->wrongAsnwer();
        }
    }
}
