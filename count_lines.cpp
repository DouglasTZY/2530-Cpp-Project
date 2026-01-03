#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    ifstream file("main.cpp");
    string line;
    int totalLines = 0;
    int commentOnlyLines = 0;
    int blankLines = 0;
    int codeLines = 0;
    bool inBlockComment = false;
    
    while(getline(file, line)) {
        totalLines++;
        
        // Check for block comment start
        if(line.find("/*") != string::npos) {
            inBlockComment = true;
        }
        
        // Check if line is empty or only whitespace
        bool isBlank = true;
        for(char c : line) {
            if(c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                isBlank = false;
                break;
            }
        }
        
        if(isBlank) {
            blankLines++;
            if(line.find("*/") != string::npos) {
                inBlockComment = false;
            }
            continue;
        }
        
        // Check for single-line comments
        string trimmed = line;
        size_t commentPos = trimmed.find("//");
        
        if(commentPos != string::npos) {
            // Check if it's only a comment
            bool onlyComment = true;
            for(size_t i = 0; i < commentPos; i++) {
                char c = trimmed[i];
                if(c != ' ' && c != '\t') {
                    onlyComment = false;
                    break;
                }
            }
            
            if(onlyComment && commentPos < trimmed.length()) {
                commentOnlyLines++;
                if(line.find("*/") != string::npos) {
                    inBlockComment = false;
                }
                continue;
            }
        }
        
        // Check for block comments
        if(inBlockComment) {
            commentOnlyLines++;
            if(line.find("*/") != string::npos) {
                inBlockComment = false;
            }
            continue;
        }
        
        // It's code
        codeLines++;
    }
    
    cout << "Total Lines: " << totalLines << endl;
    cout << "Blank Lines: " << blankLines << endl;
    cout << "Comment-Only Lines: " << commentOnlyLines << endl;
    cout << "Code Lines: " << codeLines << endl;
    cout << "\nNon-Comment, Non-Blank Lines: " << (totalLines - commentOnlyLines - blankLines) << endl;
    
    return 0;
}
