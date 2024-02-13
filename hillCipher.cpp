#include <iostream>
using namespace std;

int determinant(const int matrix[][2]){
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

int modularInverse(int x, int m){
    // x and m must be coprimes for modular inverse to exist
    x = (x % m+m)%m;
    for(int i = 1; i < m; i++){
        if((x * i)%m == 1){
            return i;
        }
    }
    return -1;
}

int inverseExists(const int matrix[][2]){
    int det = determinant(matrix);
    if(det == 0){
        cout << "Matrix is not invertible!";
        return 0;
    }

    int modInvDet = modularInverse(det, 26);
    if(modInvDet == -1){
        cout << "Modular Multiplicative Inverse of Matrix Doesn't Exist!";
        return 0;
    }
    return modInvDet;
}

void inverse(int matrix[][2], int inv[][2], int modInvDet){
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(i==j) inv[i][j] = matrix[1-i][1-j] * modInvDet;
            else inv[i][j] = -matrix[i][j] * modInvDet; 
            inv[i][j] = ((inv[i][j]%26)+26)%26;
        }
    }
}

string hill(string text, int key[][2]){
    int len = text.length();
    
    if(len & 1){
        text.append("x");
        len++;
    }
    string text2;
    for(int i=0; i<len; i+=2){
        int ch1 = (char)tolower(text[i]) - 'a';
        int ch2 = (char)tolower(text[i+1]) - 'a';
        int en1 = (ch1*key[0][0] + ch2*key[0][1])%26;
        int en2 = (ch1*key[1][0] + ch2*key[1][1])%26;
        text2 += (en1 + 'a');
        text2 += (en2 + 'a');
    }
    
    return text2;
}

int main(){
    int key[2][2], modInvDet;
    string k;

    cout << "Enter Key(string) of length 4: ";
    cin >> k;
    
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            key[i][j] = k[i*2+j] - 'a';
        }
    }

    modInvDet = inverseExists(key);
    if(modInvDet == 0){
        return 0;
    }

    string text;
    cout << "Enter Plain Text: ";
    cin >> text;

    string cipherText = hill(text, key);
    cout << "Encrypted: " << cipherText << endl;

    int inv[2][2];
    inverse(key, inv, modInvDet);

    string plainText = hill(cipherText, inv);
    cout << "Plain Text: " << plainText << endl;

    return 0;
}
