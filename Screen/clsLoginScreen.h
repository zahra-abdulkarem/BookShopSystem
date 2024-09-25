#pragma once
#include "../Global.h"
#include "clsMainScreen.h"
using namespace std;

class clsLoginScreen{
    private:
    static void _ReadUserInfo(string &UserName , string &Password){
        UserName = General::ReadString("----> Enter UserName: ");
        Password = General::ReadString("----> Enter Password: ");
    }

    public:
    static void ShowLoginScreen(){
        string UserName , Password;
        int TryingChances = 0;
        _ReadUserInfo(UserName, Password);
        CurrentUser = clsUser::Find(UserName, Password);

        while(!CurrentUser.IsEmpty() || TryingChances != 3){
            clsMainScreen::ShowMainMenuScreen();
        }
    }

    static void LogOut(){
        CurrentUser = clsUser::Find("" , "");
        ShowLoginScreen();
    }
};

