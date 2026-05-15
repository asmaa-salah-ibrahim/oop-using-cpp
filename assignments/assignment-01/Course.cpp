#include <bits/stdc++.h>
#include "Instructor.cpp"
using namespace std;
#define endl "\n"
class Course {
private:
    char* courseName;
    Instructor* instructor;

public:
    Course() {
        instructor=nullptr;
        courseName=nullptr;
        cout<<"Hello form Course parameterless ctor"<<endl;
    }
    Course(const char* name) {
        if (name!=nullptr) {
            strcpy(courseName,name);
        }else {
            courseName=nullptr;
        }
        instructor=nullptr;
        cout<<"Hello from parameterized ctor"<<endl;
    }
    void SetInstructor(Instructor* i) {
        if (i!=nullptr)
            instructor=i;
    }
    void Print() const {

            cout<< "Course: "<<courseName<<endl;
        cout<< instructor<<endl;
    }

    ~Course() {
        delete []courseName;
        cout<< "Hello from dtor"<<endl;
        //can't destroy instructor here because is not my job it's aggregation relationship just use object  inside the function scope
    }

};




// ________________________________________
// Important Rule
// This is WRONG:
// delete instructor;
// inside Course destructor.
// Why?
// Because aggregation is NOT ownership.
// ________________________________________
