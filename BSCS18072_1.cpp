// BSCS18072_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Ad_Hoc Scanner

/*set of alphabets = {a, b, c, ..., x, y, z, A, B, C, ..., X, Y, Z, 0, 1, 2, 3, 4, 5, 6, ., ;,
                    +, -, *, /, % ,< , <=, >, >=, =, ==, !=, &&, ||, [, ], (, ), −−, {, }, ++, <<, >>}

set of identifiers = {w | w is an alpha-numeric words that is at least 2 characters long with
                          at least one capital letter in it but will not start with digits}

set of operators = {+, -, *, /, % ,< , <=, >, >=, =, ==, !=, &&, ||, [, ], (, ), −−, {, }, ++, <<}

 set of keywords = {int, float, double, void, while, for, if, else, char, array, struct, class, break,
                    case, return, cout, cin}

 set of separators = {;}

 set of integers = {w | w is a word of any length that contains only digits 0-6}

 set of string = {w | w is a word that start and ends in inverted commas}

 set of float = {w | w is a word of any length that contains exactly 1 decimal point and digits digits 0=6,
                and does not start or end in decimal point}

 set of M-Comment = {w | w is a string of any length that starts with "/*" and ends with in * / and is not in the same line}

 set of S-Comment = {w | w is a string of any length that starts with // and ends by the end of line}

*/

/*ASSUMPTIONS
1)  semicolon (;) does not fit into the given categories of tokens, so i am going to add a new category
    with the name separator for semicolon.
2)  The inverted commas for the strings will be part of the string when writing output.
3)  I will use tag S-comment for single line comment and M-Comment for multiple line comment
4)  in total I have the following tokens: keyword, identifier, operator, separator, integer, float, string, M-Comment, S-Comment
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

int main() {
    string filename = "code.txt";
    string outputfile = "output.txt";
    ofstream out(outputfile);
    vector<vector<string>> w; // 2d vector to store words in order to record the line numbers as well through indexes
    vector<string> words; // to store words wo one line
    fstream file;
    file.open(filename);
    //reading line by line and storing in a vector to note the line number through indexes.
    string l;
    vector<stringstream> lines;
    while (getline(file, l)) {
        lines.push_back(stringstream(l));
    }

    string word;
    for (int i = 0; i < lines.size(); i++) {
        //separating words by space
        while (getline(lines[i], word, ' ')) {
            // going to separate words that have no white spaces but other separators including all operators
            int j = 0;
            for (int i = 0; i < word.size(); i++) {
                //separating at inverted commas for string
                if (i == 0 && word.size() > 1 && word[i] == '"' && word[word.size() - 1] != '"') {
                    words.push_back(word.substr(0, 1));
                    words.push_back(word.substr(1, word.size() - 1));
                    i = word.size();
                }
                else if (i == 0 && word.size() > 2 && word[i] != '"' && word[(word.size() - 1)] == '"') {
                    words.push_back(word.substr(0, (word.size() - 1)));
                    words.push_back(word.substr((word.size() - 1), 1));
                    i = word.size();
                }
                else if (i == 0 && word.size() > 2 && word[i] == '"' && word[(word.size() - 1)] == '"') {
                    words.push_back(word.substr(0, 1));
                    words.push_back(word.substr(1, (word.size() - 2)));
                    words.push_back(word.substr((word.size() - 1), 1));
                    i = word.size();
                }

                //seprating the single line comment symbol
                else if (i == 0 && word.size() == 2 && word[i] == '/' && word[i + 1] == '/') {
                    words.push_back("//");
                    i = word.size();
                }
                else if (i == 0 && word[i] == '/' && word[i + 1] == '/' && word.size() > 2) {
                    words.push_back("//");
                    words.push_back(word.substr(2, words.size() - 2));
                    i = word.size();
                }

                //separating the multiple line comments symbol
                else if (i == 0 && word[i] == '/' && word[i + 1] == '*' && word.size() > 2) {
                    words.push_back("/*");
                    words.push_back(word.substr(2, words.size() - 2));
                    i = word.size();
                }

                else if (i == 0 && word.size() > 2 && word[word.size() - 2] == '*' && word[word.size() - 1] == '/') {
                    words.push_back(word.substr(0, (word.size() - 2)));
                    words.push_back("*/");
                    i = word.size();
                }
                else if (i == 0 && word.size() == 2 && word[i] == '/' && word[i + 1] == '*') {
                    words.push_back("/*");
                    i = word.size();
                }
                else if (i == 0 && word.size() == 2 && word[i] == '*' && word[i + 1] == '/') {
                    words.push_back("*/");
                    i = word.size();
                }

                //separating double operators
                else if (i < word.size() - 2) {
                    //separating on ++ operator
                    if ((word[i + 1] == '+') && (word[i + 2] == '+')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("++");
                        i++;
                        j = i + 2;
                    }

                    //separating on -- operator
                    else if ((word[i + 1] == '-') && (word[i + 2] == '-')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("--");
                        i++;
                        j = i + 2;
                    }

                    //separating on == operator
                    else if ((word[i + 1] == '=') && (word[i + 2] == '=')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("==");
                        i++;
                        j = i + 2;
                    }

                    //separating on <= operator
                    else if ((word[i + 1] == '<') && (word[i + 2] == '=')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("<=");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '>') && (word[i + 2] == '=')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back(">=");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '!') && (word[i + 2] == '=')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("!=");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '&') && (word[i + 2] == '&')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("&&");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '|') && (word[i + 2] == '|')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("||");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '<') && (word[i + 2] == '<')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back("<<");
                        i++;
                        j = i + 2;
                    }
                    else if ((word[i + 1] == '>') && (word[i + 2] == '>')) {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back(">>");
                        i++;
                        j = i + 2;
                    }
                    else if (word[i + 1] == ';' || word[i + 1] == '+' || word[i + 1] == '-' || word[i + 1] == '*' || word[i + 1] == '/'
                        || word[i + 1] == '%' || word[i + 1] == '<' || word[i + 1] == '>' || word[i + 1] == '=' ||
                        word[i + 1] == '[' || word[i + 1] == ']' || word[i + 1] == '(' || word[i + 1] == ')' || word[i + 1] == '{' ||
                        word[i + 1] == '}') {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back(word.substr(i + 1, 1));
                        i++;
                        j = i + 1;
                    }
                }

                //separating single operators
                else if (i < word.size() - 1) {
                    if (word[i + 1] == ';' || word[i + 1] == '+' || word[i + 1] == '-' || word[i + 1] == '*' || word[i + 1] == '/'
                        || word[i + 1] == '%' || word[i + 1] == '<' || word[i + 1] == '>' || word[i + 1] == '=' ||
                        word[i + 1] == '[' || word[i + 1] == ']' || word[i + 1] == '(' || word[i + 1] == ')' || word[i + 1] == '{' ||
                        word[i + 1] == '}') {
                        words.push_back(word.substr(j, (i + 1) - j));
                        words.push_back(word.substr(i + 1, 1));
                        i++;
                        j = i + 1;
                    }
                }

                //if word has no operator
                if (i == word.size() - 1) {
                    words.push_back(word.substr(j, (i + 1) - j));
                }
            }

        }
        //pushing vector words of words of line i in 2d vector w
        w.push_back(words);
        words.clear();
    }


 //word scannerr

    vector<string> keywords = { "int", "float", "double", "void", "while", "for",
    "if", "else", "char", "array", "struct", "class", "break", "case", "return", "cout", "cin" };

    vector<string> operators = { "+", "-", "*", "/" , "%" , "<" , "<=" , ">", ">=" , "=", "==" , "!=" ,
        "&&", "||" ,"[" ,"]", "(", ")" , "−−", "{", "}", "++", "<<", ">>" };

    bool tokenFound = false;

    //i is the line index/number that i will use in error reporting
    for (int i = 0; i < w.size(); i++) {
        //j is the word index in each line

        for (int j = 0; j < w[i].size(); j++) {
            //cout << "hello j " << j << endl;
            tokenFound = false;


            //checking for semicolon that comes in the token category 'separator'
            if (!tokenFound) {
                if (w[i][j] == ";") {
                    tokenFound = true;
                    //dont need to loop over characters for this because semicolon is in the first place separated individually.
                    out << "\n<separator, " << w[i][j] << ">" << endl;
                }
            }

            //checking for integers
            //using k index to loop over each character in word
            if (!tokenFound) {
                for (int k = 0; k < w[i][j].size(); k++) {
                    if (w[i][j][k] == '0' || w[i][j][k] == '1' || w[i][j][k] == '2' || w[i][j][k] == '3' ||
                        w[i][j][k] == '4' || w[i][j][k] == '5' || w[i][j][k] == '6') {
                        tokenFound = true;
                    }
                    else tokenFound = false;
                    if (!tokenFound) {
                        break;
                    }
                    else if (k == (w[i][j].size() - 1) && tokenFound) {
                        out << "<integer, " << w[i][j] << ">" << endl;
                    }
                }
            }

            //checking for float
            if (!tokenFound) {
                //assumption for floating poing is that it will NOT start or end with decimal 
                bool possible = false; // variable to mark that it is possible that the word is a float or integer
                bool isfloat = false;
                for (int k = 0; k < w[i][j].size(); k++) {
                    //checking for digits before the decimal
                    if (isfloat == false && (w[i][j][k] == '0' || w[i][j][k] == '1' || w[i][j][k] == '2' || w[i][j][k] == '3' ||
                        w[i][j][k] == '4' || w[i][j][k] == '5' || w[i][j][k] == '6'))
                    {
                        possible = true;
                    }

                    //making sure decimal point is not at the start
                    else if (k != 0 && possible == true && isfloat == false && w[i][j][k] == '.')
                    {
                        isfloat = true;
                    }

                    //checking for digits after the decimal
                    else if (isfloat == true && (w[i][j][k] == '0' || w[i][j][k] == '1' || w[i][j][k] == '2' ||
                        w[i][j][k] == '3' || w[i][j][k] == '4' || w[i][j][k] == '5' || w[i][j][k] == '6'))
                    {
                        tokenFound = true;
                    }
                    else
                    {
                        tokenFound == false;
                        k == w[i][j].size() - 1; // will exit this for loop and stop checking for float or int
                    }

                    //if we have reached the end (checked the whole word)
                    if (k == (w[i][j].size() - 1) && tokenFound && isfloat) {
                        out << "<float, " << w[i][j] << ">" << endl;
                        break; // to move to next word
                    }
                }
            }


            //checking for single line comments
            if (!tokenFound) {
                bool isScomment = false;
                if (w[i][j] == "//") { // if the word is "//" that means all words followed by "//" in the same line are included in the comment
                    tokenFound = true;
                    out << "<S-comment, //";
                    for (int k = j + 1; k < w[i].size(); k++) {
                        cout << w[i][k] << " ";
                    }
                    out << ">" << endl;
                }
            }

            //checking for strings
            // assuming string will be only in one line, no one string will continue on next line
            //assuming string will always be in double quotations
            if (!tokenFound) {
                bool isstring = false;
                int end; //to record the index of closing inverted commas
                if (w[i][j][0] == '"') { //if current word is "
                    for (int k = j + 1; k < w[i].size(); k++) { //checking all following words to see when we get " again
                        if (w[i][k][0] == '"') {
                            isstring = true;
                            end = k;
                            k = w[i].size(); // to get out of loop
                        }
                    }
                    if (isstring) {
                        tokenFound = true;
                        out << "<string, ";
                        for (int m = j; m <= end; m++) {
                            out << w[i][m] << " ";
                        }
                        out << ">" << endl;
                    }
                    j = end; // setting j as end so it will check next word in the line i which is after the string
                }
            }

            //checking for identifier

            if (!tokenFound) {
                bool couldBe = false;// to record when i think it could be an identifier
                //ASCII code for A-Z is 65-90 and a-z is 97-122 and 0-6 is 48-54 inclusive
                if (w[i][j].size() > 2 && ((w[i][j][0] >= 65 && w[i][j][0] <= 90) || (w[i][j][0] >= 97 && w[i][j][0] <= 122))) {
                    //if first letter is capital A-Z
                    if (w[i][j][0] >= 65 && w[i][j][0] <= 90) {
                        //starting loop from 1 because I have checked the first character
                        for (int k = 1; k < w[i][j].size(); k++) {
                            //true if if only contains a-z, A-Z, and 0-6
                            if ((w[i][j][k] >= 65 && w[i][j][k] <= 90) || (w[i][j][k] >= 97 && w[i][j][k] <= 122) || (w[i][j][k] >= 48 && w[i][j][k] <= 54)) {
                                tokenFound = true;
                            }
                            //will only enter here if conatins any other letters than either a-z, A-Z, or 0-6
                            else {
                                tokenFound = false;
                                break;
                            }
                        }
                    }
                    //if first character is from a-z
                    else if (w[i][j][0] >= 97 && w[i][j][0] <= 122) {
                        for (int k = 1; k < w[i][j].size(); k++) {
                            //true if if only contains a-z, A-Z, and 0-6
                            if ((w[i][j][k] >= 65 && w[i][j][k] <= 90) || (w[i][j][k] >= 97 && w[i][j][k] <= 122) || (w[i][j][k] >= 48 && w[i][j][k] <= 54)) {
                                couldBe = true;
                            }
                            //will only enter here if conatins any other letters than either a-z, A-Z, or 0-6
                            else {
                                tokenFound = false;
                                break;
                            }
                            if (w[i][j][k] >= 65 && w[i][j][k] <= 90 && couldBe) {
                                tokenFound = true;
                            }
                        }
                    }
                    if (tokenFound) {
                        out << "<identifier, ";
                        out << w[i][j] << ">" << endl;
                    }
                }
            }


            //checking for keywords
            if (!tokenFound) {
                //using index k to loop over each character in a single word
                for (int k = 0; k < keywords.size(); k++) {
                    if (w[i][j] == keywords[k]) {
                        tokenFound = true;
                        out << "<keyword, " << w[i][j] << ">" << endl;;
                        break; // token found we move to next word
                    }
                }
            }

            //checking for operators
            //using k index to loop over the given list of operators
            if (!tokenFound) {
                for (int k = 0; k < operators.size(); k++) {
                    if (w[i][j] == operators[k]) {
                        tokenFound = true;
                        out << "\n<operator, " << w[i][j] << ">" << endl;
                        break; // token found we move to next word
                    }
                }
            }

            //checking for multiple line comments
            if (!tokenFound) {
                bool couldBeComment = false;
                int updatedi = i; // to update index of line after reading the whole multiple line comment
                int updatedj = j; // to update word index 
                bool isMcomment = false;
                if (w[i][j] == "/*") { // if the word is "/*" that means all words followed by "/*" in the same line are included in the comment
                    couldBeComment = true;
                    //now we want to move to next lines and words until we find */
                    //li index is for line i and wi index is for word i
                    //li is starting from i+1 because currently we found /* in line i 
                    for (int li = i + 1; li < w.size(); li++) {
                        for (int wi = 0; wi < w[li].size(); wi++) {
                            if (w[li][wi] == "*/" && couldBeComment) { // this means we have found the end of comment
                                tokenFound = true;
                                //for output
                                out << "<M-Comment, "; // M-Comment token is for multiple comments
                                // storing from same line
                                for (int wi2 = j; wi2 < w[i].size(); wi2++) {
                                    out << w[i][wi2] << " ";
                                }
                                //storing complete next lines minus the last line containing end of comment
                                for (int li2 = i + 1; li2 < li; li2++) {
                                    for (int wi3 = 0; wi3 < w[li2].size(); wi3++) {
                                        out << w[li2][wi3] << " ";
                                    }
                                }
                                for (int wi4 = 0; wi4 <= wi; wi4++) {
                                    out << w[li][wi4] << " ";
                                }
                                out << ">" << endl;
                                updatedi = li;
                                updatedj = wi;
                            }
                            if (tokenFound) break;
                        }
                        if (tokenFound) break;

                    }
                }
                i = updatedi;
                j = updatedj;
            }

            //even after checking for all tokens, you cant fit the word in any category
            if (!tokenFound) {
                cout << "Error in line number " << i+1 << ": Word '" << w[i][j] << "' does not belong to any token category.\n";
            }

        }
    }
    return 0;
}