#pragma once
#include <iostream>
#include <string.h>
#include "clsMainScreen.h"
using namespace std;

class clsScreenStyle{
    public:
    static void _DrawScreenHeader(string Title, string SubTitle=""){
        cout << "\t\t\t====================================================="<<endl;
        cout << "\t\t\t\t\t\t" << Title <<endl;
        cout << "\t\t\t\t\t" << SubTitle <<endl;
        cout << "\t\t\t====================================================="<<endl;

    }

    static short ManageList(string title){
    short choise;
    cout << "=================================" << endl;
    cout << "      Manage " << title << " Screen        " << endl;
    cout << "=================================" << endl;
    cout << "[1] "<<  title <<" List." << endl;
    cout << "[2] Add New "<<  title <<"." << endl;
    cout << "[3] Update "<<  title <<"." << endl;
    cout << "[4] Delete "<<  title <<"." << endl;
    cout << "[5] Find "<<  title <<"." << endl;
    cout << "[6] Exit." << endl;
    cout << "=================================" << endl;
    cout << "choose what do you want to do? [1 to 6]? ";
    cin >> choise;
    return choise;
    }

    static void _GoBackToMainScreen(){
        cout << "Click any key to go back to Manage Users: ";
        system("pause>0");
        system("cls");
        //clsMainScreen::ShowMainMenuScreen();
    }
};