#include <iostream>
using namespace std;


int determinant(const int matrix[][2]){
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}



int modularInverse(int x, int m){
    // x and m must be coprimes for modular inverse to exist
    x = x % m;
    for(int i = 1; i < m; i++){
        if((x * i)%m == 1){
            return x;
        }
    }
    return -1;
}


bool inverseExists(const int matrix[][2]){
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
    inv[0][0] = matrix[1][1] * modInvDet;
    inv[0][1] = -matrix[0][1] * modInvDet;
    inv[1][0] = -matrix[1][0] * modInvDet;
    inv[1][1] = matrix[0][0] * modInvDet;
}


string encrypt(string text, int key[][2]){
    int len = text.length();
    
    if(len & 1){
        text.append("x");
        len++;
    }
    string encrypt;
    for(int i=0; i<len; i+=2){
        int ch1 = (char)tolower(text[i]) - 'a';
        int ch2 = (char)tolower(text[i+1]) - 'a';
        int en1 = (ch1*key[0][0] + ch2*key[1][0])%26;
        int en2 = (ch1*key[0][1] + ch2*key[1][1])%26;
        encrypt[i] = en1 + 'a';
        encrypt[i+1] = en2 + 'a';
    }
    
    return encrypt;
}


int main(){
    int key[2][2], modInvDet;
    cout << "Enter Key matrix of order 2: ";
    cin >> key[0][0] >> key[0][1] >> key[1][0] >> key[1][1];

    modInvDet = inverseExists(key);
    if(modInvDet == 0){
        return 0;
    }

    string text;
    cout << "Enter Plain Text: ";
    cin >> text;

    string ans = encrypt(text, key);
    cout << "Encryped: " << ans << endl;

    int inv[2][2];
    inverse(key, inv, modInvDet);

    return 0;
}
