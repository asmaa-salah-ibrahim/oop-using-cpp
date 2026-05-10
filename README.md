# OOP using C++

Learning OOP in C++ through practical implementation without STL to deeply understand:
- memory management
- object lifecycle
- copy behavior
- ownership
- object relationships

---

# Topics Covered

- Stack vs Heap
- Constructors
- Destructor
- Shallow Copy
- Deep Copy
- Copy Constructor
- Assignment Operator
- Self Assignment
- Pass by Value vs Pass by Reference
- Const Correctness
- Static Members
- Friend Functions
- Operator Overloading
- Object Lifecycle

---

# Learning Goals

This repository focuses on understanding how objects behave internally in memory instead of relying on STL containers.

Main goals:
- understand dynamic memory allocation
- manually implement deep copy
- understand ownership problems
- understand object lifecycle
- practice operator overloading
- build strong OOP fundamentals for interviews

---

# SmartBuffer Class Overview

`SmartBuffer` is a custom dynamic array implementation built manually using raw pointers.

Main features:
- dynamic resizing
- deep copy support
- operator overloading
- object counting using static members
- manual memory management

---

# 1) Stack vs Heap

## Stack Allocation

```cpp
SmartBuffer b;
object itself is created on the Stack
automatic lifetime management
Heap Allocation

Inside the class:

arr = new int[size];
dynamic array is allocated on the Heap
memory must be released manually
Important Idea

An object can live on the Stack while owning memory on the Heap.

Because of this, classes with raw pointers usually need:

Constructor
Destructor
Copy Constructor
Assignment Operator
2) Constructors
Default Constructor

Responsible for:

initializing object state
allocating initial memory
SmartBuffer()
{
    size = 5;
    currentSize = 0;
    arr = new int[size]{};
}
Parameterized Constructor

Allows custom initial size.

SmartBuffer(int s)
{
    size = s;
    currentSize = 0;
    arr = new int[size]{};
}
3) Destructor

Responsible for cleanup.

~SmartBuffer()
{
    delete[] arr;
}
Why Destructor Matters

If dynamically allocated memory is not released:

memory leak occurs

If shallow copy exists:

double delete may occur
4) Shallow Copy
Problem

Default copy behavior copies the pointer address only.

Example:

SmartBuffer b = a;

Both objects point to the same Heap memory.

Problems Caused
shared memory unintentionally
modifying one object affects the other
double delete during destruction
5) Deep Copy
Solution

Allocate new memory for each object.

Then copy values manually.

Visualization
a ----> heap1
b ----> heap2

Same values, different memory locations.

Benefit
safe destruction
independent objects
no shared ownership problems
6) Copy Constructor
Purpose

Creates a new object from an already existing object.

Example:

SmartBuffer b2 = b1;
Implementation
SmartBuffer(const SmartBuffer& other)
{
    size = other.size;
    currentSize = other.currentSize;

    arr = new int[size]{};

    for(int i = 0; i < currentSize; i++)
    {
        arr[i] = other.arr[i];
    }
}
Why const reference?
const SmartBuffer& other
Why not pass by value?

Because pass by value itself creates a copy.

That would recursively call Copy Constructor infinitely.

Why const?

To guarantee the source object will not be modified.

7) Assignment Operator
Purpose

Assign values between already existing objects.

Example:

b2 = b1;

This is NOT Copy Constructor.

This is Assignment Operator.

Implementation
SmartBuffer& operator=(const SmartBuffer& other)
{
    if(this != &other)
    {
        delete[] arr;

        size = other.size;
        currentSize = other.currentSize;

        arr = new int[size];

        for(int i = 0; i < currentSize; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    return *this;
}
8) Self Assignment
Problem
b = b;

Without protection:

object may delete its own memory
then try copying from destroyed memory
Solution
if(this != &other)
9) Pass by Value vs Pass by Reference
Pass by Value
void Process(SmartBuffer b)
Behavior
creates object copy
invokes Copy Constructor
slower
extra memory usage
Pass by Reference
void Process(SmartBuffer& b)
Behavior
no copy created
faster
works on original object
Const Reference
void Process(const SmartBuffer& b)

Best choice when only reading data.

Advantages:

no copy
safe
efficient
10) Const Member Functions

Functions that do not modify object state should be marked as const.

Example:

int get(int index) const
void print() const
SmartBuffer operator+(const SmartBuffer& other) const
Benefits
prevents accidental modification
allows usage with const objects
improves code readability
11) Operator Overloading
Example: operator+
SmartBuffer b4 = b1 + b2;

Allows custom objects to behave like built-in types.

Implementation Idea
SmartBuffer operator+(const SmartBuffer& other) const

Creates:

temporary result object
sums values
returns new object
12) Temporary Objects & Return by Value

Inside operator+:

SmartBuffer result(currentSize);
return result;

result is a local temporary object.

The compiler may apply:

RVO
NRVO
copy elision

to avoid unnecessary copying.

13) Static Members

Static members belong to the class itself, not individual objects.

Example:

static int objectsCount;

Shared between all objects.

Usage

Increment in constructor:

++objectsCount;

Decrement in destructor:

--objectsCount;

Access:

SmartBuffer::GetObjectsCount()
14) Friend Functions

Friend functions are outside the class but can access private members.

Example:

friend void PrintInfo(const SmartBuffer& b);

Useful for utility/helper functions.

15) Object Lifecycle Example
SmartBuffer b1;
SmartBuffer b2 = b1;
Internally
Constructor for b1
Heap memory allocation
Copy Constructor for b2
New Heap allocation
Deep copy values
Destructor for b2
Destructor for b1
16) Common Bugs & Pitfalls
Memory Leak

Occurs when:

allocated memory is never deleted
Double Delete

Occurs when:

multiple objects own same pointer
shallow copy exists
Infinite Recursion

Occurs if Copy Constructor takes parameter by value:

SmartBuffer(SmartBuffer other)
Self Assignment Bug

Occurs if Assignment Operator does not check:

if(this != &other)
17) Interview Notes
Difference Between
SmartBuffer b2 = b1;

and

b2 = b1;
First
Copy Constructor
creating new object
Second
Assignment Operator
assigning existing object
Why pass by const reference?

Because it:

avoids copying
improves performance
protects object from modification
Why classes with raw pointers need deep copy?

Because default shallow copy copies addresses only.

This causes:

shared ownership
double delete
undefined behavior
18) Questions & Discoveries During Learning
Why does pass by value invoke Copy Constructor?

Because function parameters become new objects internally.

Why did Copy Constructor appear during:
SmartBuffer b4 = b1 + b2;

Because operator+ returns an object by value.

Compiler may optimize this using copy elision.

Why make operator+ const?

Because addition should not modify either object.

Why return *this in Assignment Operator?

Allows chaining:

a = b = c;
