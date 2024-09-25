#pragma once
#include "../Lib/clsClient.h"
#include "clsScreenStyle.h"
#include "../Global.h"
using namespace std;

class clsShowManageClientsScreen : public clsScreenStyle{
    private:
    static void _PrintClientRecordLine(clsClient Client){
        cout << "| " << left << setw(7) << Client.GetClientID();
        cout << "| " << left << setw(20) << Client.GetFirstName();
        cout << "| " << left << setw(20) << Client.GetLastName();
        cout << "| " << left << setw(15) << Client.GetPhone();
        cout << "| " << left << setw(30) << Client.GetEmail();
    }

    static void _ShowClientsList(){

        vector <clsClient> vClients = clsClient::GetClientsList();
        string Title = "Client List Screen";
        string SubTitle = "(" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "| " << left << setw(7) << "ClientID";
        cout << "| " << left << setw(20) << "First Name";
        cout << "| " << left << setw(20) << "Last Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        if(vClients.size() == 0){
            cout << "\t\tNo Clients Available In the System!";
        }else{
            for(clsClient Client : vClients){
                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    }

    static void _ReadClientInfo(clsClient &Client){
        Client.SetFirstName(General::ReadString("enter FirstName: "));
        Client.SetLastName(General::ReadString("enter LastName: "));
        Client.SetEmail(General::ReadString("enter Email: "));
        Client.SetPhone(General::ReadString("enter Phone: "));
    }
    
    static void _PrintClient(clsClient Client){
        cout << "\nClient Card:";
        cout << "\n - - - - - - - - - - - -  - - - -  - - - - - - -\n";
        cout << "\nClientID     : " << Client.GetClientID();
        cout << "\nFirst Name      : " << Client.GetFirstName();
        cout << "\nLast Name      : " << Client.GetLastName();
        cout << "\nEmail         : " << Client.GetEmail();
        cout << "\nPhone         : " << Client.GetPhone();
        cout << "\n - - - - - - - - - -  - - - - - -  - - - - - - -\n";
    }
    
    static int _ReadClientID(){
        int ClientID = General::ReadPositiveNumber<int>("enter ClientID: ");
        while(!clsClient::IsClientExist(ClientID)){
            cout << "\nClientID is not found , choose anthor one:\n";
            ClientID = General::ReadPositiveNumber<int>("enter ClientID: ");
        }
        return ClientID;
    }

    static void _ShowAddNewClientsScreen(){

        _DrawScreenHeader("Add New Client Screen\n\n");
        int ClientID = clsClient::GetClientsList().size() + 2000;

        clsClient NewClient = clsClient::GetAddNewClientObject(ClientID);
        _ReadClientInfo(NewClient);

        clsClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
        switch(SaveResult){
            case clsClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Addeded Successfuly :-)\n";
                _PrintClient(NewClient);
                break;
            }
            case clsClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Account was not Saved Because it's Empty!";
                break;
            }
            case clsClient::enSaveResults::svFaildClientIDExists:
            {
                cout << "\nError Faild Account Number Exists!\n";
                break;
            }
        }
    }

    static void _ShowUpdateClientsScreen(){

        _DrawScreenHeader("Update Client Screen");
        clsClient Client1 = clsClient::Find(_ReadClientID());
        _PrintClient(Client1);

        cout << "\nAre you sure you want to Update this client y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            cout << "\nUpdate Client Info:";
            cout << "\n__________________________\n";
            _ReadClientInfo(Client1);
        }

        clsClient::enSaveResults SaveResult;
        SaveResult = Client1.Save();
        switch(SaveResult){
            case clsClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfuly :-)\n";
            _PrintClient(Client1);
            break;
            case clsClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError Account was not Saved Because it's Empty!";
            break;
        }
    }

    static void _ShowDeleteClientsScreen(){

        _DrawScreenHeader("Delete Client Screen");
        clsClient Client1 = clsClient::Find(_ReadClientID());
        _PrintClient(Client1);
        cout << "\nAre you sure you want to delete this client y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            if(Client1.Delete()){
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }else{
                cout << "\nError Client Was Not Deleted";
            }
        }
    }

    static void _ShowFindClientScreen(){
        _DrawScreenHeader("Find Client Screen");

        clsClient Client1 = clsClient::Find(_ReadClientID());
        if(!Client1.IsEmpty()){
            cout << "\nClient Is Found :-)\n";
        }else{
            cout << "\n!!Client Is not Found.\n";
        }
        _PrintClient(Client1);
    }

    static void _GoBackToClientScreen(){
        cout << "Click any key to go back to Manage Clients: ";
        system("pause>0");
        ShowManageClientsScreen();
    }

    public:
    enum enScreens{enshowList = 1, enaddnew = 2, enupdate = 3, endelete = 4, enfind = 5, enExite = 6};
    static void ShowManageClientsScreen(){
    if(!CurrentUser.CheckAccessPermission(clsUser::enMainMenuPermissions::pManageClient)){
        return ;
    }

    switch (ManageList("Client"))
    {
        case enshowList:
        system("cls");
        _ShowClientsList();
        _GoBackToClientScreen();
        break;
        case enaddnew:
        system("cls");
        _ShowAddNewClientsScreen();
        _GoBackToClientScreen();
        break;
        case enupdate:
        system("cls");
        _ShowUpdateClientsScreen();
        _GoBackToClientScreen();
        break;
        case endelete:
        system("cls");
        _ShowDeleteClientsScreen();
        _GoBackToClientScreen();
        break;
        case enfind:
        system("cls");
        _ShowFindClientScreen();
        _GoBackToClientScreen();
        break;
        case enExite:
        system("cls");
        _GoBackToMainScreen();
        break;
    }
}
};