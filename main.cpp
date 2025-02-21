#include <iostream>
#include <fstream>
#include <string> 
#include <cctype>
#include "list.h"
#include "node.h"
#include "timer.h" 

using namespace std;

// Function to clean the word as specified
string cleanWord(string word) {
    string newWord = "";
    int index = 0;
    newWord.reserve(word.size());  // Reserve memory upfront to avoid multiple reallocations
    
    for (char ch : word) {
        // Keep lowercase letters, numbers, and apostrophe
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '\'') {
            newWord += ch;
        }
        // Convert uppercase letters to lowercase and append
        else if (ch >= 'A' && ch <= 'Z') {
            newWord += ch + 32;  // Equivalent to converting to lowercase
        }
    }

/*while(newWord[index] == '\'' && index < newWord.length()){ // Finds the location of any leading '
        index++;
    }

    if (index){ // Gets rid of leading '
        newWord = newWord.substr(index);
}  */


    return newWord;
}

int main() {
    string word;
    myList<string> dictionary;
    long long compare = 0;
                                            int alpha = 0;
    int correctWords = 0;
    int incorrectWords = 0;
    int skippedWords = 0;
    long long correctComparisons = 0;
    long long incorrectComparisons = 0;

    // Open dictionary file (assuming dictionary is a file with words)
    ifstream dictionaryFile("dict.txt");

    // Reading dictionary words into the  linked list
    if (dictionaryFile.is_open()) {
        while (dictionaryFile >> word) {
            word = cleanWord(word); // Clean each word before inserting
            if (!word.empty()) {
                dictionary.insert(word); // Insert cleaned word into dictionary
            }
        }
        dictionaryFile.close();
    } else {
        cerr << "Error: Unable to open dictionary file." << endl;
        return 1;
    }
    //cout << "Dict read" << endl;
    //cout << "Printing dictionary contents: " << endl;
    //dictionary.printList();


    // Timer setup
    Timer Watch;
    Watch.Start();

    // Open book file for spell checking
    ifstream bookFile("book.txt");
    ofstream misspelledFile("misspelled.txt");

    // Checking each word in the book
    if (bookFile.is_open()) {
        while (bookFile >> word) {
            word = cleanWord(word); // Clean the word from the book

            if (!(isalpha(word[0])) && word.empty() == 0) {
                skippedWords++; // Skip empty words
                //cout << "Skipped: " << word << " and >" << word[0] << "< on skipped word: " << skippedWords << " Empty: " << word.empty() << " Isaplpha: " << !(isalpha(word[0])) << "Alpha: " << alpha << endl;
                if(word[0] && isalpha(word[1])){
                    alpha++;
                }
                continue;
            }

            compare = 0; 
            if (dictionary.find(word, compare)) {
                correctWords++;   // Word found in dictionary
                correctComparisons += compare;
            } else if(!(word.empty())) {
                incorrectWords++; // Word not found in dictionary
                incorrectComparisons += compare;
                //cout << "Not dick: " << word << "    on skipped word: " << skippedWords << endl;

                misspelledFile << word << endl; // Write misspelled word to file
            }
        }
        bookFile.close();
    } else {
        cerr << "Error: Unable to open book file." << endl;
        return 1;
    }

    // Stop the timer and calculate the elapsed time
    Watch.Stop();

    // Output the results
    cout << "Dictionary size: " << dictionary.getSize() << endl;
    cout << "Finished in time: " << Watch.Time() << " seconds" << endl;
    cout << "There are " << correctWords << " words found in the dictionary" << endl;
    cout << "  " << correctComparisons << " compares. Average: " << (correctComparisons / correctWords) << endl;
    cout << "There are " << incorrectWords << " words NOT found in the dictionary" << endl;
    cout << "  " << incorrectComparisons << " compares. Average: " << (incorrectComparisons / incorrectWords) << endl;
    cout << "There are " << skippedWords << " words not checked." << endl;

    return 0;
}
