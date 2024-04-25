#include <iostream>
#include <cstring>

using namespace std;

class Vozac{
protected:
    char name[100];
    int age;
    int num_races;
    bool is_veteran;
public:
    Vozac(){
        strcpy(this->name, "NONE");
        this->age=0;
        this->num_races=0;
        this->is_veteran=false;
    }

    Vozac(char name[100], int age, int num_races, bool is_veteran){
        strcpy(this->name, name);
        this->age=age;
        this->num_races=num_races;
        this->is_veteran=is_veteran;
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.name << endl << vozac.age << endl << vozac.num_races << endl;
        if (vozac.is_veteran){
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual double earnings(){
        //virtual function for salary
        return 0;
    }
    
    virtual double danok(){
        //virtual function for tax;
        return 0;
    }


};

class Avtomobilist : public Vozac{
private:
    double price;
public:
    Avtomobilist(char name[100], int age,  int num_races, bool is_veteran, double price) : Vozac(name, age, num_races, is_veteran){
        strcpy(this->name, name);
        this->age=age;
        this->num_races=num_races;
        this->is_veteran=is_veteran;
        this->price=price;
    }

    double earnings() override{
        return price/5.0;
    }

    double danok() override{
        double tax=0;
        if (num_races <10){
            return earnings()*0.10;
        } else
            return earnings()*0.15;
    }

};

class Motociklist : public Vozac{
private:
    int horsepower;
public:
    Motociklist(char name[100], int age,  int num_races, bool is_veteran, int horsepower) : Vozac(name, age, num_races, is_veteran){
        strcpy(this->name, name);
        this->age=age;
        this->num_races=num_races;
        this->is_veteran=is_veteran;
        this->horsepower=horsepower;
    }
    
    double earnings() override{
        return horsepower*20;
    }

    double danok() override{
        double tax=0;
        if (is_veteran){
            return earnings()*0.25;
        } else
            return earnings()*0.20;
    }

};

int soIstaZarabotuvachka(Vozac **v, int num_drivers, Vozac *other){
    int num_same_salary=0;
    for (int i=0; i<num_drivers; i++){
        if (v[i]->earnings() == other->earnings()){
            num_same_salary++;
        }
    }
    return num_same_salary;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}