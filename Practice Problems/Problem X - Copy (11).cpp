#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
private:
    char name[50];
    int year;
    char origin[50];
public:
    Delo(){
        strcpy(this->name, "NONE");
        strcpy(this->origin, "NONE");
        this->year=0;
    }

    Delo(char name[50], int year, char origin[50]){
        strcpy(this->name, name);
        this->year=year;
        strcpy(this->origin, origin);
    }

    bool operator==(const Delo &rhs) const {
        return (!strcmp(this->name, rhs.name));
    }

    bool operator!=(const Delo &rhs) const {
        return !(rhs == *this);
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        Delo::year = year;
    }

    const char *getOrigin() const {
        return origin;
    }
};

class Pretstava{
protected:
    Delo delo;
    int num_sold_cards;
    char date[15];
public:
    Pretstava(){
        this->num_sold_cards=0;
        strcpy(this->date, "NONE");
    }

    Pretstava(Delo delo, int num_sold_cards, char date[15]){
        this->delo=delo;
        this->num_sold_cards=num_sold_cards;
        strcpy(this->date, date);
    }

    virtual int cena() {
        int m = 0;
        int n = 0;
        if (delo.getYear() > 1900){
            m=50;
        } else if (delo.getYear() > 1800 && delo.getYear() < 1900){
            m=75;
        } else if (delo.getYear() <= 1800){
            m=100;
        }

        if (!strcmp(delo.getOrigin(), "Italija")){
            n=100;
        } else  if (!strcmp(delo.getOrigin(), "Rusija")){
            n=150;
        } else{
            n=80;
        }
        return n+m;
    }

    const Delo &getDelo() const {
        return delo;
    }

    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }

    int getNumSoldCards() const {
        return num_sold_cards;
    }

    void setNumSoldCards(int numSoldCards) {
        num_sold_cards = numSoldCards;
    }

    const char *getDate() const {
        return date;
    }
};

class Opera : public Pretstava{
private:
    //nothing?
public:
    Opera(Delo delo, int num_sold_cards, char year[15]) : Pretstava(delo, num_sold_cards, year){
        this->delo=delo;
        this->num_sold_cards=num_sold_cards;
        strcpy(this->date, date);
    }

};

class Balet : public Pretstava{
private:
    static int price;
public:
    Balet(Delo delo, int num_sold_cards, char year[15]) : Pretstava(delo, num_sold_cards, year){
        this->delo=delo;
        this->num_sold_cards=num_sold_cards;
        strcpy(this->date, date);
    }

    static void setCenaBalet(int price);

    int cena() override{
        int balet_cena=Pretstava::cena() + price;
        return balet_cena;
    }

};
int Balet::price = 150;

void Balet::setCenaBalet(int price) {
    Balet::price = price;
}

int prihod(Pretstava **pr, int n){
    int sum=0;
    for (int i=0; i<n; i++){
        sum+=pr[i]->cena() * pr[i]->getNumSoldCards();
    }
    return sum;
}

int brojPretstaviNaDelo(Pretstava **pr, int n, Delo delo){
    int sum=0;
    for (int i=0; i<n; i++){
        if (pr[i]->getDelo() == delo){
            sum++;
        }
    }
    return sum;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
