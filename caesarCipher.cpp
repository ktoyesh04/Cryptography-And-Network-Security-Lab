#include <iostream>
#include <string>
using namespace std;


void caesar(string &text, int key){
    int chr;
    for(int i=0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            chr = islower(text[i])? 'a':'A';
            text[i] = (text[i] - chr + key + 26) % 26 + chr;
        }
    }
}

int main(){
    string text;
    int key;

    cout << "Enter Text: ";
    getline(cin, text);

    cout << "Enter Key: ";
    cin >> key;

    key = key % 26;

    // encrypt text
    caesar(text, key);

    cout << "Cipher Text: " << text << endl;

    // decrypt text
    caesar(text, -key);

    cout << "Decrypt Cipher Text: " << text;

    return 0;
}
