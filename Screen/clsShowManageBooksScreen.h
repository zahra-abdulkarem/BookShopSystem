#pragma once
#include "../Lib/clsBook.h"
#include "clsScreenStyle.h"
#include "../Global.h"
using namespace std;

class clsShowManageBooksScreen : public clsScreenStyle{

    private:
    static void _PrintBookRecordLine(clsBook Book){
        cout << "| " << left << setw(5) << Book.GetBookID();
        cout << "| " << left << setw(38) << Book.GetBookName();
        cout << "| " << left << setw(30) << Book.GetAuthor();
        cout << "| " << left << setw(30) << Book.GetPublisher();
        cout << "| " << left << setw(7) << Book.GetPrice();
    }

    static void _ShowBooksListScreen(){

        vector <clsBook> vBooks = clsBook::GetBooksList();
        string Title = "Book List Screen";
        string SubTitle = "(" + to_string(vBooks.size()) + ") Book(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "| " << left << setw(5) << "BookID";
        cout << "| " << left << setw(40) << "Book Name";
        cout << "| " << left << setw(30) << "Author";
        cout << "| " << left << setw(30) << "Publisher";
        cout << "| " << left << setw(7) << "Price";
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        if(vBooks.size() == 0){
            cout << "\t\tNo Books Available In the System!";
        }else{
            for(clsBook Book : vBooks){
                _PrintBookRecordLine(Book);
                cout << endl;
            }
        }
        cout << setw(8) << left << "\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    }
    
    static void _ReadBookInfo(clsBook &Book){
        Book.SetBookName(General::ReadString("Enter Book Name: "));
        Book.SetAuthor(General::ReadString("Enter Author: "));
        Book.SetSummary(General::ReadString("Enter Summary: "));
        Book.SetPublisher(General::ReadString("Enter Publisher: "));
        Book.SetPrice(General::ReadPositiveNumber<float>("Enter Price: "));
    }
    
    static void _PrintBook(clsBook Book){
        cout << "\nBook Card:";
        cout << "\n - - - - - - - - - - - -  - - - -  - - - - - - -\n";
        cout << "\nBookID    : " << Book.GetBookID();
        cout << "\nBook Name : " << Book.GetBookName();
        cout << "\nAuthor    : " << Book.GetAuthor();
        cout << "\nSummary   : " << Book.GetSummary();
        cout << "\nPublisher : " << Book.GetPublisher();
        cout << "\nPrice : " << Book.GetPrice();
        cout << "\n - - - - - - - - - -  - - - - - -  - - - - - - -\n";
    }

    static void _AddNewBookScreen(){

        _DrawScreenHeader("Add New Book Screen\n\n");

        clsBook NewBook = clsBook::GetAddNewBookObject();
        _ReadBookInfo(NewBook);

        clsBook::enSaveResults SaveResult;
        SaveResult = NewBook.Save();
        switch(SaveResult){
            case clsBook::enSaveResults::svSucceeded:
            {
                cout << "\nBook Addeded Successfuly :-)\n";
                _PrintBook(NewBook);
                break;
            }
            case clsBook::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Book was not Saved Because it's Empty!";
                break;
            }
            case clsBook::enSaveResults::svFaildBookIDExists:
            {
                cout << "\nError Faild BookID Exists!\n";
                break;
            }
        }
    }
    
    static void _ShowDeleteBooksScreen(){

        _DrawScreenHeader("Delete Book Screen");
        string BookName = "";
        BookName = General::ReadString("please enter BookName: ");
        while(!clsBook::IsBookExist(BookName)){
            cout << "BookName is not found , choose anthor one:\n";
            BookName = General::ReadString("please enter BookName: ");
        }
        clsBook Book = clsBook::Find(BookName);
        _PrintBook(Book);
        cout << "\nAre you sure you want to delete this Book y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            if(Book.Delete()){
                cout << "\nBook Deleted Successfully :-)\n";
                _PrintBook(Book);
            }else{
                cout << "\nError Book Was Not Deleted";
            }
        }
    }

    static void _ShowFindBookScreen(){
        _DrawScreenHeader("Find Book Screen");
        string BookName;
        cout << "\nPlease Enter Book Name: ";
        cin >> BookName;
        while(!clsBook::IsBookExist(BookName)){
            cout << "\nBook Name Is Not Found,\nChoose Another One: ";
            BookName = General::ReadString("");
        }

        clsBook Book = clsBook::Find(BookName);
        if(!Book.IsEmpty()){
            cout << "\nBook Is Found :-)\n";
        }else{
            cout << "\n!!Book Is not Found.\n";
        }
        _PrintBook(Book);
    }

    static void _ShowUpdateBooksScreen(){

        _DrawScreenHeader("Update Book Screen");
        string BookName = "";
        BookName = General::ReadString("enter BookName: ");
        while(!clsBook::IsBookExist(BookName)){
            cout << "Book Name is not found , choose anthor one:\n";
            BookName = General::ReadString("enter BookName: ");
        }
        clsBook Book = clsBook::Find(BookName);
        _PrintBook(Book);

        cout << "\nAre you sure you want to Update this Book y/n?";
        char Answer = 'n';
        cin >> Answer;
        if(Answer == 'y' || Answer == 'Y'){
            cout << "\nUpdate Book Info:";
            cout << "\n__________________________\n";
            _ReadBookInfo(Book);
        }

        clsBook::enSaveResults SaveResult;
        SaveResult = Book.Save();
        switch(SaveResult){
            case clsBook::enSaveResults::svSucceeded:
            cout << "\nBook Updated Successfuly :-)\n";
            _PrintBook(Book);
            break;
            case clsBook::enSaveResults::svFaildEmptyObject:
            cout << "\nError Book was not Saved Because it's Empty!";
            break;
        }
    }

    static void _GoBackToBooksScreen(){
        cout << "Click any key to go back to Manage Books: ";
        system("pause>0");
        system("cls");
        ShowManageBooksScreen();
    }

    enum enScreens{enshowList = 1, enaddnew = 2, enupdate = 3, endelete = 4, enfind = 5, enExite = 6};
    
    public:
    static void ShowManageBooksScreen(){
        if(!CurrentUser.CheckAccessPermission(clsUser::enMainMenuPermissions::pManageBooks)){
            return ;
        }

    switch (ManageList("Book"))
        {
        case enshowList:
        system("cls");
        _ShowBooksListScreen();
        _GoBackToBooksScreen();
        break;
        case enaddnew:
        system("cls");
        _AddNewBookScreen();
        _GoBackToBooksScreen();
        break;
        case enupdate:
        system("cls");
        _ShowUpdateBooksScreen();
        _GoBackToBooksScreen();
        break;
        case endelete:
        system("cls");
        _ShowDeleteBooksScreen();
        _GoBackToBooksScreen();
        break;
        case enfind:
        system("cls");
        _ShowFindBookScreen();
        _GoBackToBooksScreen();
        break;
        case enExite:
        system("cls");
        _GoBackToMainScreen();
        break;
        default:
        break;
    }
}
};