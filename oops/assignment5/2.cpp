/*
    In a library, for each book book-id, serial number (denotes copy number of a
    book), title, author, publisher and price are stored. Book-id and serial number
    together will be unique identifier for a book. Members are either student or
    faculty. Each member has unique member-id. Name, e-mail, address are also to
    be stored. For any transaction (book issue or return), members are supposed to
    place transactions slip. User will submit member-id, book-id, and serial number
    (only for book return). While processing a transaction, check the validity of the
    member. While issuing, availability of a copy of the book is to be checked. While
    returning a book, it is to be checked whether this copy was issued to the member
    or not. A student member can have 2 books issued at a point of time. For faculty
    members it is 10. Transaction information is to be stored like date of transaction,
    member-id, book-id, serial number, returned or not. An entry is made when book
    is issued and updated when the book is returned.
    Design the classes and implement. For list consider memory data structure.
*/
#include <iostream>
#include <string.h>
using namespace std;

class MEMBER;
class BOOK;
class TRANSACTION;
class LIBRARY;
class MANAGER;

class COPY
{
    int sl_no;
    bool available;
    int issued_to;
    public:
    void setData(int sl_no, bool b)
    {
        this->sl_no = sl_no;
        this->available = b;
        issued_to = 0;
    }

    bool isAvailable()
    {
        return available;
    }

    int getSlNo()
    {
        return sl_no;
    }

    void issue(int mem_id)
    {
        issued_to = mem_id;
        available = 0;
    }

    int issuedTo()
    {
        return issued_to;
    }

    void returnCopy()
    {
        issued_to = 0;
        available = 1;
    }
};

class BOOK
{
    int book_id;
    char title[31];
    char author[31];
    char publisher[31];
    int price;
    COPY list[100];
    int copyCount;
    public:
    void setData(int book_id, char title[], char author[], char publisher[], int price)
    {
        this->book_id = book_id;
        strcpy(this->title, title);
        strcpy(this->author, author);
        strcpy(this->publisher, publisher);
        this->price = price;
        copyCount = 0;
    }

    void addCopies(int amt)
    {
        for (int i = 0; i < amt; i++)
        {
            list[(copyCount++)].setData(copyCount, 1);
        }
    }

    int issueBook(int mem_id)
    {
        for (int i = 0; i < copyCount; i++)
        {
            if (list[i].isAvailable())  
            {
                list[i].issue(mem_id);
                return i + 1;
            }
        }
        return -1;
    }

    int returnBook(int sl_no)
    {
        list[sl_no - 1].returnCopy();
    }

    char *getName()
    {
        return title;
    }

    int issuedTo(int sl_no)
    {
        if (sl_no > copyCount)
        {
            return 0;
        }
        return list[sl_no - 1].issuedTo();
    }
};

class MEMBER
{
    int mem_id;
    bool type;
    int capacity;
    char name[31];
    char email[31];
    char address[1000];
    public:
    void setData(bool type, int id, char name[], char email[], char address[])
    {
        mem_id = id;
        this->type = type;
        if (type == 0) 
        {
            capacity = 2;
        }
        else
        {
            capacity = 10;
        }
        strcpy(this->name, name);
        strcpy(this->email, email);
        strcpy(this->address, address);
    }

    int getCapacity()
    {
        return capacity;
    }

    char *getName()
    {
        return name;
    }

    void issueBook()
    {
        capacity--;
    }

    void returnBook()
    {
        capacity++;
    }
};

class TRANSACTION
{
    char issue_date[20];
    char return_date[20];
    int mem_id;
    int book_id;
    int sl_no;
    bool returned;
    int type;
    public: 
    TRANSACTION()
    {
        strcpy(issue_date, "Not issued");
        strcpy(return_date, "Not returned");
    }

    int getMem_id()
    {
        return mem_id;
    }

    int getBook_id()
    {
        return book_id;
    }

    int getSlNo()
    {
        return sl_no;
    }

    void setData(char date[], int mem_id, int book_id, int sl_no, int type)
    {
        if (type == -1)
        {
            strcpy(this->issue_date, date);
            this->mem_id = mem_id;
            this->book_id = book_id;
            this->sl_no = sl_no;
            this->type = type;
            this->returned = 0;
        }
    }
    
    void setData(char date[])
    {
        strcpy(this->return_date, date);
        this->returned = 1;
    }

    void display()
    {
        cout << "Date issued: " << issue_date << endl;
        cout << "Date returned: " << return_date << endl;
        cout << "Member ID: " << mem_id << endl;
        cout << "Book ID: " << book_id << "\t" << "Serial No.: " << sl_no << endl;
    }
};

class LIBRARY
{
    MEMBER mem_list[500];
    int memCount;
    BOOK book_list[1000];
    int bookCount;
    TRANSACTION history[1000];
    int historyCount;
    public:
    LIBRARY()
    {
        memCount = 0;
        bookCount = 0;
        historyCount = 0;
    }

    void addMember(bool type, char name[], char email[], char address[])
    {
        mem_list[memCount++].setData(type, memCount, name, email, address);
        cout << "Membership Successful!\nYour Member ID is: " << memCount << endl;
    }

    void addBook(char title[], char author[], char publisher[], int price)
    {
        book_list[bookCount++].setData(bookCount, title, author, publisher, price);
        cout << "Book added Successfully!\nThe Book ID is: " << bookCount << endl;
    }

    void addCopies(int id, int amount)
    {
        if (id > bookCount)
        {
            cout << "ERROR: Inavlid book id" << endl;
            return;
        }

        book_list[id - 1].addCopies(amount);
    }

    void issueBook(int mem_id, int book_id, char date[])
    {
        if (mem_id > memCount)
        {
            cout << "ERROR: Inavlid member id" << endl;
            return;
        }

        if (mem_list[mem_id - 1].getCapacity() == 0)
        {
            cout << "Transaction failed: Maximum borrow limit of the member is reached" << endl;
            return;
        }

        if (book_id > bookCount)
        {
            cout << "ERROR: Inavlid book id" << endl;
            return;
        }

        int sl_no = book_list[book_id - 1].issueBook(mem_id);

        if (sl_no == -1) 
        {
            cout << "Transaction failed: No copies of the book available\n";
            return;
        }

        mem_list[mem_id - 1].issueBook();
        
        history[historyCount++].setData(date, mem_id, book_id, sl_no, -1);
        
        cout << "Book issued successfully!" << endl;
        return;
    }

    void returnBook(int mem_id, int book_id, int sl_no, char date[])
    {
        if (mem_id > memCount)
        {
            cout << "ERROR: Inavlid member id" << endl;
            return;
        }

        if (book_id > bookCount)
        {
            cout << "ERROR: Inavlid book id" << endl;
            return;
        }

        if (book_list[book_id - 1].issuedTo(sl_no) != mem_id)
        {
            cout << "ERROR: incorrect serial number" << endl;
        }

        book_list[book_id - 1].returnBook(sl_no);
        mem_list[mem_id - 1].returnBook();

        for (int i = 0; i < historyCount; i++)
        {
            if (history[i].getBook_id() == book_id && history[i].getMem_id() == mem_id && history[i].getSlNo() == sl_no)
            {
                history[i].setData(date);
            }
        }
    }
};

class MANAGER
{
    LIBRARY l;
    public:
    void addMember()
    {
        bool type;
        char name[31];
        char email[31];
        char address[1000];
        cout << "Enter the type of Mebership:\n";
        cout << "1) 0 for Student\n";  
        cout << "2) 1 for Faculty\n";
        cin >> type;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter address: ";
        cin >> address;
        l.addMember(type, name, email, address);
    }
    /*
        book    author  Amount
    1:  a       A       1
    2:  b       B       2
    3:  c       C       3
    4:  d       D       4
    5:  e       E       5
    6:  f       F       6

    1: Arin     0
    2: Parthiv  0
    3: Farhan   0
    4: Dwip     0
    5: urmom    0
    6: SKS      1
    7: CM       1
    */
    void addBook()
    {
        char title[31];
        char author[31];
        char publisher[31];
        int price;
        cout << "Enter the title of the book: ";
        cin >> title;
        cout << "Enter the name of the author: ";
        cin >> author;
        cout << "Enter the name of the publisher: ";
        cin >> publisher;
        cout << "Enter the price of the book: ";
        cin >> price;
        l.addBook(title, author, publisher, price);
    }

    void addCopies()
    {
        int id;
        int amt;
        cout << "Enter the book id: ";
        cin >> id;
        cout << "Enter the number of copies to be added: ";
        cin >> amt;
        l.addCopies(id, amt);
    }

    void issueBook()
    {
        int mem_id;
        int book_id;
        char date[20];
        cout << "Enter Member ID: ";
        cin >> mem_id;
        cout << "Enter Book ID: ";
        cin >> book_id;
        cout << "Enter issue date: ";
        cin >> date;
        l.issueBook(mem_id, book_id, date);
    }

    void returnBook()
    {
        int mem_id;
        int book_id;
        int sl_no;
        char date[20];
        cout << "Enter Member ID: ";
        cin >> mem_id;
        cout << "Enter Book ID: ";
        cin >> book_id;
        cout << "Enter Serial N0: ";
        cin >> sl_no;
        cout << "Enter date: ";
        cin >> date;
        l.returnBook(mem_id, book_id, sl_no, date);
    }
};

int main()
{
    MANAGER m;
    int c;
    while (true)
    {
        cout << "Enter: " << endl;
        cout << "1) 1 to add membership\n";
        cout << "2) 2 to add books\n";
        cout << "3) 3 to add copies of an existing book\n";
        cout << "4) 4 to issue book\n";
        cout << "5) 5 to return an issued book\n";
        cout << "6) 6 to exit\n";
        cin >> c;
        if (c == 6) break;
        switch(c)
        {
            case 1: m.addMember();      break;
            case 2: m.addBook();        break;
            case 3: m.addCopies();      break;
            case 4: m.issueBook();      break;
            case 5: m.returnBook();     break;
            default:                    break;
        }
    }
    return 0;
}