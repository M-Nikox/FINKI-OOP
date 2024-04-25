#include <iostream>
#include <cstring>

using namespace std;

class Transport{
protected:
    char destination[100];
    int base_price;
    int distance;
public:
    Transport(){
        strcpy(this->destination, "NONE");
        this->base_price=0;
        this->distance=0;
    }

    Transport(char destination[100], int base_price, int distance){
        strcpy(this->destination,destination);
        this->base_price=base_price;
        this->distance=distance;
    }

    const char *getDestination() const {
        return destination;
    }

    int getBasePrice() const {
        return base_price;
    }

    void setBasePrice(int basePrice) {
        base_price = basePrice;
    }

    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        Transport::distance = distance;
    }

    virtual int price() = 0;

};

class AvtomobilTransport : public Transport{
private:
    bool driver_is_paid;
public:
    AvtomobilTransport(){
        strcpy(this->destination, "NONE");
        this->base_price=0;
        this->distance=0;
        this->driver_is_paid=false;
    }
    AvtomobilTransport(char destination[100], int base_price, int distance, bool driver_is_paid) : Transport(destination, base_price, distance){
        strcpy(this->destination,destination);
        this->base_price=base_price;
        this->distance=distance;
        this->driver_is_paid=driver_is_paid;
    }

    bool isDriverIsPaid() const {
        return driver_is_paid;
    }

    void setDriverIsPaid(bool driverIsPaid) {
        driver_is_paid = driverIsPaid;
    }

    int price() override {
        if (driver_is_paid) {
            return static_cast<int>(base_price * 1.20);
        } else {
            return base_price;
        }
    }

    bool operator<(const AvtomobilTransport & other){
        return distance<other.distance;
    }
};

class KombeTransport : public Transport{
private:
    int num_passengers;
public:
    KombeTransport(){
        strcpy(this->destination, "NONE");
        this->base_price=0;
        this->distance=0;
        this->num_passengers=0;
    }
    KombeTransport(char destination[100], int base_price, int distance, int num_passengers) : Transport(destination, base_price, distance){
        strcpy(this->destination,destination);
        this->base_price=base_price;
        this->distance=distance;
        this->num_passengers=num_passengers;
    }

    int getNumPassengers() const {
        return num_passengers;
    }

    void setNumPassengers(int numPassengers) {
        num_passengers = numPassengers;
    }

    int price() override {
        int new_price=base_price;
        for (int i=0; i<num_passengers; i++){
            new_price-=200;
        }
        return new_price;
    }

    bool operator<(const KombeTransport & other){
        return distance<other.distance;
    }
};

void pecatiPoloshiPonudi(Transport **offers, int num_offers, AvtomobilTransport other) {
    Transport **tmp = new Transport *[num_offers]; // Allocate memory for tmp array

    int k = 0;
    for (int i = 0; i < num_offers; i++) {
        if (offers[i]->price() > other.price()) {
            tmp[k] = offers[i]; // Allocate memory for each transport and copy it
            k++;
        }
    }

    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++) {
            if (tmp[j]->price() > tmp[j + 1]->price()) {
                Transport *temp = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << tmp[i]->getDestination() << " " << tmp[i]->getDistance() << " " << tmp[i]->price() << endl;
    }
    delete [] tmp;
}



int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
