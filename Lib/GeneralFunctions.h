#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class General{
    public:

    static string DateNow()
    {
	    time_t t = time(0);
	    tm* now = localtime(&t);
        return to_string(now->tm_mday) + " " + to_string(now->tm_mon + 1) + " " + to_string(now->tm_year + 1900);
    }

    static vector<string> Split(string Str, string delim){
        short pos = 0;
        string sWord;
        vector <string> vWords;
        while((pos = Str.find(delim)) != std::string::npos){
            sWord = Str.substr(0, pos);
            vWords.push_back(sWord);
            Str.erase(0, pos + delim.length());
        }
        if(Str != ""){
            vWords.push_back(Str);
        }
        return vWords;
}

    static string EncryptionText(string Text, short EncryptionKey = 17){
        for(int i = 0; i <= Text.length(); i++){
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    } 

    static string DecryptionText(string Text, short EncryptionKey = 17){
        for(int i = 0; i <= Text.length(); i++){
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }

    static string ReadString(string message){
        string S1 = "";
        cout << message;
        getline(cin >> ws , S1);
        return S1;
    }

    template <typename T> static T ReadPositiveNumber(string message){
        T N;
        do{
            cout << message;
            cin >> N;
        }while(N < 0);
        return N;
    }
};