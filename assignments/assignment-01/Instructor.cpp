#include <bits/stdc++.h>
#include "Person.cpp"
using namespace std;
#define endl "\n"


// 3) Instructor Class
// Inheritance
// class Instructor : public Person
class Instructor : public Person {
private:
    double salary;


public:
    Instructor():Person() {
        salary=0;

        cout<<"Hello form instrutor ctor"<<endl;
    }
    Instructor(const char* n, int a, double s):Person(n,a,strlen(n)) {

        if (s>6000) {
            salary=s;
        }else {
            salary=6000;
        }
        age=0;
        cout<<"Hello form instrutor parameterize ctor"<<endl;
    }
    void Teach() {

        cout<< name<<" is teaching..........."<<endl;
    }
    void Print() const {
        Person::Print();
        cout<<"\tSalary: "<<salary<<endl;
    }
};

