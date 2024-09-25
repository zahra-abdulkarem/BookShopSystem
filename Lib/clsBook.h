#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "GeneralFunctions.h"
using namespace std;

string BOOKS__FILE = "../BookShop/core/BooksData.txt";

class clsBook{
    private:

    enum enMode{EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    int _BookID;
    string _BookName;
    string _Author;
    string _Summary;
    string _Publisher;
    float _Price;

    static clsBook _ConvertLineToBookObject(string Line, string Seperator = "<---->"){
        vector <string> vBookData;
        vBookData = General::Split(Line, Seperator);

        return clsBook(enMode::UpdateMode, stoi(vBookData[0]), vBookData[1], vBookData[2],vBookData[3],vBookData[4], stof(vBookData[5]));
    }

    static string _ConvertBookObjectToLine(clsBook Book, string Seperator = "<---->"){
        string stBookRecord = "";
        stBookRecord += to_string(Book.GetBookID()) + Seperator;
        stBookRecord += Book.GetBookName() + Seperator;
        stBookRecord += Book.GetAuthor() + Seperator;
        stBookRecord += Book.GetSummary() + Seperator;
        stBookRecord += Book.GetPublisher() + Seperator;
        stBookRecord += Book.GetPrice();
        return stBookRecord;
    }
    
    static vector <clsBook> _LoadBooksDataFromFile(){
        vector <clsBook> vBooks;
        fstream BookFile;
        BookFile.open(BOOKS__FILE, ios::in);
        if(BookFile.is_open()){
            string Line;
            while(getline(BookFile, Line)){
                clsBook Book = _ConvertLineToBookObject(Line);
                vBooks.push_back(Book);
            }
            BookFile.close();
        }
        return vBooks;
    }
    
    static void _SaveBooksDataToFile(vector <clsBook> vBooks){
        fstream BookFile;
        BookFile.open(BOOKS__FILE, ios::out);
        string DataLine;
        if(BookFile.is_open()){
            for(clsBook C : vBooks){
                DataLine = _ConvertBookObjectToLine(C);
                BookFile << DataLine << endl;
            }
            BookFile.close();
        }
    }


    void _Update(){
        vector <clsBook> _vBooks;
        _vBooks = _LoadBooksDataFromFile();
        for(clsBook &C : _vBooks){
            if(C.GetBookName() == GetBookName()){
                C = *this;
                break;
            }
        }
        _SaveBooksDataToFile(_vBooks);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertBookObjectToLine(*this));
    }

    void _AddDataLineToFile(string DataLine){
        fstream BookFile;
        BookFile.open(BOOKS__FILE, ios::out | ios::app);
        if(BookFile.is_open()){
            BookFile << DataLine << endl;
            BookFile.close();
        }
    }

    
    static clsBook _GetEmptyBookObject(){
        return clsBook(enMode::EmptyMode, 0, "" , "" , "", "", 0);
    }


    public:

    bool IsEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    clsBook(enMode mode , int BookID, string BookName, string Author, string Summary , string Publisher, float Price){
        _Mode = mode;
        _BookID = BookID;
        _BookName = BookName;
        _Author = Author;
        _Summary = Summary;
        _Publisher = Publisher;
        _Price = Price;
    }

    void SetBookName(string BookName){
        _BookName = BookName;
    }

    void SetAuthor(string Author){
        _Author = Author;
    }

    void SetSummary(string Summary){
        _Summary = Summary;
    }

    void SetPublisher(string Publisher){
        _Publisher = Publisher;
    }
    
    void SetPrice(float Price){
        _Price = Price;
    }
    short GetBookID(){
        return _BookID;
    }

    float GetPrice(){
        return _Price;
    }

    string GetBookName(){
        return _BookName;
    }

    string GetAuthor(){
        return _Author;
    }

    string GetSummary(){
        return _Summary;
    }

    string GetPublisher(){
        return _Publisher;
    }


    static clsBook Find(int BookID){
        vector <clsBook> vBooks;
        fstream BookDataFile;
        BookDataFile.open(BOOKS__FILE, ios::in);//read mode
        if(BookDataFile.is_open()){
            string Line;
            while(getline(BookDataFile , Line)){
                clsBook Book = _ConvertLineToBookObject(Line);
                if(Book.GetBookID() == BookID){
                    BookDataFile.close();
                    return Book;
                }
                vBooks.push_back(Book);
            }
            BookDataFile.close();
        }
        return _GetEmptyBookObject();
    }


    static clsBook Find(string BookName){
        vector <clsBook> vBooks;
        fstream BookDataFile;
        BookDataFile.open(BOOKS__FILE, ios::in);
        if(BookDataFile.is_open()){
            string Line;
            while(getline(BookDataFile , Line)){
                clsBook Book = _ConvertLineToBookObject(Line);
                if(Book.GetBookName() == BookName){
                    BookDataFile.close();
                    return Book;
                }
                vBooks.push_back(Book);
            }
            BookDataFile.close();
        }
        return _GetEmptyBookObject();
    }


    enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildBookIDExists};
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
                if(clsBook::IsBookExist(_BookID)){
                    return enSaveResults::svFaildBookIDExists;
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
    
    static bool IsBookExist(int BookID){
        clsBook Book = clsBook::Find(BookID);
        return (!Book.IsEmpty());
    }

    static bool IsBookExist(string BookName){
        clsBook Book = clsBook::Find(BookName);
        return (!Book.IsEmpty());
    }

    bool Delete(){
        vector <clsBook> _vBook;
        _vBook = _LoadBooksDataFromFile();
        for(clsBook &C : _vBook){
            if(C.GetBookName() == _BookName){
                break;
            }
        }
        _SaveBooksDataToFile(_vBook);
        *this = _GetEmptyBookObject();
        return true;
    }
    
    static clsBook GetAddNewBookObject(){
        int BookID = _LoadBooksDataFromFile().size() + 1;
        return clsBook(enMode::AddNewMode, BookID, "", "", "", "", 0);
    }

    static vector <clsBook> GetBooksList(){
        return _LoadBooksDataFromFile();
    }
};
