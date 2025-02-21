#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string word = "";

    cout << word[0] << endl;

    cout << !(isalpha(word[0])) << endl;

    cout << (word.empty());

    return 0;
}