#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord{
private:
    char ID[12];
    char name[50];
    double price;
    double mom_price;
    int num_bought;
public:
    StockRecord(char *ID="", char *name="", double price=0, int num_bought=0){
        strcpy(this->ID, ID);
        strcpy(this->name,name);
        this->price=price;
        this->mom_price=0;
        this->num_bought=num_bought;
    }

    void setNewPrice(double c) {
        this->mom_price = c;
    }

    double value(){
        return num_bought*mom_price;
    }

    double profit(){
        return num_bought * (mom_price - price);
    }

    double getMomPrice() const {
        return mom_price;
    }

    friend ostream & operator<<(ostream & os, StockRecord & c){
        os<<c.name<<" "<<c.num_bought<<" "<<c.price<<" "<<c.mom_price<<" "<<c.profit()<<endl;
        return os;
    }

    ~StockRecord(){

    }
};

class Client{
private:
    char namesurname[60];
    int ID;
    int num_companies;
    StockRecord *companies;
public:
    Client(){
        strcpy(this->namesurname, "");
        this->ID=0;
        this->num_companies=0;
        this->companies=new StockRecord[0];
    }

    Client(char *namesurname, int ID, int num_companies, StockRecord *companies){
        strcpy(this->namesurname, namesurname);
        this->ID=ID;
        this->num_companies=num_companies;
        for (int i=0; i<num_companies; i++){
            this->companies=companies;
        }
    }

    Client(char *namesurname, int ID){
        strcpy(this->namesurname,namesurname);
        this->ID=ID;
        this->num_companies=0;
        this->companies = new StockRecord[0];
    }

    double totalValue(){
        double sum=0.0;
        for (int i=0; i<num_companies; i++){
            sum+=companies[i].value();
        }
        return sum;
    }

    Client& operator+=(const StockRecord& that) {
        StockRecord* tmp = new StockRecord[num_companies + 1];
        for(int i = 0; i < num_companies; i++) tmp[i] = this->companies[i];
        tmp[num_companies++] = that;

        delete [] companies;
        this->companies = new StockRecord[num_companies];
        for(int i = 0; i < num_companies; i++) this->companies[i] = tmp[i];
        delete [] tmp;

        return *this;
    }

    friend ostream & operator<<(ostream & os, Client& c){
        os<<c.ID<<" "<<c.totalValue()<<" "<<endl;
        for (int i=0; i<c.num_companies; i++){
            os<<c.companies[i];
        }
        return os;
    }

    ~Client(){
        delete [] companies;
    }
};

// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
    	double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
    	char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
        	cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
    	cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
        	StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
            	cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}