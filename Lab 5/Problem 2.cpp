#include <iostream>
#include <cstring>
using namespace std;

class DeliveryPerson{
private:
    char ID[5];
    char *name;
    int location;
    int num_finished;
    void copy(const DeliveryPerson & other){
        strcpy(this->ID, other.ID);
        this->name = new char [strlen(other.name)+1];
        strcpy(this->name, other.name);
        this->location=other.location;
        this->num_finished=other.num_finished;
    }
public:
    DeliveryPerson(){
        strcpy(this->ID, "");
        this->name = new char[2];
        strcpy(this->name, " ");
        this->location=0;
        this->num_finished=0;
    }

    DeliveryPerson(char ID[5], const char *name, int location){
        strcpy(this->ID, ID);
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->location=location;
        this->num_finished=0;
    }

    void print(){
        cout<<"ID: "<<ID<<" Name: "<<name<<" Current location: "<<location<<" # of deliveries: "<<num_finished<<endl;
    }

    DeliveryPerson(const DeliveryPerson & other){
        copy(other);
    }

    DeliveryPerson & operator=(const DeliveryPerson & other){
        if (this==&other){
            return *this;
        } else{
            delete [] name;
            copy(other);
            return *this;
        }
    }

    const char *getId() const {
        return ID;
    }

    char *getName() const {
        return name;
    }

    void setName(char *name) {
        DeliveryPerson::name = name;
    }

    int getLocation() const {
        return location;
    }

    void setLocation(int location) {
        DeliveryPerson::location = location;
    }

    int getNumFinished() const {
        return num_finished;
    }

    void setNumFinished(int numFinished) {
        num_finished = numFinished;
    }

    ~DeliveryPerson() {
        //delete [] name;
    }
};

class DeliveryApp{
private:
    char name[20];
    DeliveryPerson *persons;
    int num_persons;
    void copy(const DeliveryApp & other){
        strcpy(this->name, other.name);
        this->num_persons=other.num_persons;
        for (int i=0; i<num_persons; i++){
            persons[i]=other.persons[i];
        }
    }
public:
    DeliveryApp(){
        strcpy(this->name, "");
        this->persons = new DeliveryPerson[0];
        this->num_persons=0;
    }

    DeliveryApp(char name[20]){
        strcpy(this->name, name);
        this->num_persons=0;
    }

    DeliveryApp(const DeliveryApp & other){
        copy(other);
    }

    DeliveryApp & operator=(const DeliveryApp & other){
        if (this==&other){
            return *this;
        } else
            delete [] persons;
            copy(other);
            return *this;
    }

    void print(){
        cout<<name<<endl;
        if (!num_persons){
            cout<<"EMPTY"<<endl;
            return;
        }
        for (int i=0; i<num_persons; i++){
            persons[i].print();
        }
    }

    const char *getName() const {
        return name;
    }

    DeliveryPerson *getPersons() const {
        return persons;
    }

    void setPersons(DeliveryPerson *persons) {
        DeliveryApp::persons = persons;
    }

    int getNumPersons() const {
        return num_persons;
    }

    void setNumPersons(int numPersons) {
        num_persons = numPersons;
    }

    void addDeliveryPerson (const DeliveryPerson & person){
        DeliveryPerson *tmp = new DeliveryPerson[num_persons+1];
        for (int i=0; i<num_persons; i++){
            if (!strcmp(persons[i].getId(), person.getId())){
                return;
            }
        }
        for (int i=0; i<num_persons; i++){
            tmp[i]=persons[i];
        }
        tmp[num_persons]=person;
        persons=tmp;
        num_persons++;
    }

    void assignDelivery(int restaurantArea, int customerArea) {
        int closestIndex = -1;
        int closestDistance = 999;
        int numClosest = 0;
        int minNumFinished = 999;

        int flag=0;

        for (int i=0; i<num_persons; i++){
            if (persons[i].getLocation() == restaurantArea && persons[i+1].getLocation()==restaurantArea) {
                if (persons[i].getNumFinished() < persons[i+1].getNumFinished()){
                    closestIndex=i;
                    flag++;
                }
            }
        }

        if (flag!=0){
            persons[closestIndex].setLocation(customerArea);
            persons[closestIndex].setNumFinished(persons[closestIndex].getNumFinished() + 1);
            return;
        }

        for (int i = 0; i < num_persons; i++) {
            if (persons[i].getLocation() == restaurantArea) {
                closestIndex = i;
                break;
            } else {
                int distance = abs(persons[i].getLocation() - restaurantArea);
                if (distance < closestDistance) {
                    closestIndex = i;
                    closestDistance = distance;
                    numClosest = 1;
                    minNumFinished = persons[i].getNumFinished();
                } else if (distance == closestDistance) {
                    numClosest++;
                    if (persons[i].getNumFinished() < minNumFinished) {
                        closestIndex = i;
                        minNumFinished = persons[i].getNumFinished();
                    }
                }
            }
        }

        persons[closestIndex].setLocation(customerArea);
        persons[closestIndex].setNumFinished(persons[closestIndex].getNumFinished() + 1);
    }





    ~DeliveryApp(){
        //delete [] persons;
    }
};

int main() {

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person("12345", "Stefan", 5);
        person.print();
        cout << "CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person = DeliveryPerson("12345", "Stefan", 5);
        person.print();
        cout << "COPY-CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson" << endl;
        DeliveryPerson person;
        DeliveryPerson person2("12345", "Stefan", 5);
        person = person2;
        person.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR DeliveryApp" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        app.print();
        cout << "CONSTRUCTOR DeliveryApp OK" << endl;
    } else if (testCase == 5) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        cin >> n; //read assign deliveries
        for (int i = 0; i < n; i++) {
            int restaurantArea, customerArea;
            cin >> restaurantArea >> customerArea;
            app.assignDelivery(restaurantArea, customerArea);
        }
        app.print();
    }
    return 0;
}
