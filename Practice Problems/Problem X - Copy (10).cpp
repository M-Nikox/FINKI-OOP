#include <iostream>
#include <cstring>

using namespace std;

class Koncert {
protected:
    char concert_name[20];
    char location[20];
    static double discount;
    double price;
public:
    static void setSezonskiPopust(double discount);
    char * getNaziv(){
        return concert_name;
    }
    static double getSezonskiPopust(){
        return discount;
    }

    void setPrice(double price);

    Koncert(){
        strcpy(this->concert_name, "NONE");
        strcpy(this->location, "NONE");
        this->price=0;
    }
    Koncert(char concert_name[20], char location[20], double price){
        strcpy(this->concert_name, concert_name);
        strcpy(this->location, location);
        this->price=price;
    }

    virtual double cena(){
        return price - (price * (getSezonskiPopust()));
    }
};

class ElektronskiKoncert : public Koncert{
private:
    char *DJ_name;
    double length;
    bool d_n;
public:
    ElektronskiKoncert(){
        strcpy(this->concert_name, "NONE");
        strcpy(this->location, "NONE");
        this->price=0;
        this->length=0;
        this->d_n=false;
        this->DJ_name=new char[10];
        strcpy(this->DJ_name, "EMPTY");
    }

    ElektronskiKoncert(char concert_name[20], char location[20], double price, char * DJ_name, double length, bool d_n) : Koncert(concert_name, location, price){
        strcpy(this->concert_name, concert_name);
        strcpy(this->location, location);
        this->price=price;
        this->DJ_name = new char [strlen(DJ_name)+1];
        strcpy(this->DJ_name, DJ_name);
        this->length=length;
        this->d_n=d_n;
    }

    double cena() override {
        double new_price = price - (price*getSezonskiPopust());
        if (length > 5.0) {
            new_price += 150;
        }

        if (length > 7.0) {
            new_price += 360;
        }

        if (d_n) {
            new_price -= 50;
        }
        
        if (!d_n) {
            new_price += 100;
        }
        return new_price;
    }



    ~ElektronskiKoncert(){
        delete [] DJ_name;
    }
};

double Koncert::discount=0.2;

void Koncert::setSezonskiPopust(double discount) {
    Koncert::discount = discount;
}

void Koncert::setPrice(double price) {
    Koncert::price = price;
}

void najskapKoncert(Koncert** koncerti, int n) {
    int num_obj = 0;
    for (int i = 0; i < n; i++) {
        Koncert* k = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if (k) {
            num_obj++;
        }
    }

    int max_index = 0;
    for (int i = 0; i < n; i++) {
        if (koncerti[max_index]->cena() < koncerti[i]->cena()){
            max_index = i;
        }
    }

    cout << "Najskap koncert: " << koncerti[max_index]->getNaziv() << " " << koncerti[max_index]->cena() << endl;
    cout << "Elektronski koncerti: " << num_obj << " od vkupno " << n << endl;
}


bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski){
    bool found=false;
    if (elektronski){
        for (int i=0; i<n; i++){
            Koncert *obj = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if (obj){
                if (!strcmp(koncerti[i]->getNaziv(), naziv)){
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    found=true;
                }
            }
        }
    } else {
        for (int i=0; i<n; i++){
            if (!strcmp(koncerti[i]->getNaziv(), naziv)){
                found=true;
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
            }
        }
    }
    return found;
}

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,true);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
