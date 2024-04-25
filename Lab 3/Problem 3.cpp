#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Employee{
private:
    char name[100];
    char surname[100];
    int salary;
public:
    Employee(){}

    Employee(char *name, char *surname, int salary){
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary=salary;
    }

    Employee(const Employee& other){
        strcpy(this->name, other.name);
        strcpy(this->surname, other.surname);
        this->salary=other.salary;
    }

    const char *getName() const {
        return name;
    }

    const char *getSurname() const {
        return surname;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int salary) {
        Employee::salary = salary;
    }

    void print(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }

    ~Employee(){}
};

class TechCompany{
private:
    char compname[100];
    Employee employees[100];
    int numEmp;
public:
    TechCompany(){}

    TechCompany(char *name){
        strcpy(this->compname, name);
    }

    TechCompany(char *cname, Employee *emp, int num){
        strcpy(this->compname, cname);
        this->numEmp=num;
        for (int i=0; i<numEmp; i++) {
            employees[i] = emp[i];
        }
    }

    const char *getCompname() const {
        return compname;
    }

    char setName(char *name){
        strcpy(this->compname,name);
    }

    const Employee *getEmployees() const {
        return employees;
    }

    int getNumEmp() const {
        return numEmp;
    }

    void setNumEmp(int numEmp) {
        TechCompany::numEmp = numEmp;
    }

    float avg(){
        int n=getNumEmp();
        int sum=0;
        float average=0;

        for (int i=0; i<n; i++) {
            sum+=employees[i].getSalary();
        }
        average=sum/numEmp;
        return average;
    }

    int sum(){
        int sum=0;
        int n=getNumEmp();
        for (int i=0; i<n; i++){
            sum+=employees[i].getSalary();
        }
        return sum;
    }


    ~TechCompany(){}
};


TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies){
    TechCompany highestpaid=companies[0];
    int sumacomp[]={0};
    int sum=0;
    for (int i=0; i<numCompanies; i++){
        for (int j=0; j<companies[i].getNumEmp(); j++){
            sum=0;
            sum+=companies[i].getEmployees()->getSalary();
        }
        sumacomp[i]=sum;
    }
    int tmp=0;
    for (int i=0; i<numCompanies; i++){
        for (int j=0; j<numCompanies-i-1; j++){
            if (sumacomp[j]>sumacomp[j+1]){
                tmp=j;
            }
        }
    }
    return companies[tmp];
}


TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies){
    float var=0;
    float std=0;
    int sum=0;
    for (int i=0; i<numCompanies; i++){
        for (int j=0; j<companies[i].getNumEmp(); j++){
            var = (((sum*companies[i].getEmployees()->getSalary())-companies[i].avg())*((sum*companies[i].getEmployees()->getSalary())-companies[i].avg()))/companies[i].getNumEmp()-1;
        }
        std=sqrt(var);
    }
}


bool isSameCompany(TechCompany company1, TechCompany company2){
    if (company1.getCompname() == company2.getCompname()){
        return true;
    }
}
//DO NOT CHANGE main()

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
