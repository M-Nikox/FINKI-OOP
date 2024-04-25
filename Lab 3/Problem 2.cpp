#include <iostream>
#include <cstring>

using namespace std;

class SpaceObject{
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    SpaceObject(){}

    SpaceObject(char *name, char *type, int distance){
        strcpy(this->name, name);
        strcpy(this->type, type);
        this->distanceFromEarth=distance;
    }

    SpaceObject(const SpaceObject& other){
        strcpy(this->name, other.name);
        strcpy(this->type, other.type);
        this->distanceFromEarth=other.distanceFromEarth;
    }

    const char *getName() const {
        return name;
    }

    const char *getType() const {
        return type;
    }

    int getDistanceFromEarth() const {
        return distanceFromEarth;
    }

    void setDistanceFromEarth(int _distanceFromEarth) {
        distanceFromEarth = _distanceFromEarth;
    }

    void print(){
        cout<<name<<" ("<<type<<") - distance: "<<distanceFromEarth<<" light years away from Earth"<<endl;
    }

    ~SpaceObject(){}
};

class Alien{
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;
    SpaceObject objects[10];
public:
    Alien(){

    }

    Alien(char *name, int age, char *homePlanet, int numObj, SpaceObject *obj){
        strcpy(this->name, name);
        this->age=age;
        strcpy(this->homePlanet, homePlanet);
        this->numObj=numObj;
        for (int i=0; i<numObj; i++){
            objects[i]=obj[i];
        }
    }

    Alien(const Alien& other){
        strcpy(this->name, other.name);
        this->age=other.age;
        strcpy(this->homePlanet, other.homePlanet);
        this->numObj=other.numObj;
        for(int i=0; i<numObj; i++){
            objects[i]=other.objects[i];
        }
    }

    const SpaceObject *getObjects() const {
        return objects;
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    const char *getHomePlanet() const {
        return homePlanet;
    }

    int getNumObj() const {
        return numObj;
    }

    void setAge(int age) {
        Alien::age = age;
    }

    void setNumObj(int numObj) {
        Alien::numObj = numObj;
    }

    SpaceObject getObjectClosestToEarth(){
        SpaceObject tmp;
            for (int i=0; i<numObj; i++){
                for (int j=0; j<numObj-i-1; j++){
                    if (objects[j].getDistanceFromEarth()>objects[j+1].getDistanceFromEarth()){
                        tmp=objects[j];
                        objects[j]=objects[j+1];
                        objects[j+1]=tmp;
                    }
                }
            }
        objects[0].print();
    }


    void print(){
        cout<<"Alien name: "<<name<<endl;
        cout<<"Alien age: "<<age<<endl;
        cout<<"Alien home planet: "<<homePlanet<<endl;
        cout<<"Favourite space object closest to earth: ";
        getObjectClosestToEarth();
    }

    ~Alien(){

    }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main()
{
    char name[100], homePlanet[100];
    int age, numObj;
    cin>>name>>age>>homePlanet>>numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for(int i=0; i<numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin>>spaceObjectName>>spaceObjectType>>distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i]=SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien=Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}