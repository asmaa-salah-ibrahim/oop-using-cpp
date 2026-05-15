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

    //+overloading
    SmartBuffer operator+(const SmartBuffer& other)const {
        if (this->currentSize== other.currentSize) {

           SmartBuffer result(currentSize);
            result.currentSize= this->currentSize;
            for (int i=0;i<other.currentSize;i++) {
                result.arr[i]=this->arr[i]+other.arr[i];
            }
            return result;
        }else {
            throw ("can't do this operation because different size");
        }
    }

    //defination of friend function
    friend void PrintInfo(const SmartBuffer& b);


    //Constructor
    SmartBuffer() {
    size=5;
    currentSize=0;
    arr= new int [size]{};
        ++objectsCount;
    cout<<"Default Constructor Called"<<endl;
}

    //parameterized constructor
    SmartBuffer(int s) {
    size=s;
        currentSize=0;
        ++objectsCount;
    arr= new int [size]{};
    cout<<"Parameterized Constructor Called"<<endl;
}

    //destrcutor
    ~SmartBuffer() {
    delete []arr;
    --objectsCount;
    cout<< "Destructor Called"<<endl;
}

    //add Function
   void Add(int num) {
    if (currentSize==size) {
        Expand();
    }
    arr[currentSize]=num;
    ++currentSize;
}

    //set Function
    void set(int num, int index) {
        if (index<currentSize && currentSize>0&& index>=0) {
                arr[index]=num;

        }else {
            throw "not found in current Array";
        }
    }


    //Expand Function
    void Expand() {
    int *newArr= new int [size*2];
    for (int i=0 ;i<currentSize;i++) {
        newArr[i]= arr[i];
    }
    delete []arr;
    arr= newArr;
    size= size*2;

}

    //get Function
    //const because it does't change the state of the object
    int  get( int index)const {
        if (index<currentSize && currentSize>0&& index>=0) {
            return  arr[index];
        }else {
            throw "not found in current Array";
        }
    }



//= overloading
    SmartBuffer& operator=(const SmartBuffer& other) {
      if (this!= &other) {
          this->size= other.size;
          this->currentSize= other.currentSize;
          delete [] this->arr;
          this->arr= new int [size];
          for (int i=0;i<currentSize;i++) {
              this-> arr[i]= other.arr[i];
          }
      }
        return *this;
    }


    //print function
    //const because it does't change the state of the object
    void print()const {
    for (int i=0;i<currentSize;i++) {
        cout<< arr[i]<<" ";
    }
    cout<<endl;
    }


    //copy constructor
    SmartBuffer(const SmartBuffer& other) {
    size= other.size;
    currentSize= other.currentSize;
     arr = new int [size]{};
    for (int i=0 ;i<other.currentSize;i++) {
        arr[i]= other.arr[i];
    }
        ++objectsCount;
cout<<"Copy Constructor Called"<<endl;
}

};
class Marker {
public :
    string color ;
    Marker(string color) {
        this->color= color;
    }
    void Write()const {
        cout<<"The Marker with color "<<this->color<<" is write now"<<endl;

    }
};
class Instructor {
private:
    string name;
public:
    Instructor(string value) {
        name= value;
    }
    void setName(string name) {
       this->name= name;
    }
    void WriteByMarker(Marker &mark) {
      mark.Write();
    }

};

//standalone fucntion with const input paramenter
//conpy constructor will not invoked here
void PrintInfo(const SmartBuffer& b) {
    for (int i= 0;i<b.currentSize;i++) {
        cout<< b.arr[i]<<" ";
    }
    cout<<endl;
    cout<< "The Size of this array is "<<b.size<< "And the number of the current element is this array is "<<b.currentSize<<endl;
}

// standalone function pass by value
//conpy constructor will  invoked here
void Process1(SmartBuffer b) {
    cout<<" wellcome from function with pass by value";
    b.print();
}

//statndalone function with const , ref input parameter
//conpy constructor will not invoked here
 void Process2(const SmartBuffer& b) {
    cout<<"wellcome from function with pass by reference";
    b.print();
}

//the intialization of static varaiable
     int SmartBuffer::objectsCount=0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
   SmartBuffer b(2);
   b.Add(10);
   b.Add(20);
   b.Add(30);
    b.Add(40);
    b.Add(50);
    b.set( 44,1);
   cout<< b.get(2)<<endl;
    b.print();
    SmartBuffer b2= b;
    b2.print();
   SmartBuffer b3(2);
   b3.Add(20);
   b3.Add(100);
   b3.print();
   cout<<"B3 after overloading "<<endl;
   b3=b;
   b3.print();

   PrintInfo(b3);
   Process1(b3);
   Process2(b3);
   cout<< SmartBuffer::GetObjectsCount()<<endl;
   b=b;//return *this;
   SmartBuffer b4 = b + b3;
   b4.print();

Marker mark("Red");
Instructor inst("Omer");
    inst.WriteByMarker(mark);



    return 0;

}