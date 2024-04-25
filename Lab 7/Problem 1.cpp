#include <iostream>
#include <cstring>
using namespace std;

class Kvadrat{
protected:
    double len;
public:
    Kvadrat(){
        this->len=0.0;
    }
    Kvadrat(double len){
        this->len=len;
    }

    Kvadrat(const Kvadrat & other){
        this->len=other.len;
    }

    double perimetar(){
        return 4.0 * len;
    }

    double plostina(){
        return len*len;
    }

    void pecati(){
        cout<<"Kvadrat so dolzina a="<<len<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }

    ~Kvadrat(){}
};

class Pravoagolnik : public Kvadrat{
private:
    double x;
    double y;
public:
    Pravoagolnik(){
        this->x=0.0;
        this->y=0.0;
    }

    Pravoagolnik(const Kvadrat &k, double x, double y) : Kvadrat(k){
        this->x=x+len;
        this->y=y+len;
        if (x==y){
            len=len+x;
        }
    }

    Pravoagolnik(const Pravoagolnik & other){
        this->x=other.x;
        this->y=other.y;
    }

    double plostina(){
        return x*y;
    }

    double perimetar(){
        return 2*(x+y);
    }

    void pecati(){
        if (x == y){
            Kvadrat::pecati();
        }
    else
        cout<<"Pravoagolnik so strani: "<<x<<" i "<<y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }

    ~Pravoagolnik(){}
};

int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;
	
	cin>>n;
    
    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];
    
	for (int i=0;i<n;i++){
		cin>>a;
        
		kvadrati[i] = Kvadrat(a);
	}
	
	for (int i=0;i<n;i++){
		cin>>x>>y;
        
		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}
	
	int testCase;
	cin>>testCase;
    
	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}