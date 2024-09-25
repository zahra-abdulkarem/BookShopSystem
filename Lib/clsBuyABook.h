#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsUser.h"
#include "clsClient.h"
#include "clsBook.h"
#include "GeneralFunctions.h"
using namespace std;

string PURCHASE__DATA__FILE = "../BookShop/core/PurchaseData.txt";

class clsBuyABook{
private:
    enum enMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _PurchaseDate = General::DateNow();
    int _PurchaseID = -1;
    int _ClientID = -1;
    string _UserName;
    string _BookName;

    static clsBuyABook _ConvertLineToBuyABookObject(string Line, string Seperator = "<---->"){
        vector <string> vUserData;
        vUserData = General::Split(Line, Seperator);

        return clsBuyABook(stoi(vUserData[0]), stoi(vUserData[1]), vUserData[2] , vUserData[3], vUserData[4]);
    }

    static string _ConvertBuyABookObjectToLine(clsBuyABook Transation, string Seperator = "<---->"){
        string stTransationRecord = "";
        stTransationRecord += to_string(Transation.GetPurchaseID()) + Seperator;
        stTransationRecord += to_string(Transation.GetClientID()) + Seperator;
        stTransationRecord += Transation.GetUserName() + Seperator;
        stTransationRecord += Transation.GetBookName() + Seperator;
        stTransationRecord += Transation.GetPurchaseDate();
        return stTransationRecord;
    }
    
    static vector <clsBuyABook> _LoadPurchaseDateFromFile(){
        vector <clsBuyABook> vPurchases;
        fstream PurchaseFile;
        PurchaseFile.open(PURCHASE__DATA__FILE, ios::in);
        if(PurchaseFile.is_open()){
            string Line;
            while(getline(PurchaseFile, Line)){
                clsBuyABook Purchase = _ConvertLineToBuyABookObject(Line);
                vPurchases.push_back(Purchase);
            }
            PurchaseFile.close();
        }
        return vPurchases;
    }
    
    static void _SavePurchasesDataToFile(vector <clsBuyABook> vPurchases){
        fstream PurchasesFile;
        PurchasesFile.open(PURCHASE__DATA__FILE, ios::out);
        string DataLine;
        if(PurchasesFile.is_open()){
            for(clsBuyABook C : vPurchases){
                DataLine = _ConvertBuyABookObjectToLine(C);
                PurchasesFile << DataLine << endl;
            }
            PurchasesFile.close();
        }
    }

    void _AddDataLineToFile(string DataLine){
        fstream BuyABookFile;
        BuyABookFile.open(PURCHASE__DATA__FILE, ios::out | ios::app);
        if(BuyABookFile.is_open()){
            BuyABookFile << DataLine << endl;
            BuyABookFile.close();
        }
    }

    
    static clsBuyABook _GetEmptyBuyABookObject(){
        return clsBuyABook(-1, -1, "" , "", "" );
    }


    public:

    clsBuyABook(int PurchaseID ,  int ClientID, string Date , string UserName , string BookName){
        _PurchaseID = PurchaseID;
        _PurchaseDate = Date;
        _ClientID = ClientID;
        _UserName = UserName;
        _BookName = BookName;
    }

    void SetPurchaseID(int PurchaseID){
        _PurchaseID = PurchaseID;
    }

    void SetPurchaseDate(string PurchaseDate){
        _PurchaseDate = PurchaseDate;
    }

    void SetUserName(string UserName){
        _UserName = UserName;
    }

    void SetBookName(string BookName){
        _BookName = BookName;
    }

    void SetClientID(int ClientID){
        _ClientID = ClientID;
    }

    int GetClientID(){
        return _ClientID;
    }

    string GetUserName(){
        return _UserName;
    }

    string GetPurchaseDate(){
        return _PurchaseDate;
    }

    string GetBookName(){
        return _BookName;
    }

    int GetPurchaseID(){
        return _PurchaseID;
    }

    static clsBuyABook Find(int PurchaseID){
        vector <clsBuyABook> vPurchaseData;
        fstream PurchaseFile;
        PurchaseFile.open(PURCHASE__DATA__FILE, ios::in);
        if (PurchaseFile.is_open()){
            string Line;
            while(getline(PurchaseFile , Line)){
                clsBuyABook Purchase = _ConvertLineToBuyABookObject(Line);
                if(Purchase.GetPurchaseID() == PurchaseID){
                    PurchaseFile.close();
                    return Purchase;
                }
                vPurchaseData.push_back(Purchase);
            }
            PurchaseFile.close();
        }
        return clsBuyABook(-1 , -1 , "", "", "" );
    }


    static vector<clsBuyABook> GetClientPurchases(int clientID){
        vector<clsBuyABook> CleintPurchaseList;
        vector<clsBuyABook> AllData = GetTransactionsList();
        for(clsBuyABook record : AllData){
            if(record.GetClientID() == clientID){
                CleintPurchaseList.push_back(record);
            }
        }
        return CleintPurchaseList;
    }

    static vector<clsBuyABook> GetUserPurchases(string UserName){
        vector<clsBuyABook> UserPurchaseList;
        vector<clsBuyABook> AllData = GetTransactionsList();
        for(clsBuyABook record : AllData){
            if(record.GetUserName() == UserName){
                UserPurchaseList.push_back(record);
            }
        }
        return UserPurchaseList;
    }

    bool AddNewPurchase(){
        _AddDataLineToFile(_ConvertBuyABookObjectToLine(*this));
        return true;
    }

    bool Delete(){
        vector <clsBuyABook> _vBuyABook;
        _vBuyABook = _LoadPurchaseDateFromFile();
        for(clsBuyABook &C : _vBuyABook){
            if(C.GetPurchaseID() == _PurchaseID){
                break;
            }
        }
        _SavePurchasesDataToFile(_vBuyABook);
        *this = clsBuyABook(-1, -1, "" , "", "");
        return true;
    }
    
    static clsBuyABook GetAddNewBuyABookObject(){
        int PurchaseID = GetTransactionsList().size() + 1;
        return clsBuyABook(PurchaseID, -1, "" , "", "");
    }

    static vector <clsBuyABook> GetTransactionsList(){
        return _LoadPurchaseDateFromFile();
    }

};
