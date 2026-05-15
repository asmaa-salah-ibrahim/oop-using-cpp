#include <bits/stdc++.h>
#include "Person.cpp"
using namespace std;
#define endl "\n"


class Student: public Person {
private:
    int studentId;
    float gpa;
public:
    Student():Person() {
        gpa=0.0;
        studentId=0;
        cout<< "Hello from parameterlesss ctor"<<endl;
    }
    Student(const char* n, int a, int id, float g):Person(n,a,strlen(n)) {

        studentId=id;
        gpa=g;

        cout<< "Hello Form Student parameeterized ctor"<<endl;
    }

    void Study() {
     cout<<name<<" is studing nw"<<endl;
    }

    void Print() const{
        Person::Print();
        cout<<"\tStudent Id: "<<studentId<<endl;
    }

};



