#include <iostream>
#include <cstring>

using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[30];
    double price;
public:
    Book(){
        strcpy(this->isbn, "NONE");
        strcpy(this->title, "NONE");
        strcpy(this->author, "NONE");
        this->price=0;
    }
    Book(char isbn[20], char title[50], char author[30], double price){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price=price;
    }
    virtual double bookPrice() {
        return price;
    }

    void setISBN(char * isbn) {
        strcpy(this->isbn, isbn);
    }

    friend ostream &operator<<(ostream &os, Book &book) {
        os << book.isbn << ": " << book.title << ", " << book.author << " " << book.bookPrice()<<endl;
        return os;
    }

    bool operator>(Book & other){
        if (this->bookPrice() > other.bookPrice()){
            return true;
        }
    }

};

class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(){
        strcpy(this->isbn, "NONE");
        strcpy(this->title, "NONE");
        strcpy(this->author, "NONE");
        this->url = new char [10];
        strcpy(this->url, "NONE");
        this->price=0;
        this->size=0;
    }

    OnlineBook(char isbn[20], char title[50], char author[30], double price, char *url, int size) : Book(isbn, title, author, price){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price=price;
        this->url=new char[strlen(url)+1];
        strcpy(this->url, url);
        this->size=size;
    }

    double bookPrice() override{
        if (size>20){
            return price*1.20;
        } else return price;
    }

    bool operator>(OnlineBook other){
        if (this->bookPrice() > other.bookPrice()){
            return true;
        } else return false;
    }

    friend ostream &operator<<(ostream &os, OnlineBook book) {
        os << book.isbn << ": " << book.title << ", " << book.author << " " << book.bookPrice()<<endl;
        return os;
    }

};

class PrintBook : public Book{
private:
    double weight;
    bool  in_stock;
public:
    PrintBook(){
        strcpy(this->isbn, "NONE");
        strcpy(this->title, "NONE");
        strcpy(this->author, "NONE");
        this->price=0;
        this->weight=0;
        this->in_stock=false;
    }

    PrintBook(char isbn[20], char title[50], char author[30], double price, double weight, bool in_stock) : Book(isbn, title, author, price){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price=price;
        this->weight=weight;
        this->in_stock=in_stock;
    }

    double bookPrice() override{
        if (weight > 0.7){
            return price * 1.15;
        } else return price;
    }

    bool operator>(PrintBook other){
        if (this->bookPrice() > other.bookPrice()){
            return true;
        } else return false;
    }

    friend ostream &operator<<(ostream &os, PrintBook book) {
        os << book.isbn << ": " << book.title << ", " << book.author << book.bookPrice();
        return os;
    }

};

void mostExpensiveBook (Book** books, int n){
    cout<<"FINKI-Education"<<endl;
    int num_printed_books=0;
    int num_online_books=0;
    int max_index=0;
    for (int i=0; i<n; i++){
        Book *b1 = dynamic_cast<PrintBook*>(books[i]);
        Book *b2 = dynamic_cast<OnlineBook*>(books[i]);
        if (b1){
            num_printed_books++;
        }
        else if (b2){
            num_online_books++;
        }
    }
    cout<<"Total number of online books: "<<num_online_books<<endl;
    cout<<"Total number of print books: "<<num_printed_books<<endl;

    for (int i=0; i<n; i++){
        if (books[max_index]->bookPrice() < books[i]->bookPrice()){
            max_index=i;
        }
    }
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[max_index]<<endl;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
