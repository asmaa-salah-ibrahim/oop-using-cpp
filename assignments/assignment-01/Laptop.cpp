#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

class Laptop {
private:
    char*brand;
public:
    Laptop() {
        brand=nullptr;
        cout<<"Hello from Laptop parameterless ctor"<<endl;
    }



    Laptop(char*b) {

        if (b!=nullptr) {
            int namesize=strlen(b);
            brand= new char[namesize+1]{};
            for (int i=0;i<namesize;i++) {
                brand[i]=b[i];
            }
            brand[namesize]='\0';
        }

        cout<<"Hello from Laptop parameterized ctor"<<endl;
    }



    Laptop(const Laptop&other) {
       if (other.brand !=nullptr) {
           int namesize=strlen(other.brand);
           brand= new char[namesize+1]{};
           for (int i=0;i<namesize;i++) {
               brand[i]=other.brand[i];
           }
           brand[namesize]='\0';
       }
        cout<<"Hello form Laptop Copy Constructor Called"<<endl;
    }



    Laptop& operator=(const Laptop &other) {
        if (&other!=this ) {
            int namesize=strlen(other.brand);
            delete[]brand;
            brand= new char[namesize+1]{};
            for (int i=0;i<namesize;i++) {
                brand[i]=other.brand[i];


            }
            brand[namesize]='\0';
        }
        return *this;
    }
        ~Laptop() {
            delete []brand;
            cout<<"Hello from laptop dtor"<<endl;
        }

};