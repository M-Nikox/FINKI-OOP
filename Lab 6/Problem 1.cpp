#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction{
private:
    char *name{};
    char *reason{};
    int index{};
    int num_ban{};
    void copy(const DisciplinaryAction & other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->reason=new char [strlen(other.reason)+1];
        strcpy(this->reason, other.reason);
        this->index=other.index;
        this->num_ban=other.num_ban;
    }
public:
    DisciplinaryAction(){
        this->name=new char [6];
        strcpy(this->name, "EMPTY");
        this->reason=new char [6];
        strcpy(this->reason, "EMPTY");
        this->num_ban=-1;
        this->index=-1;
    }

    DisciplinaryAction(char *name, int index,char *reason, int num_ban){
        this->name=new char[strlen(name)+1];
        this->reason=new char[strlen(reason)+1];
        strcpy(this->name, name);
        strcpy(this->reason, reason);
        this->num_ban=num_ban;
        this->index=index;
    }

    DisciplinaryAction(const DisciplinaryAction & other){
        copy(other);
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction & other){
        if (this == &other){
            return *this;
        } else{
            delete [] name;
            delete [] reason;
            copy(other);
            return *this;
        }
    }

    friend ostream & operator<<(ostream & os, DisciplinaryAction s){
        os<<"Student: "<<s.name<<endl;
        os<<"Student's index: "<<s.index<<endl;
        os<<"Reason: "<<s.reason<<endl;
        os<<"Sessions: "<<s.num_ban<<endl;
    }

    DisciplinaryAction & operator++(){
        ++num_ban;
        return *this;
    }

    bool operator>=(const DisciplinaryAction & other) const {
        if (this->num_ban >= other.num_ban){
            return true;
        } else return false;
    }

    ~DisciplinaryAction(){
        delete [] name;
        delete [] reason;
    }
};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}