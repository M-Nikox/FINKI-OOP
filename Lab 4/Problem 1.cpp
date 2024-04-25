#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction{
private:
    char *name;
    int index;
    char *reason;
    void copy(const DisciplinaryAction & c){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, c.name);
        this->index=c.index;
        this->reason= new char[strlen(reason)+1];
        strcpy(this->reason, c.reason);
    }
public:
    DisciplinaryAction(){
        name = new char[1];
        index=0;
        reason = new char[1];
        name[0] = '\0';
        reason[0] = '\0';
    }

    DisciplinaryAction(char * name, int index, char *reason){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->index=index;
        this->reason=new char[strlen(reason)+1];
        strcpy(this->reason, reason);
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

    DisciplinaryAction operator=(const DisciplinaryAction & other){
        if (this==&other){
            return *this;
        }
        delete [] name;
        delete [] reason;
        copy(other);
        return *this;
    }

    void print(){
        cout<<"Student: "<<name<<endl;
        cout<<"Student's index: "<<index<<endl;
        cout<<"Reason: "<<reason<<endl;
    }

    ~DisciplinaryAction(){
        delete [] name;
        delete [] reason;
    }

};



/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for(int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for(int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}