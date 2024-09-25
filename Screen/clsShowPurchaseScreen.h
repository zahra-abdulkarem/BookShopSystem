#pragma once
#include "../Lib/clsBuyABook.h"
#include "../Global.h"
#include "clsScreenStyle.h"

using namespace std;

class clsShowPurchaseScreen : public clsScreenStyle{
    private:
    static void _PrintPurchaseRecordLine(clsBuyABook Purchase){
        cout << "| " << left << setw(7) << Purchase.GetPurchaseID();
        cout << "| " << left << setw(7) << Purchase.GetClientID();
        cout << "| " << left << setw(15) << Purchase.GetUserName();
        cout << "| " << left << setw(37) << Purchase.GetBookName();
        cout << "| " << left << setw(10) << Purchase.GetPurchaseDate();
    }

    static void _ShowPurchasesList(vector <clsBuyABook> vPurchases = clsBuyABook::GetTransactionsList()){
        string Title = "Purchase List Screen";
        string SubTitle = "(" + to_string(vPurchases.size()) + ") Purchase(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "| " << left << setw(7) << "Purchase ID";
        cout << "| " << left << setw(7) << "Client ID";
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(37) << "Book Name";
        cout << "| " << left << setw(10) << "Purchase Date";
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        if(vPurchases.size() == 0){
            cout << "\t\tNo Purchases Available In the System!";
        }else{
            for(clsBuyABook Purchase : vPurchases){
                _PrintPurchaseRecordLine(Purchase);
                cout << endl;
            }
        }
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    }

    static void _ReadPurchaseInfo(clsBuyABook &Purchase){
        Purchase.SetClientID(General::ReadPositiveNumber<int>("enter ClientID: "));
        Purchase.SetUserName(General::ReadString("enter UserName: "));
        Purchase.SetBookName(General::ReadString("enter Book Name: "));
        Purchase.SetPurchaseDate(General::DateNow());
    }
    
    static void _PrintPurchaseCard(clsBuyABook Purchase){
        cout << "\nPurchase Card:";
        cout << "\n - - - - - - - - - - - -  - - - -  - - - - - - -\n";
        cout << "\nPurchase ID  : " << Purchase.GetPurchaseID();
        cout << "\nClient ID    : " << Purchase.GetClientID();
        cout << "\nUserName     : " << Purchase.GetUserName();
        cout << "\nBook Name    : " << Purchase.GetBookName();
        cout << "\nPurchase Date: " << Purchase.GetPurchaseDate();
        cout << "\n - - - - - - - - - -  - - - - - -  - - - - - - -\n";
    }
    
    static void _ShowAddNewPurchaseScreen(){
        _DrawScreenHeader("Add New Purchase Screen\n\n");
        clsBuyABook NewPurchase = clsBuyABook::GetAddNewBuyABookObject();
        _ReadPurchaseInfo(NewPurchase);

        if(NewPurchase.AddNewPurchase()){
            cout << "\nPurchase Addeded Successfuly :-)\n";
        }else{
            cout << "\nError Purchase was not Saved!";
        }
    }

    static void _ShowFindPurchaseScreen(int PurchaseID){
        _DrawScreenHeader("Find Purchase Screen");
        clsBuyABook Purchase = clsBuyABook::Find(PurchaseID);
        _PrintPurchaseCard(Purchase);
    }

    static void _ShowClientPurchaseScreen(){
        int ClientID = General::ReadPositiveNumber<float>("enter ClientID: ");
        vector <clsBuyABook> vPurchases = clsBuyABook::GetClientPurchases(ClientID);
        _ShowPurchasesList(vPurchases);
    }

    static void _ShowUserPurchaseScreen(){
        string UserName = General::ReadString("enter UserName: ");
        vector <clsBuyABook> vPurchases = clsBuyABook::GetUserPurchases(UserName);
        _ShowPurchasesList(vPurchases);
    }

    static short _ManagePurchaseList(){
    short choise;
    cout << "=================================" << endl;
    cout << "           Buy A Book            " << endl;
    cout << "=================================" << endl;
    cout << "[1] show Purchase List." << endl;
    cout << "[2] Add New Purchase." << endl;
    cout << "[3] Find Client Purchase." << endl;
    cout << "[4] Find User Purchase." << endl;
    cout << "[5] Exit." << endl;
    cout << "=================================" << endl;
    cout << "choose what do you want to do? [1 to 5]? ";
    cin >> choise;
    return choise;
    }
    
    

    enum enScreens{PurchaseList = 1, AddNewPurchase = 2, FindClientPurchase = 3,  FindUserPurchase = 4, Exit = 5};
    
    public:
    static void ShowPurchaseScreen(){
        switch (_ManagePurchaseList())
        {
        case PurchaseList:
        system("cls");
        _ShowPurchasesList();
        _GoBackToMainScreen();
        break;
        case AddNewPurchase:
        system("cls");
        _ShowAddNewPurchaseScreen();
        _GoBackToMainScreen();
        break;
        case FindClientPurchase:
        system("cls");
        _ShowClientPurchaseScreen();
        _GoBackToMainScreen();
        break;
        case FindUserPurchase:
        system("cls");
        _ShowUserPurchaseScreen();
        _GoBackToMainScreen();
        break;
        case Exit:
        break;
        }
    }
};
