#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "sanitize.hpp"

using namespace std;

class TextReader {

private:

    map<string, vector<string>> wordFollowers;

public:
    
    void readIn(const string & filename);

    bool isEndPunctuation(const char & character);

    vector<string> getValues(const string & key);

    bool search(const string& key);

    size_t howManyfollowers(const string& key);
    
};

//  TO DO

//  COMPLETE THE FOLLOWING FUNCTIONS


void TextReader::readIn(const string& filename) {
    ifstream _in(filename);
   
    string oldWord = "^";
    string newWord;

    while(_in >> newWord){
        
        sanitize(newWord);
        if (isEndPunctuation(newWord[newWord.size()-1])){

            string punc(1,newWord[newWord.size()-1]);
            string firstpart = newWord.substr(0, newWord.size()-1);;

            wordFollowers[oldWord].push_back(firstpart);
            wordFollowers[firstpart].push_back(punc);
            wordFollowers[punc].push_back("$");

            oldWord = "^";

        }else{
            
            wordFollowers[oldWord].push_back(newWord);
            oldWord = newWord;
        }
        cout << " STILL IN THE LOOP " << endl;
    }
    
  
}


bool TextReader::isEndPunctuation(const char& character) {

    if(character == '.' || character == '?' || character == '!')
       return true;
   return false;


}



vector<string> TextReader::getValues(const string& key) {

    //cout << key << endl;

    return wordFollowers[key];

}



bool TextReader::search(const string& key) {

    map<string, vector<string>>::iterator temp = wordFollowers.find(key);
    if(temp != wordFollowers.end()){
        return true;
    }else{
        return false;
    }

}


size_t TextReader::howManyfollowers(const string& key) {

    return wordFollowers[key].size();

}