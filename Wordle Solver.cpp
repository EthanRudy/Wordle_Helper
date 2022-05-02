#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
    Filters (by reference) the possible words using a passed word and its code

    @param word of type STD::STRING. The word guessed
    @param code of type STD::STRING. The code returned
*/
void filter(std::vector<std::string>& words, std::string& word, std::string& code);

int main() {
    std::vector<std::string> words;
    std::string line;
    std::ifstream file("5long.txt");
    // Filling the possible words from a text file
    // NOTE: Words are sorted by their frequency
    // SOURCE: https://github.com/dwyl/english-words/blob/master/words.txt
    // I then eliminated any non 5 letter word
    std::cout << "Filling words...\n";
    while (getline(file, line)) {
        words.push_back(line);
    }
    std::cout << "Filled words!";

    // Looping "infinitely"
    while (true) {
        // Getting the guess
        std::string ans = "";
        std::cout << "\nEnter the word guessed: ";
        std::cin >> ans;
        // Getting the code
        std::string code = "";
        std::cout << "Enter code (0 for grey, 1 for yellow, and 2 for green): ";
        std::cin >> code;
        // Breaker
        if (code == "22222") {
            std::cout << "You Found It!";
            return 0;
        }
        // Calling filter function
        filter(words, ans, code);
        // Printing popularity
        std::cout << "Availible words (" << words.size() << "): \n";
        for (int i = 0; i < words.size(); ++i) {
            std::cout << words[i] << ", ";
        }
    }

}


// Filters (by reference) the possible words using a passed word and its code
void filter(std::vector<std::string>& words, std::string& word, std::string& code) {
    // Lopping through the word and the code
    for (int i = 0; i < 5; i++) {
        // Letter doesn't exist
        if (code[i] == '0') {
            for (int index = 0; index < words.size(); ++index) {
                if (words[index].find(word[i]) != std::string::npos) {
                    words.erase(words.begin() + index);
                    --index;
                }
            }
        }
        // Letter exists but in the wrong spot
        else if (code[i] == '1') {
            for (int index = 0; index < words.size(); ++index) {
                bool del = false;
                if (words[index][i] == word[i]) {
                    del = true;
                }
                else if (words[index].find(word[i]) == std::string::npos) {
                    del = true;
                }
                if (del) {
                    words.erase(words.begin() + index);
                    --index;
                }
            }
        }
        // Letter is in the right spot
        else {
            for (int index = 0; index < words.size(); ++index) {
                if (words[index][i] != word[i]) {
                    words.erase(words.begin() + index);
                    --index;
                }
            }
        }
    }
}