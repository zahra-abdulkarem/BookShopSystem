#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "GeneralFunctions.h"
using namespace std;

string CLIENTS__FILE = "../BookShop/core/ClientsData.txt";

class clsClient{
    private:

    enum enMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    int _ClientID;
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;
    bool _MarkedForDelete = false;

    static clsClient _ConvertLineToClientObject(string Line, string Seperator = "<---->"){
        vector <string> vClient;
        vClient = General::Split(Line, Seperator);

        return clsClient(enMode::UpdateMode, stoi(vClient[0]), vClient[1], vClient[2], vClient[3], vClient[4]);
    }

    static string _ConvertClientObjectToLine(clsClient Client, string Seperator = "<---->"){
        string stClientRecord = "";
        stClientRecord += to_string(Client.GetClientID()) + Seperator;
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone();
        
        return stClientRecord;
    }
    
    static vector <clsClient> _LoadClientsDateFromFile(){
        vector <clsClient> vClients;
        fstream ClientFile;
        ClientFile.open(CLIENTS__FILE, ios::in);
        if(ClientFile.is_open()){
            string Line;
            while(getline(ClientFile, Line)){
                clsClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }
            ClientFile.close();
        }
        return vClients;
    }
    
    static void _SaveClientsDataToFile(vector <clsClient> vClients){
        fstream ClientFile;
        ClientFile.open(CLIENTS__FILE, ios::out);
        string DataLine;
        if(ClientFile.is_open()){
            for(clsClient C : vClients){
                DataLine = _ConvertClientObjectToLine(C);
                ClientFile << DataLine << endl;
            }
            ClientFile.close();
        }
    }


    void _Update(){
        vector <clsClient> _vClients;
        _vClients = _LoadClientsDateFromFile();
        for(clsClient &C : _vClients){
            if(C.GetClientID() == GetClientID()){
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string DataLine){
        fstream ClientFile;
        ClientFile.open(CLIENTS__FILE, ios::out | ios::app);
        if(ClientFile.is_open()){
            ClientFile << DataLine << endl;
            ClientFile.close();
        }
    }

    
    static clsClient _GetEmptyClientObject(){
        return clsClient(enMode::EmptyMode, 0, "" , "", "" , "");
    }


    public:

    bool IsEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    clsClient(enMode mode , int ClientID, string FirstName , string LastName, string Email, string Phone){
        _Mode = mode;
        _ClientID = ClientID;
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    void SetFirstName(string Firstname){
        _FirstName = Firstname;
    }

    void SetLastName(string Lastname){
        _LastName = Lastname;
    }

    void SetEmail(string Email){
        _Email = Email;
    }

    void SetPhone(string Phone){
        _Phone = Phone;
    }

    int GetClientID(){
        return _ClientID;
    }

    string GetFirstName(){
        return _FirstName;
    }

    string GetLastName(){
        return _LastName;
    }

    string GetEmail(){
        return _Email;
    }

    string GetPhone(){
        return _Phone;
    }


    static clsClient Find(int ClientID){
        vector <clsClient> vClients;
        fstream ClientsFile;
        ClientsFile.open(CLIENTS__FILE, ios::in);
        if(ClientsFile.is_open()){
            string Line;
            while(getline(ClientsFile , Line)){
                clsClient Client = _ConvertLineToClientObject(Line);
                if(Client.GetClientID() == ClientID){
                    ClientsFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            ClientsFile.close();
        }
        return _GetEmptyClientObject();
    }


    enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildClientIDExists};
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
                if(clsClient::IsClientExist(_ClientID)){
                    return enSaveResults::svFaildClientIDExists;
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
    
    static bool IsClientExist(int ClientID){
        clsClient Client = clsClient::Find(ClientID);
        return (!Client.IsEmpty());
    }

    bool Delete(){
        vector <clsClient> _vClient;
        _vClient = _LoadClientsDateFromFile();
        for(clsClient &C : _vClient){
            if(C.GetClientID() == _ClientID){
                C._MarkedForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(_vClient);
        *this = _GetEmptyClientObject();
        return true;
    }
    
    static clsClient GetAddNewClientObject(int ClientID){
        return clsClient(enMode::AddNewMode, ClientID, "" , "", "" , "");
    }

    static vector <clsClient> GetClientsList(){
        return _LoadClientsDateFromFile();
    }

};
