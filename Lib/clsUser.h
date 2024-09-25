#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "GeneralFunctions.h"
using namespace std;

string USER__FILE = "../BookShop/core/UserData.txt";

class clsUser{
    private:

    enum enMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _UserName;
    string _Password;
    short _Permissions;
    bool _MarkedForDelete = false;

    static clsUser _ConvertLineToUserObject(string Line, string Seperator = "<---->"){
        vector <string> vUserData;
        vUserData = General::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], stoi(vUserData[2]));
    }

    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "<---->"){
        string stUserRecord = "";
        stUserRecord += User.GetUserName() + Seperator;
        stUserRecord += General::EncryptionText(User.GetPassword()) + Seperator;
        stUserRecord += to_string(User.GetPermissions());
        return stUserRecord;
    }
    
    static vector <clsUser> _LoadUsersDateFromFile(){
        vector <clsUser> vUsers;
        fstream UserFile;
        UserFile.open(USER__FILE, ios::in);//read mode
        if(UserFile.is_open()){
            string Line;
            while(getline(UserFile, Line)){
                clsUser User = _ConvertLineToUserObject(Line);
                vUsers.push_back(User);
            }
            UserFile.close();
        }
        return vUsers;
    }
    
    static void _SaveUsersDataToFile(vector <clsUser> vUsers){
        fstream UserFile;
        UserFile.open(USER__FILE, ios::out);
        string DataLine;
        if(UserFile.is_open()){
            for(clsUser C : vUsers){
                DataLine = _ConvertUserObjectToLine(C);
                UserFile << DataLine << endl;
            }
            UserFile.close();
        }
    }


    void _Update(){
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDateFromFile();
        for(clsUser &C : _vUsers){
            if(C.GetUserName() == GetUserName()){
                C = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string DataLine){
        fstream UserFile;
        UserFile.open(USER__FILE, ios::out | ios::app);
        if(UserFile.is_open()){
            UserFile << DataLine << endl;
            UserFile.close();
        }
    }

    
    static clsUser _GetEmptyUserObject(){
        return clsUser(enMode::EmptyMode, "", "" , 0);
    }


    public:

    enum enMainMenuPermissions{
        eAll = -1, pManageBooks = 1, pBuyBook = 2, pManageClient = 4, pManageUsers = 8, pShowLoginRegester = 16
    };

    bool IsEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    clsUser(enMode mode , string username, string password, short permissions){
        _Mode = mode;
        _UserName = username;
        _Password = password;
        _Permissions = permissions;
    }

    void SetUserName(string username){
        _UserName = username;
    }

    void SetPassword(string Password){
        _Password = Password;
    }

    void SetPermissions(short Permissions){
        _Permissions = Permissions;
    }

    string GetUserName(){
        return _UserName;
    }

    string GetPassword(){
        return _Password;
    }

    short GetPermissions(){
        return _Permissions;
    }

    static clsUser Find(string UserName, string Password){
        vector <clsUser> vUsers;
        fstream UserDataFile;
        UserDataFile.open(USER__FILE, ios::in);//read mode
        if(UserDataFile.is_open()){
            string Line;
            while(getline(UserDataFile , Line)){
                clsUser User = _ConvertLineToUserObject(Line);
                if(User.GetUserName() == UserName && User.GetPassword() == Password){
                    UserDataFile.close();
                    return User;
                }
                vUsers.push_back(User);
            }
            UserDataFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists};
    enSaveResults Save(){
        switch(_Mode){
            case enMode::EmptyMode:
            {
                if(IsEmpty()){
                    return enSaveResults::svFaildEmptyObject;
                }
            }

            case enMode::UpdateMode:
            {
                _Update();
                return enSaveResults::svSucceeded;
                break;
            }

            case enMode::AddNewMode:
            {
                if(clsUser::IsUserExist(_UserName, _Password)){
                    return enSaveResults::svFaildUserNameExists;
                }else{
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
            }
        }
        return enSaveResults::svFaildEmptyObject;
    }
    
    static bool IsUserExist(string UserName, string Password){
        clsUser User1 = clsUser::Find(UserName , Password);
        return (!User1.IsEmpty());
    }

    bool IsUserExist(){
        clsUser User = clsUser::Find(_UserName , _Password);
        return (!User.IsEmpty());
    }

    bool Delete(){
        vector <clsUser> _vUser;
        _vUser = _LoadUsersDateFromFile();
        for(clsUser &C : _vUser){
            if(C.GetUserName() == _UserName){
                C._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUser);
        *this = _GetEmptyUserObject();
        return true;
    }
    
    static clsUser GetAddNewUserObject(string UserName, string Password){
        return clsUser(enMode::AddNewMode, UserName, Password , 0);
    }

    static vector <clsUser> GetUsersList(){
        return _LoadUsersDateFromFile();
    }

    bool CheckAccessPermission(enMainMenuPermissions Permission){
        if(this->_Permissions == enMainMenuPermissions::eAll)
            return true;

        if((Permission & this->_Permissions) == Permission)
            return true;
        else
            return false;
    }

};
