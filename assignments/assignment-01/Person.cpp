#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

class Person {
   // private:
    //public:
    protected:
    char* name;
    int age;
    int nameLength;
public:
    //parameter less ctor
    Person() {
         nameLength=0;
        name=nullptr;
        age=0;
        cout<<"Welcome Form Person parameterless ctor"<<endl;
    }

    //parameterized ctor
    Person(const char* n, int a,int nameSize) {
        nameLength=nameSize;
        name = new char[nameSize+1]{};
        for (int i=0;i<nameSize;i++) {
            name[i]=n[i];

        }
        name[nameSize] = '\0';
        age= a;
        cout<< "Welcome form Person Parameterized ctor"<<endl;
    }




    //copy constructor
    Person(const Person&other) {
        nameLength=other.nameLength;
        age=other.age;
      if (other.name != nullptr) {
          name = new char[nameLength + 1];
          for (int i=0;i<nameLength;i++) {
              name[i]=other.name[i];
          }
          name[nameLength] = '\0';
          cout<<"Welcome Form Person copy ctor"<<endl;
      }else {
          name = nullptr;
      }


    }
    ~Person() {
         delete []name;
        cout<< "Hello From Person Destructo"<<endl;
    }
    //Person& operator=(const Person& other);
    Person& operator=(const Person& other) {
      if (&other!=this) {
          nameLength=other.nameLength;
          age= other.age;
        if (other.name!=nullptr) {
              delete [] name;
          name= new char[nameLength+1]{};
          for (int i=0;i<nameLength;i++) {
              name[i]=other.name[i];
          }
          name[nameLength]='\0';

      }else {
          name=nullptr;
      }
      }
        return *this;
    }
    //void SetName(const char* n);
    void SetName(const char*n) {
        if (n!=nullptr ) {
            delete []name;
           nameLength= strlen(n);
          name= new char[nameLength+1]{};
          strcpy(name, n);
            name[nameLength]='\0';

        }
else {
    throw"Invalid Name";
}
    }
    void Print() const {
        if (name!= nullptr) {
            cout<< "Name: "<<name <<"\tAge: "<< age<<endl;
        }else {
            throw "Not found the name";
        }
    }



};


