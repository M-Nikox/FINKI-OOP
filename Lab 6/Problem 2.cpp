#include <iostream>
#include <cstring>

using namespace std;

class Book{
private:
    char *name;
    int *isbn;
    int num_pages;
    void copy(const Book & other){
        this->name = new char [strlen(other.name)+1];
        this->isbn = new int [5];
        this->num_pages=other.num_pages;
        strcpy(this->name, other.name);
        for (int i=0; i<5; i++){
            this->isbn[i]=other.isbn[i];
        }
    }
public:
    Book(){
        this->name=new char[6];
        strcpy(this->name, " EMPTY");
        this->isbn=new int[1];
        this->isbn[0]=-1;
        this->num_pages=-1;
    }

    Book(char *name, int *isbn, int num_pages){
        this->name=new char[strlen(name)+1];
        this->isbn=new int[5];
        this->num_pages=num_pages;
        strcpy(this->name, name);
        for (int i=0; i<5; i++){
            this->isbn[i]=isbn[i];
        }
    }

    bool operator==(const Book & other) const {
        return isbn == other.isbn;
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os << "Title: " << book.name << " ISBN: [ ";
        for (int i=0; i<5; i++) {
            os << book.isbn[i] << " ";
        }
        os<<"]"<<endl;
        return os;
    }

    char *getName() const {
        return name;
    }

    void setName(char *name) {
        Book::name = name;
    }

    int *getIsbn() const {
        return isbn;
    }

    void setIsbn(int *isbn) {
        Book::isbn = isbn;
    }

    int getNumPages() const {
        return num_pages;
    }

    void setNumPages(int numPages) {
        num_pages = numPages;
    }

    ~Book(){

    }
};

class BorrowABook{
private:
    char name[100];
    Book *books;
    int num_books;
    void copy(const BorrowABook & other){
        strcpy(this->name, other.name);
        this->num_books=other.num_books;
        for (int i=0; i<num_books; i++){
            this->books[i]=other.books[i];
        }
    }
public:
    BorrowABook(char name[100]){
        strcpy(this->name, name);
        this->num_books=0;
    }

    BorrowABook & operator+=(const Book & b){
        Book *tmp = new Book[num_books +1];

        for (int i=0; i<num_books; i++){
            tmp[i]=books[i];
        }

        tmp[num_books]=b;
        books=tmp;
        num_books++;

        return *this;
    }

    BorrowABook & operator-=(const Book & b){
        int k=0;
        Book *tmp=new Book[num_books];
        for (int i=0; i<num_books; i++){
            if (books[i].getIsbn() != b.getIsbn()){
                tmp[k++]=books[i];
            }
        }

        if (k==num_books){
            return *this;
        } else{
            delete [] books;
            books=tmp;
            num_books--;
            return *this;
        }
    }

    void printNumberOfPages(int max){
        cout<<name<<endl;
        for (int i=0; i<num_books; i++){
            if (books[i].getNumPages() > max){
                cout<<books[i];
            }
        }
    }

    ~BorrowABook(){
        delete [] books;
    }
};

/// Do NOT edit the main() function
int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int j=0;j<5;j++)
            cin>>isbn[j];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}