#include <iostream>
#include <cstring>
using namespace std;


enum tip { POP = 0, RAP = 1, ROK = 2};

class Pesna{
    char *name;
    int minutes;
    tip type;
    void copy(const Pesna & other){
        this->name=new char[strlen(other.name+1)];
        strcpy(this->name, other.name);
        this->minutes=other.minutes;
        this->type=other.type;
    }
public:
    Pesna(){
        this->name = new char [2];
        strcpy(this->name, " ");
        this->minutes=0;
        this->type=POP;
    }

    Pesna(char *name, int minutes, tip type){
        this->name = new char [strlen(name+1)];
        strcpy(this->name, name);
        this->minutes=minutes;
        this->type=type;
    }

    Pesna(const Pesna& other){
        copy(other);
    }

    Pesna& operator=(const Pesna & other){
        if (this==&other){
            return *this;
        } else {
            delete [] name;
            copy(other);
            return *this;
        }
    }

    char *getName() const {
        return name;
    }

    void setName(char *name) {
        Pesna::name = name;
    }

    int getMinutes() const {
        return minutes;
    }

    void setMinutes(int minutes) {
        Pesna::minutes = minutes;
    }

    tip getType() const {
        return type;
    }

    void setType(tip type) {
        Pesna::type = type;
    }

    void pecati() {
        cout << "\"" << name << "\"" << "-" << minutes << "min\n";
    }

    ~Pesna(){
        delete [] name;
    }
};

class CD{
    Pesna pesni[10];
    int br_pesni;
    int maxtime;
public:
    CD(){
        this->br_pesni=0;
    }
    CD(int maxtime){
        this->br_pesni=0;
        this->maxtime=maxtime;
    }

    Pesna getPesna(int idx){return pesni[idx];}

    const Pesna *getPesni() const {
        return pesni;
    }

    int getNum() const {
        return br_pesni;
    }

    void setBrPesni(int brPesni) {
        br_pesni = brPesni;
    }

    int getMaxtime() const {
        return maxtime;
    }

    void setMaxtime(int maxtime) {
        CD::maxtime = maxtime;
    }

    void pecatiPesniPoTip(enum tip type){
        for (int i=0; i<br_pesni; i++){
            if (pesni[i].getType()==type){
                pesni[i].pecati();
            }
        }
    }

    void dodadiPesna(Pesna p){
        int idx=0;
        for (int i=0; i<br_pesni; i++){
            idx+=pesni[i].getMinutes();
        }
        if (br_pesni<10 && idx+p.getMinutes() <= maxtime){
            pesni[br_pesni++]=p;
        }
    }

    ~CD(){

    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getNum(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}