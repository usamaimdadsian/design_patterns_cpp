/*
    IMPLEMENT YOUR INTERFACES SO THAT IMPLEMENTATION CAN PICK AND CHOOSE ACCORDING TO THEIR NEED.

    the idea here is to segregate parts of a complicated
    interface into separate interfaces so as to avoid forcing implementers to
    implement functionality that they do not really need.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Document
{
    /* data */
};

// struct IMachine{
//     virtual void print(vector<Document *> docs) = 0;
//     virtual void fax(vector<Document *> docs) = 0;
//     virtual void scan(vector<Document *> docs) = 0;

// };

// struct MyFavouritePrinter: IMachine {
//     void print(vector<Document *> docs) override;
//     void fax(vector<Document *> docs) override;
//     void scan(vector<Document *> docs) override;
// };

struct IPrinter
{
    virtual void print(vector<Document *> docs) = 0;
};
struct IScanner
{
    virtual void scan(vector<Document *> docs) = 0;
};
struct IFax
{
    virtual void fax(vector<Document *> docs) = 0;
};
struct IMachine : IPrinter, IScanner, IFax
{
};




struct Printer : IPrinter
{
    void print(vector<Document *> docs) override;
};

struct Scanner : IScanner
{
    void scan(vector<Document *> docs) override;
};

struct Photocopier : IPrinter, IScanner
{
    void print(vector<Document *> docs) override;
    void scan(vector<Document *> docs) override;
};

struct Machine : IMachine
{
    IPrinter &printer;
    IScanner &scanner;
    IFax &faxMachine;

    Machine(IPrinter &printer, IScanner &scanner, IFax &fax) : printer{printer}, scanner{scanner}, faxMachine{fax} {}

    void print(vector<Document *> docs) override
    {
        printer.print(docs);
    }

    void scan(vector<Document *> docs) override
    {
        scanner.scan(docs);
    }
    void fax(vector<Document *> docs) override
    {
        faxMachine.fax(docs);
    }
};

int main()
{
    
}