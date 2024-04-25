#include <iostream>
#include <cstring>

using namespace std;

class FoodItem{
protected:
    char *type;
    int num;
public:
    FoodItem(){}
    virtual int getPrice() = 0;
    virtual int getTime() = 0;
    virtual ~FoodItem() {
        delete [] type;
    }

    FoodItem(char *type, int num){
        this->type=new char[strlen(type)+1];
        strcpy(this->type, type);
        this->num=num;
    }

    char *getType() const {
        return type;
    }
};

class Pizza : public FoodItem {
private:
    char *dough;
public:
    Pizza() : FoodItem(){
        this->type=new char[2];
        strcpy(this->type, " ");
        this->dough=new char[2];
        strcpy(this->dough, " ");
        this->num=0;
    }

    Pizza(char *type, int num, char *dough) : FoodItem(type, num){
        this->type=new char[strlen(type)+1];
        strcpy(this->type, type);
        this->dough=new char [strlen(dough)+1];
        strcpy(this->dough, dough);
        this->num=num;
    }
    int getTime() override{
        return 25;
    }

    int getPrice() override{
        if (!strcmp(dough, "wholeWheat")){
            return 250*num;
        } else return 350*num;
    }

    ~Pizza(){
        delete [] dough;
    }
};

class Steak : public FoodItem{
private:
    bool cooked;
public:
    Steak() : FoodItem(){
        this->type=new char[2];
        strcpy(this->type, " ");
        this->num=0;
        this->cooked=false;
    }

    Steak(char *type, int num, bool cooked) : FoodItem(type, num){
        this->type=new char[strlen(type)+1];
        strcpy(this->type, type);
        this->num=num;
        this->cooked=cooked;
    }

    int getTime() override{
        if (cooked){
            return 20;
        } else return 15;
    }

    int getPrice() override{
        return 1300*num;
    }

    ~Steak(){}
};

FoodItem* getMaxFoodItem(FoodItem *pItem[], int n){
    int max=pItem[0]->getPrice();
    int max_index=0;
    for (int i=0; i<n; i++){
        if (max < pItem[i]->getPrice()){
            max=pItem[i]->getPrice();
            max_index=i;
        }
    }
    return pItem[max_index];
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max price is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}