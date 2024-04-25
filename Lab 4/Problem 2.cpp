#include <iostream>
#include <cstring>

using namespace std;

#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    char* name{};
    int age{};
    char* major{};

    void copy(const Student& copied) {
        this->name = new char[strlen(copied.name) + 1];
        strcpy(this->name, copied.name);
        this->age = copied.age;
        this->major = new char[strlen(copied.major) + 1];
        strcpy(this->major, copied.major);
    }

public:
    Student() {
        name = new char[1];
        name[0] = '\0';
        age = 0;
        major = new char[1];
        major[0] = '\0';
    }

    Student(const char* name, int age, const char* major) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
        this->major = new char[strlen(major) + 1];
        strcpy(this->major, major);
    }

    char* getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    char* getMajor() const {
        return major;
    }

    Student(const Student& other) {
        copy(other);
    }

    void print()
    {
        cout<<name<<" ("<<age<<", "<<major<<")"<<endl;
    }
    ~Student(){

    }
};


class Classroom {
private:
    Student *students;
    int numStudents;
    int capacity;

    void copy(const Classroom& copied) {
        this->capacity = copied.capacity;
        this->numStudents = copied.numStudents;
        this->students = new Student[capacity];
        for (int i = 0; i < numStudents; i++) {
            this->students[i] = copied.students[i];
        }
    }

public:
    Classroom() {
        capacity = 10;
        numStudents = 0;
        students = new Student[capacity];
    }

    Classroom(int capacity) {
        this->capacity = capacity;
        numStudents = 0;
        students = new Student[capacity];
    }

    Classroom(const Classroom &other) {
        copy(other);
    }

    Classroom& operator=(const Classroom &other) {
        if (this != &other) {
            delete[] students;
            copy(other);
        }
        return *this;
    }

    void add(const Student& student) {
        if (numStudents < capacity) {
            students[numStudents] = student;
            numStudents++;
        }
    }

    void remove(const char *name) {
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].getName(), name) == 0) {
                for (int j = i; j < numStudents - 1; j++) {
                    students[j] = students[j + 1];
                }
                numStudents--;
                i--;
            }
        }
    }

    int getNumStudents() const {
        return numStudents;
    }

    Student *getStudents() const {
        return students;
    }

    void printStudents() const {
        for (int i = 0; i < numStudents; i++) {
            students[i].print();
        }
        cout<<endl;
    }

    ~Classroom() {
        delete[] students;
    }
};


float findMedianAge(Classroom &c){
    int numStudents=c.getNumStudents();
    int medianIndex = numStudents / 2;
    if (numStudents % 2 == 0) {
        return (c.getStudents()[medianIndex-1].getAge() + c.getStudents()[medianIndex].getAge()) / 2.0;
    }
    else {
        return c.getStudents()[medianIndex].getAge();
    }
    cout<<"After removing the elements: "<<endl;
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;

    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}
