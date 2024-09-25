#pragma once
#include "clsShowManageBooksScreen.h"
#include "clsShowPurchaseScreen.h"
#include "clsShowManageClientsScreen.h"
#include "clsShowManageUsersScreen.h"
#include "clsScreenStyle.h"
#include "../Global.h"
using namespace std;

class clsMainScreen{

    private:
    static void _PrintMainScreen(){
    clsScreenStyle::_DrawScreenHeader("Main Menu Screen", "Hello Wellcome " + CurrentUser.GetUserName());  
    cout << "[1] Manage Books." << endl;
    cout << "[2] Buy a book." << endl;
    cout << "[3] Manage clients." << endl;
    cout << "[4] Manage users." << endl;
    cout << "[5] Exit." << endl;
    cout << "=================================" << endl;
    cout << "choose what do you want to do? [1 to 5]? ";
    }

    public:
    enum enScreens{ManageBooks = 1,  BuyABook = 2, ManageClients = 3, ManageUsers = 4, Exit = 5};
    
    static void ShowMainMenuScreen(){
        short choise;
        _PrintMainScreen();
        cin >> choise;
    
        switch (enScreens(choise))
        {
        case ManageBooks:
        system("cls");
        clsShowManageBooksScreen::ShowManageBooksScreen();
        break;
        case BuyABook:
        system("cls");
        clsShowPurchaseScreen::ShowPurchaseScreen();
        break;
        case ManageClients:
        system("cls");
        clsShowManageClientsScreen::ShowManageClientsScreen();
        break;
        case ManageUsers:
        system("cls");
        clsShowManageUsersScreen::ShowManageUsersScreen();
        break;
        case Exit:
        system("cls");
        //clsLoginScreen::LogOut();
        break;
        }
    }

};
