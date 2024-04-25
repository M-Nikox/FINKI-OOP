#include <iostream>
#include <cstring>

using namespace std;

class Pica{
private:
    char name[15];
    int price;
    char *garnish;
    int discount; //expressed in %
    void copy(const Pica & other){
        strcpy(this->name, other.name);
        this->price=other.price;
        this->discount=other.discount;
        this->garnish = new char [strlen(other.garnish)+1];
        strcpy(this->garnish, other.garnish);
    }
public:
    Pica(){
        strcpy(this->name, "");
        this->garnish = new char [2];
        strcpy(this->garnish, " ");
        this->price=0;
        this->discount=0;
    }

    Pica(char name[15], int price, char *garnish, int discount){
        strcpy(this->name, name);
        this->price=price;
        this->discount=discount;
        this->garnish = new char [strlen(garnish)+1];
        strcpy(this->garnish, garnish);
    }

    Pica(const Pica & other){
        copy(other);
    }

    const Pica & operator=(const Pica & other){
        if (this==&other){
            return *this;
        } else {
            delete [] garnish;
            copy(other);
            return *this;
        }
    }

    void pecati(){
        cout<<name<<" - "<<garnish<<", "<<price<<" ";
    }

    bool istiSe(Pica p){
        if (!strcmp(getGarnish(), p.getGarnish())){
            return true;
        } else return false;
    }

    const char *getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }

    void setPrice(int price) {
        Pica::price = price;
    }

    char *getGarnish() const {
        return garnish;
    }

    void setGarnish(const char* garnish) {
        delete[] this->garnish;
        this->garnish = new char[strlen(garnish) + 1];
        strcpy(this->garnish, garnish);
    }


    int getDiscount() const {
        return discount;
    }

    void setDiscount(int discount) {
        Pica::discount = discount;
    }

    ~Pica(){
       //delete [] garnish;
    }
};

class Picerija{
private:
    char name[15];
    Pica *pizzas;
    int num_pizzas;
public:
    Picerija(){
        strcpy(this->name, "");
        this->num_pizzas=0;
        pizzas = new Pica[0];
    }

    Picerija(char name[15]){
        strcpy(this->name, name);
        this->num_pizzas=0;
        pizzas = new Pica[0];
    }

    Picerija(const char name[15], Pica *pizzas, int num_pizzas){
        strcpy(this->name, name);
        this->num_pizzas=num_pizzas;
        this->pizzas=new Pica[num_pizzas];
        for (int i=0; i<num_pizzas; i++){
            this->pizzas[i]=pizzas[i];
        }
    }

    const char *getName() const {
        return name;
    }

    void setName(char name[15]){
        strcpy(this->name, name);
    }

    Pica *getPizzas() const {
        return pizzas;
    }

    int getNumPizzas() const {
        return num_pizzas;
    }

    void setNumPizzas(int numPizzas) {
        num_pizzas = numPizzas;
    }

    void dodadi(Pica p){
        Pica *tmp = new Pica[num_pizzas+1];
        int k=0;
        for (int i=0; i<num_pizzas; i++){
            if (pizzas[i].istiSe(p)){
                delete [] tmp;
                return;
            } else {
                tmp[k++]=pizzas[i];
            }
        }
        delete [] pizzas;
        tmp[num_pizzas]=p;
        pizzas=tmp;
        num_pizzas++;
    }

    Picerija & operator+=(const Pica & p){
        for (int i = 0; i < num_pizzas; i++) {
            if (pizzas[i].istiSe(p)) {
                return *this;
            }
        }

        Pica* tmp = new Pica[num_pizzas + 1];
        int k=0;
        for (int i = 0; i < num_pizzas; i++) {
            tmp[k++] = pizzas[i];
        }

        tmp[num_pizzas] = p;
        delete[] pizzas;
        pizzas = tmp;
        num_pizzas++;

        return *this;
    }

    void piciNaPromocija(){
        for (int i=0; i<num_pizzas; i++){
            if (pizzas[i].getDiscount() > 0){
                pizzas[i].pecati(); cout<<salePrice(pizzas[i])<<endl;
            }
        }
    }

    int salePrice(const Pica &p) {
        int price = p.getPrice();
        int discount = p.getDiscount();
        return price - (price * discount) / 100;
    }

    ~Picerija(){
       // delete [] pizzas;
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setName(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getName() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getName() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
