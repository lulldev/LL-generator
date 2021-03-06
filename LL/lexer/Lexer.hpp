#pragma once

#include <string>
#include <fstream>

using namespace std;

struct LexTokPair {
    string token, lexeme;
};

class Lexer {
public:
    Lexer(string);
    // constructor takes the name of an input file and attempts to open the file
    
    LexTokPair getTokenLexemePair();
    // if file input is valid, returns lexeme-token pair
    
    int findLexemeColumn(char);
    // depending on what the character is, this function returns the corresponding column of the 2D array
    
    bool isInvalid(char);
    // if character is not in the language, returns true
    
    bool isSeparator(char);
    // if character is a separator, returns true
    // this function also checks if the character is a part of the separator "<-"
    
    bool isOperator(char);
    // if character is an operator, returns true
    
    bool isKeyword(string);
    // if the identifier string is a keyword, returns true
    
    bool atEndOfFile();
    // if at end of file, returns true
    
    void closeFile();
    // close file at object level (so that main driver program has access to this feature)
    
private:
    ifstream inFile;
    string machine = ""; // digits/reals (dr) or identifiers (id) machine?
};


/*
 LexTokPair pair;
 string filename;
 ofstream outFile;
 
 // create file to print to
 outFile.open("out.txt");
 
 cout << "Enter input file name: ";
 getline(cin, filename);
 
 Lexer l(filename);
 
 outFile << "Token" << "\t\t\t" << "Lexeme" << endl;
 
 while (!l.atEndOfFile()) {
 pair = l.getTokenLexemePair();
 outFile << pair.token << setw(18) << pair.lexeme << endl;
 }
 
 // close files
 l.closeFile(); // input file
 outFile.close(); // output file
 */
