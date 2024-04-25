#include <iostream>
#include <cstring>
using namespace std;

//YOUR CODE HERE

class MobilePhone{
private:
    char model[20];
    int broj_model;
    int godinaizdavanje;
public:
    MobilePhone() {}

    MobilePhone(char *_model, int _broj_model, int _godinaizdavanje){
        strcpy(this->model, _model);
        this->broj_model=_broj_model;
        this->godinaizdavanje=_godinaizdavanje;
    }

    MobilePhone(const MobilePhone& other){
        strcpy(this->model, other.model);
        this->broj_model=other.broj_model;
        this->godinaizdavanje=other.godinaizdavanje;
    }

    const char *getModel() const {
        return model;
    }

    int getBrojModel() const {
        return broj_model;
    }

    int getGodinaizdavanje() const {
        return godinaizdavanje;
    }
    

    ~MobilePhone(){}
};

class Owner{
private:
    char ime[20];
    char prezime[20];
    MobilePhone phone;
public:
    Owner(){}

    Owner(char *ime, char *prezime, MobilePhone p){
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->phone=p;
    }

    const char *getIme() const {
        return ime;
    }

    const char *getPrezime() const {
        return prezime;
    }

    const MobilePhone &getPhone() const {
        return phone;
    }

    void print(){
        cout<<ime<<" "<<prezime<<" has a mobile phone:"<<endl;
        cout<<phone.getModel()<<" "<<phone.getBrojModel()<<" release year: "<<phone.getGodinaizdavanje()<<endl;
    }

    ~Owner(){}
};

//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}
