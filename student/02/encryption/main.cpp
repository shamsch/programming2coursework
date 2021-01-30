#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int stringScore(string abc){
    int len = abc.length();
    int sum=0;
    for(int i=0;i<len;i++){
        char a= abc.at(i);
        int val = int(a);
        sum=sum+val;
    }
    //2847
    if(sum==2847){
        return 0;
    }
    else{
        return 1;
    }
}

int checkNumberofCharcters(string abc){
    int len = abc.length();
    if(len==26){
        return 0;
    }
    else{
        return 1;
    }
}

int allSmallCase(string abc){
    int len = abc.length();
    for(int i=0;i<len;i++){
        char a= abc.at(i);
        if (isupper(a)){
            return 1;
        };
    }
    return 0;
}

int main(){
    string encryptionKey,text;
    cout<<"Enter the encryption key: ";
    cin>>encryptionKey;
    if(checkNumberofCharcters(encryptionKey)){
        cout<<"Error! The encryption key must contain 26 characters.";
        return EXIT_FAILURE;
    }
    else if (allSmallCase(encryptionKey)){
        cout<<"Error! The encryption key must contain only lower case characters.";
        return EXIT_FAILURE;
    }
    else if (stringScore(encryptionKey)){
        cout<<"Error! The encryption key must contain all alphabets a-z.";
        return EXIT_FAILURE;
    }
    cout<<"Enter the text to be encrypted: ";
    cin>>text;
    int lengthOfText=text.length();
    for(int i=0; i<lengthOfText; i++){
        char temp = text.at(i);
        int asciiCode= int(temp);
        int positionOnTheString= asciiCode-97;
        char toBeReplacedWith =encryptionKey.at(positionOnTheString);
        text.at(i)= toBeReplacedWith;
    }
    cout<<"Encrypted text: "<<text;
    return 0;
}