#include <iostream>
#include <cstring>

using namespace std;

class Gitara{
private:
    char serial[25];
    float price;
    int year;
    char type[40];
public:
    Gitara(){
        strcpy(this->serial,"");
        this->price=0;
        this->year=0;
        strcpy(this->type,type);
    }

    Gitara(char *type, char *serial, int year, float price){
        strcpy(this->serial, serial);
        this->price=price;
        this->year=year;
        strcpy(this->type,type);
    }

    bool daliIsti(Gitara gitara){
        if (!strcmp(this->serial,gitara.serial)){
            return true;
        }
        else {
            return false;
        }
    }

    const char *getSeriski() const {
        return serial;
    }

    float getNabavna() const {
        return price;
    }

    int getGodina() const {
        return year;
    }

    Gitara & operator=(const Gitara & other){
        if (this == & other){
            return *this;
        } else{
            strcpy(this->serial, other.serial);
            strcpy(this->type, other.type);
            this->price=other.price;
            this->year=other.year;
        }
        return *this;
    }

    const char *getTip() const {
        return type;
    }

    void pecati(){
        cout<<serial<<" "<<type<<" "<<price<<endl;
    }

    ~Gitara(){

    }
};

class Magacin{
private:
    char name[30];
    char location[60];
    Gitara *guitars;
    int num_guitars;
    int year;
public:
    Magacin(){
        strcpy(this->name, "");
        strcpy(this->location, "");
        this->num_guitars=0;
        this->year=0;
        guitars = new Gitara[0];
    }

    Magacin(char *name, char *location, int year){
        strcpy(this->name, name);
        strcpy(this->location,location);
        this->year=year;
        this->num_guitars=0;
        guitars = new Gitara[0];
    }

    Magacin(char *name, char *location){
        strcpy(this->name, name);
        strcpy(this->location,location);
        this->year=0;
        this->num_guitars=0;
        guitars = new Gitara[0];
    }


     double vrednost(){
         double sum=0;
         for (int i=0; i<num_guitars; i++){
             sum+=guitars[i].getNabavna();
         }
         return sum;
     }

     void dodadi(Gitara g){
         Gitara *tmp = new Gitara[num_guitars+1];
         for (int i=0; i<num_guitars; i++){
             tmp[i]=guitars[i];
         }
         tmp[num_guitars]=g;
         delete [] guitars;
         guitars = new Gitara [num_guitars+1];
         for (int i=0; i<num_guitars+1; i++){
             guitars[i]=tmp[i];
         }
         num_guitars++;
         delete [] tmp;
     }

     void prodadi(Gitara g){
         int j=0;
         for (int i=0; i<num_guitars; i++){
             if (!guitars[i].daliIsti(g)){
                 j++;
             }
         }
         Gitara *tmp = new Gitara [j];
         int k=0;
         for (int i=0; i<num_guitars; i++){
             if (!guitars[i].daliIsti(g)){
                 tmp[k++]=guitars[i];
             }
         }
         delete [] guitars;
         guitars = new Gitara [j];
         for (int i=0; i<j; i++){
             guitars[i]=tmp[i];
         }
         num_guitars=j;
         delete [] tmp;
     }

     void pecati(bool daliNovi){
        cout<<name<<" "<<location<<endl;
        if (daliNovi==true){
            for (int i=0; i<num_guitars; i++){
                if (guitars[i].getGodina() > year){
                    guitars[i].pecati();
                }
            }
        } else if (daliNovi==false){
            for (int i=0; i<num_guitars; i++){
                guitars[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
//this software is property of bethesda softworks