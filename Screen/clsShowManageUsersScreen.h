#pragma once
#include "../Lib/clsUser.h"
#include "clsScreenStyle.h"
#include "../Global.h"
using namespace std;

//--------------------------------------------------------------------------------------------------------------

//                                                  UI Classes

class clsShowManageUsersScreen : public clsScreenStyle{
    private:

    static void _PrintUserRecordLine(clsUser User){
        cout << "| " << left << setw(15) << User.GetUserName();
        cout << "| " << left << setw(10) << User.GetPassword();
        cout << "| " << left << setw(12) << User.GetPermissions();
    }

    static void _ShowUsersList(){
        vector <clsUser> vUsers = clsUser::GetUsersList();
        string Title = "User List Screen";
        string SubTitle = "(" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        if(vUsers.size() == 0){
            cout << "\t\tNo Users Available In the System!";
        }else{
            for(clsUser User : vUsers){
                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    }

    static void _ReadUserInfo(clsUser &User){

        User.SetUserName(General::ReadString("enter UserName: "));
        User.SetPassword(General::ReadString("enter Password: "));
        User.SetPermissions(_ReadPermissionsToSet());
    }
    
    static clsUser _CheckAndFindUserNameAndPassword(){
        string UserName , Password;
        UserName = General::ReadString(">> please enter UserName: ");
        Password = General::ReadString(">> please enter Password: ");
        while(!clsUser::IsUserExist(UserName, Password)){
            cout << "\nUserName or Password is not found,\n choose anthor one:\n";
            UserName = General::ReadString(">> please enter UserName: ");
            Password = General::ReadString(">> please enter Password: ");
        }
        clsUser User = clsUser::Find(UserName , Password);
        return User;
    }

    static void _PrintUser(clsUser User){
        cout << "\nUser Card:";
        cout << "\n - - - - - - - - - - - -  - - - -  - - - - - - -\n";
        cout << "\nUserName   : " << User.GetUserName();
        cout << "\nPassword   : " << User.GetPassword();
        cout << "\nPermissions: " << User.GetPermissions();
        cout << "\n - - - - - - - - - -  - - - - - -  - - - - - - -\n";
    }
    
    static int _ReadPermissionsToSet(){
        int Permissions = 0;
        char Answer = 'n';

        cout << "\t\t\tDo You wnat to give Full acces (y/n) :\n";
        cin >> Answer;
        if(toupper(Answer) == 'Y'){
            return -1;
        }

        cout << "\t\t\tDo You wnat to give acces to :\n";

        cout << "\t\t\tBuy a Book? (y/n) ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
            Permissions += clsUser::enMainMenuPermissions::pBuyBook;


        cout << "\n\t\t\tManage Books? ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
            Permissions += clsUser::enMainMenuPermissions::pManageBooks;
        

        cout << "\n\t\t\tManage Clients? ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
            Permissions += clsUser::enMainMenuPermissions::pManageClient;
        

        cout << "\n\t\t\tManage Users? ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
            Permissions += clsUser::enMainMenuPermissions::pManageUsers;
        

        cout << "\n\t\t\tShow Login Regester? ";
        cin >> Answer;
        if(toupper(Answer) == 'Y')
            Permissions += clsUser::enMainMenuPermissions::pShowLoginRegester;
        
        return Permissions;
    }

    static void _ShowAddNewUserScreen(){
        _DrawScreenHeader("Add New User Screen\n\n");

        clsUser NewUser = clsUser::Find("", "");
        _ReadUserInfo(NewUser);

        while(NewUser.IsUserExist()){
            cout << "User is Already Used, choose anthor one:\n";
            _ReadUserInfo(NewUser);
        }

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();
        switch(SaveResult){
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Addeded Successfuly :-)\n";
                _PrintUser(NewUser);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Account was not Saved Because it's Empty!";
                break;
            }
            case clsUser::enSaveResults::svFaildUserNameExists:
            {
                cout << "\nError Faild Account Number Exists!\n";
                break;
            }
        }
    }

    static void _ShowUpdateUsersScreen(){
        _DrawScreenHeader("Update User Screen");
        clsUser User = _CheckAndFindUserNameAndPassword();
        _PrintUser(User);

        cout << "\nAre you sure you want to Update this User y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            cout << "\nUpdate User Info:";
            cout << "\n_____________________________________________\n";
            _ReadUserInfo(User);
        }

        clsUser::enSaveResults SaveResult;
        SaveResult = User.Save();
        switch(SaveResult){
            case clsUser::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfuly :-)\n";
            _PrintUser(User);
            break;
            case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError Account was not Saved Because it's Empty!";
            break;
        }
    }

    static void _ShowDeleteUsersScreen(){
        _DrawScreenHeader("Delete User Screen");
        clsUser User = _CheckAndFindUserNameAndPassword();
        _PrintUser(User);
        cout << "\nAre you sure you want to delete this User y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            if(User.Delete()){
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }else{
                cout << "\nError User Was Not Deleted";
            }
        }
    }

    static void _ShowFindUserScreen(){
        _DrawScreenHeader("Find User Screen");
        clsUser User = _CheckAndFindUserNameAndPassword();
        _PrintUser(User);
    }

    static void _GoBackToManageUsersScreen(){
        cout << "Click any key to go back to Manage Users: ";
        system("pause>0");
        system("cls");
        ShowManageUsersScreen();
    }

    public:
    static void ShowManageUsersScreen(){
    enum enScreens{enshowList = 1, enaddnew = 2, enupdate = 3, endelete = 4, enfind = 5, enExite = 6};
    switch (ManageList("Users"))
        {

        if(!CurrentUser.CheckAccessPermission(clsUser::enMainMenuPermissions::pManageUsers)){
            return ;
        }

        case enshowList:
        system("cls");
        _ShowUsersList();
        _GoBackToManageUsersScreen();
        break;
        case enaddnew:
        system("cls");
        _ShowAddNewUserScreen();
        _GoBackToManageUsersScreen();
        break;
        case enupdate:
        system("cls");
        _ShowUpdateUsersScreen();
        _GoBackToManageUsersScreen();
        break;
        case endelete:
        system("cls");
        _ShowDeleteUsersScreen();
        _GoBackToManageUsersScreen();
        break;
        case enfind:
        system("cls");
        _ShowFindUserScreen();
        _GoBackToManageUsersScreen();
        break;
        case enExite:
        system("cls");
        ShowManageUsersScreen();
        _GoBackToMainScreen();
        break;
        default:
        break;
    }
}
};
