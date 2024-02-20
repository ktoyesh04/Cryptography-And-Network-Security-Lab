#include<stdio.h>
#include<string.h>
#define N 20


void printMatrix(int a[][N], int n){
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}


int power(int i, int j){
    if((i+j)&1==0)
        return 1;
    return -1;
}


int inverseMod(int a, int m){
    int i;
    a = (a%m + m)%m;
    for(i=1; i<m; i++){
        if((a*i)%m == 1)
            return i;
    }
    return 0;
}


void replace(char str[]){
    int i, cnt = 0;
    for(i=0; str[i]!='\0'; i++){
        if(str[i]!=' ')
            str[cnt++] = str[i];
    }
    str[cnt] = '\0';
}


void minor(int row, int col, int k[N][N], int n, int temp[N][N]){
    int i, j, p=0, q=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(i!=row && j!=col){
                temp[p][q] = k[i][j];
                q++;
                if(q==n-1){
                    p++;
                    q=0;
                }
            }
        }
    }
}


int determinant(int k[N][N], int n){
    int i=0, det=0, temp[N][N];
    if(n==1){
        det = k[0][0];
    }
    else if(n==2){
        det = (k[0][0]*k[1][1]) - (k[0][1]*k[1][0]);
    }
    else{
        for(i=0; i<n; i++){
            if(k[0][i] != 0){
                minor(0, i, k, n, temp);
                det += power(i, 0)*k[0][i]*determinant(temp, n-1);
            }
        }
    }
    return det;
}


void multiply(int A[N][N], int B[N], int n, int k){
    int i, j, temp, T[N];
    for(i=0; i<n; i++){
        temp = 0;
        for(j=0; j<n; j++){
            temp += A[i][j] * B[k+j];
        }
        temp = (temp + 26) % 26;
        T[i] = temp;
    }
    for(j=0; j<n; j++){
        B[j+k] = T[j];
    }
}


void inverse(int k[N][N], int k1[N][N], int n){
    int i, j, temp[N][N], d, mul;
    d = determinant(k, n);
    mul = d < 0? -1 : 1;
    d = d < 0?(d*-1) :d;
    mul*= inverseMod(d, 26);
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            minor(i, j, k, n, temp);
            k1[j][i] = power(i, j) * determinant(temp, n-1)*mul;
        }
    }
}


void cipher(char str[], int k[N][N], int mat[], int n){
    int val, i, j;
    replace(str);
    j = strlen(str);
    val = strlen(str)%n;
    if(val != 0){
        for(i=j; i<j+val; i++){
            str[i] = 'A';
        }
    }
    str[j+val] = '\0';

    printf("Plain text: ");
    for(i=0; i<strlen(str); i++){
        if(str[i]>64 && str[i]<91){
            mat[i] = str[i] - 65;
        }
        else{
            mat[i] = str[i]-97;
        }
        printf("%d ", mat[i]);
    }

    for(i=0 ; i<strlen(str); i+=n){
        multiply(k, mat, n, i);
    }

    for(i=0; i<strlen(str); i++){
        printf("%d ", mat[i]);
    }

    for(i=0; i<strlen(str); i++){
        str[i] = (char)(mat[i]+97);
    }

    str[i] = '\0';
}


void decipher(char str[], int k[N][N], int n){
    int k1[N][N], mat[N*6], i;
    inverse(k, k1, n);

    printf("Cipher Text: ");
    for(i=0; i<strlen(str);i++){
        if(str[i] > 64 && str[i] < 91){
            mat[i] = str[i]-65;
        }
        else if(str[i]>96 && str[i]<123){
            mat[i] = str[i]-97;
        }
        printf("%d ", mat[i]);
    }

    for(i=0; i<strlen(str); i+=n){
        multiply(k1, mat, n, i);
    }

    printf("Decipher text: ");
    for(i=0; i<strlen(str); i++){
        printf("%d ", mat[i]);
    }

    for(i=0; i<strlen(str); i++){
        str[i] = (char)(mat[i] + 97);
    }
    str[i] = '\0';
}


int main(){
    int k[N][N], n , val, mat[N*6],i, j;
    char str[N], key[N];

    printf("Enter text: ");
    scanf("%[^\n]s", str);

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter key of length = %d: ", n*n);
    for(i=0; i<n*n; i++){
        scanf("%c", &key[i]);
    }
    key[i] = '\0';

    val = 0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(key[val] > 64 && key[val] < 91){
                k[i][j] = key[val]-65;
            }
            else if(key[val] > 96 && key[val] < 123){
                k[i][j] = key[val] - 97;
            }
            val++;
        }
    }

    printf("\nKey matrix: \n");
    printMatrix(k, n);

    cipher(str, k, mat, n);
    printf("\nCipher test: %s\n\n", str);

    decipher(str, k, n);
    printf("\nDecipher test: %s\n\n", str);
    return 0;
}
