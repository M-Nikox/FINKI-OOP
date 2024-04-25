#include <iostream>
#include <cstring>

using namespace std;

class Employee{
protected:
    char name[100];
    int age;
public:
    Employee(){
        strcpy(this->name, "NONE");
        this->age=0;
    }
    Employee(char name[100], int age){
        this->age=age;
        strcpy(this->name, name);
    }
    virtual void displayInfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
};

class Payable{
protected:
    double salary;
public:
    Payable(double salary=0){
        this->salary=salary;
    }
    virtual double calculateSalary() = 0;
};

class Developer : public Employee, public Payable{
private:
    char programming_lan[100];
public:
    Developer(){
        strcpy(this->name, "NONE");
        this->age=0;
        strcpy(this->programming_lan, "NONE");
        this->salary=0;
    }
    Developer(char name[100], int age, double salary, char programming_lan[100]) : Employee(name, age), Payable(salary){
        this->age=age;
        strcpy(this->name, name);
        this->salary=salary;
        strcpy(this->programming_lan, programming_lan);
    }
    double calculateSalary() override{
        return salary*0.9;
    }
    void displayInfo() override{
        cout<<"-- Developer Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Programming Language: "<<programming_lan<<endl;
    }
};

class Manager : public Employee, public Payable{
private:
    int num_departments;
public:
    Manager(){
        strcpy(this->name, "NONE");
        this->age=0;
        this->salary=0;
        this->num_departments=0;
    }
    Manager(char name[100], int age, double salary, int num_departments) : Employee(name, age), Payable(salary){
        this->age=age;
        strcpy(this->name, name);
        this->salary=salary;
        this->num_departments=num_departments;
    }

    double calculateSalary(){
        double new_Salary=salary;
        for (int i=0; i<num_departments; i++){
            new_Salary+=(salary * 0.05);
        }
        return new_Salary;
    }

    void displayInfo() override{
        cout<<"-- Manager Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Number of Departments: "<<num_departments<<endl;
    }
};

double biggestSalary(Payable* payable[], int n) {
    Payable* maxSalaryEmployee = payable[0];

    for (int i = 1; i < n; i++) {
        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
            maxSalaryEmployee = payable[i];
        }
    }

    return maxSalaryEmployee->calculateSalary();
}

int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}