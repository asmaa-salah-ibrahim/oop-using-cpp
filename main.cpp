#include <bits/stdc++.h>
using namespace std;
#define endl "\n"


class SmartBuffer {

private:
    int size;
    int * arr;
    int currentSize;
public :
    static int objectsCount;
    static int GetObjectsCount() {
        return objectsCount;
    }
    SmartBuffer operator+(const SmartBuffer& other) {
        if (this->currentSize== other.currentSize) {

           SmartBuffer result(size);
            for (int i=0;i<other.currentSize;i++) {
                result.arr[i]=this->arr[i]+other.arr[i];
            }
            return result;
        }else {
            throw ("can't do this operation because different size");
        }
    }
    friend void PrintInfo(const SmartBuffer& b);
    SmartBuffer() {
    size=5;
    currentSize=0;
    arr= new int [size]{};
        ++objectsCount;
    cout<<"Default Constructor Called";
}
    SmartBuffer(int s) {
    size=s;
        currentSize=0;
        ++objectsCount;
    arr= new int [size]{};
    cout<<"Parameterized Constructor Called";
}
    ~SmartBuffer() {
    delete []arr;
    --objectsCount;
    cout<< "Destructor Called";
}
   void Add(int num) {
    if (currentSize==size) {
        Expand();
    }
    arr[currentSize]=num;
    ++currentSize;
}
    void set(int num, int index) {
        if (index<currentSize && currentSize>0) {
            for (int i=0;i<currentSize;i++) {
                arr[index]=num;
            }
        }else {
            throw "not found in current Array";
        }
    }
    void Expand() {
    int *newArr= new int [size*2];
    for (int i=0 ;i<currentSize;i++) {
        newArr[i]= arr[i];
    }
    delete []arr;
    arr= newArr;
    size= size*2;

}
    void get( int index) {
        if (index<currentSize && currentSize>0) {
            cout<< arr[index];
        }else {
            throw "not found in current Array";
        }
    }
    //if need to return the value of arr[index] not cout the value
    int getIndex( int index ) {
   return arr[index];
}
    SmartBuffer& operator=(const SmartBuffer& other) {
      if (this!= &other) {
          this->size= other.size;
          this->currentSize= other.currentSize;
          delete [] this->arr;
          this->arr= new int [size];
          for (int i=0;i<currentSize;i++) {
              this-> arr[i]= other.arr[i];
          }
      }else {
          return *this;
      }

    }
    void print() {
    for (int i=0;i<currentSize;i++) {
        cout<< arr[i]<<" ";
    }
    cout<<endl;
    }
    SmartBuffer(const SmartBuffer& other) {
    size= other.size;
    currentSize= other.currentSize;
     arr = new int [size]{};
    for (int i=0 ;i<other.currentSize;i++) {
        arr[i]= other.arr[i];
    }
cout<<"Copy Constructor Called";
}

};
void PrintInfo(const SmartBuffer& b) {
    for (int i= 0;i<b.currentSize;i++) {
        cout<< b.arr[i]<<" ";
    }
    cout<<endl;
    cout<< "The Size of this array is "<<b.size<< "And the number of the current element is this array is "<<b.currentSize<<endl;
}


void Process1(SmartBuffer b) {
    cout<<" wellcome from function with pass by value";
    b.print();
}
//  void Process2(const SmartBuffer& b) {
//     cout<<"wellcome from function with pass by reference";
//     b.print();
// }
     int SmartBuffer::objectsCount=0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // copy constructor
    // assignment
    // self assignment
    // operator
    // friend
    // static
    // pass by value
    // pass by reference
    // return object
    // destructor order
    SmartBuffer b(2);
    b.Add(10);
    b.Add(20);
    b.Add(30);
    b.Add(40);
    b.Add(50);
    b.set(2,44);
    b.get(2);
    b.print();
    b.getIndex(20);
    SmartBuffer b2= b;
    b2=b;
    b.print();
    cout<< SmartBuffer::GetObjectsCount()<<endl;


    return 0;

}