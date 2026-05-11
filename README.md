# OOP using C++

Learning OOP in C++ through practical implementation without STL to deeply understand:

* Memory management
* Object lifecycle
* Copy behavior
* Ownership
* Object relationships

---

# Topics Covered

* Stack vs Heap
* Constructors
* Destructor
* Shallow Copy
* Deep Copy
* Copy Constructor
* Assignment Operator
* Self Assignment
* Pass by Value vs Pass by Reference
* Const Correctness
* Static Members
* Friend Functions
* Operator Overloading
* Object Lifecycle
* Relationships Between Classes
* Dependency Injection (DI)

---

# Learning Goals

This repository focuses on understanding how objects behave internally in memory instead of relying on STL containers.

## Main Goals

* Understand dynamic memory allocation
* Manually implement deep copy
* Understand ownership problems
* Understand object lifecycle
* Practice operator overloading
* Build strong OOP fundamentals for interviews

---

# SmartBuffer Class Overview

`SmartBuffer` is a custom dynamic array implementation built manually using raw pointers.

## Features

* Dynamic resizing
* Deep copy support
* Operator overloading
* Object counting using static members
* Manual memory management

---

# 1) Stack vs Heap

## Stack Allocation

```cpp
SmartBuffer b;
```

The object itself is created on the Stack.

### Characteristics

* Automatic lifetime management
* Fast allocation/deallocation
* Destroyed automatically when scope ends

---

## Heap Allocation

Inside the class:

```cpp
arr = new int[size];
```

The dynamic array is allocated on the Heap.

### Important Notes

* Memory must be released manually
* Heap memory survives until `delete` is called

---

## Important Idea

An object can live on the Stack while owning memory on the Heap.

Because of this, classes with raw pointers usually need:

* Constructor
* Destructor
* Copy Constructor
* Assignment Operator

---

# 2) Constructors

## Default Constructor

Responsible for:

* Initializing object state
* Allocating initial memory

```cpp
SmartBuffer()
{
    size = 5;
    currentSize = 0;
    arr = new int[size]{};
}
```

---

## Parameterized Constructor

Allows custom initial size.

```cpp
SmartBuffer(int s)
{
    size = s;
    currentSize = 0;
    arr = new int[size]{};
}
```

---

# 3) Destructor

Responsible for cleanup.

```cpp
~SmartBuffer()
{
    delete[] arr;
}
```

## Why Destructor Matters

If dynamically allocated memory is not released:

* Memory leak occurs

If shallow copy exists:

* Double delete may occur

---

# 4) Shallow Copy

## Problem

Default copy behavior copies the pointer address only.

```cpp
SmartBuffer b = a;
```

Both objects point to the same Heap memory.

## Problems Caused

* Shared memory unintentionally
* Modifying one object affects the other
* Double delete during destruction

---

# 5) Deep Copy

## Solution

Allocate new memory for each object.

Then copy values manually.

## Visualization

```txt
a ----> heap1
b ----> heap2
```

Same values, different memory locations.

## Benefits

* Safe destruction
* Independent objects
* No shared ownership problems

---

# 6) Copy Constructor

## Purpose

Creates a new object from an already existing object.

```cpp
SmartBuffer b2 = b1;
```

---

## Implementation

```cpp
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
```

---

## Why `const reference`?

```cpp
const SmartBuffer& other
```

### Why not pass by value?

Because pass by value itself creates a copy.

That would recursively call the Copy Constructor infinitely.

### Why const?

To guarantee the source object will not be modified.

---

# 7) Assignment Operator

## Purpose

Assign values between already existing objects.

```cpp
b2 = b1;
```

This is **NOT** Copy Constructor.

This is **Assignment Operator**.

---

## Implementation

```cpp
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
```

---

# 8) Self Assignment

## Problem

```cpp
b = b;
```

Without protection:

* Object may delete its own memory
* Then try copying from destroyed memory

## Solution

```cpp
if(this != &other)
```

---

# 9) Pass by Value vs Pass by Reference

## Pass by Value

```cpp
void Process(SmartBuffer b)
```

### Behavior

* Creates object copy
* Invokes Copy Constructor
* Slower
* Extra memory usage

---

## Pass by Reference

```cpp
void Process(SmartBuffer& b)
```

### Behavior

* No copy created
* Faster
* Works on original object

---

## Const Reference

```cpp
void Process(const SmartBuffer& b)
```

Best choice when only reading data.

### Advantages

* No copy
* Safe
* Efficient

---

# 10) Const Member Functions

Functions that do not modify object state should be marked as `const`.

## Examples

```cpp
int get(int index) const
void print() const
SmartBuffer operator+(const SmartBuffer& other) const
```

## Benefits

* Prevents accidental modification
* Allows usage with const objects
* Improves code readability

---

# 11) Operator Overloading

## Example

```cpp
SmartBuffer b4 = b1 + b2;
```

Allows custom objects to behave like built-in types.

---

## Implementation Idea

```cpp
SmartBuffer operator+(const SmartBuffer& other) const
```

### Internally

* Creates temporary result object
* Sums values
* Returns new object

---

# 12) Temporary Objects & Return by Value

Inside `operator+`:

```cpp
SmartBuffer result(currentSize);
return result;
```

`result` is a local temporary object.

The compiler may apply:

* RVO
* NRVO
* Copy Elision

to avoid unnecessary copying.

---

# 13) Static Members

Static members belong to the class itself, not individual objects.

## Example

```cpp
static int objectsCount;
```

Shared between all objects.

---

## Usage

Increment in constructor:

```cpp
++objectsCount;
```

Decrement in destructor:

```cpp
--objectsCount;
```

Access:

```cpp
SmartBuffer::GetObjectsCount()
```

---

# 14) Friend Functions

Friend functions are outside the class but can access private members.

## Example

```cpp
friend void PrintInfo(const SmartBuffer& b);
```

Useful for utility/helper functions.

---

# 15) Object Lifecycle Example

```cpp
SmartBuffer b1;
SmartBuffer b2 = b1;
```

## Internally

1. Constructor for `b1`
2. Heap memory allocation
3. Copy Constructor for `b2`
4. New Heap allocation
5. Deep copy values
6. Destructor for `b2`
7. Destructor for `b1`

---

# 16) Common Bugs & Pitfalls

## Memory Leak

Occurs when allocated memory is never deleted.

---

## Double Delete

Occurs when:

* Multiple objects own same pointer
* Shallow copy exists

---

## Infinite Recursion

Occurs if Copy Constructor takes parameter by value:

```cpp
SmartBuffer(SmartBuffer other)
```

---

## Self Assignment Bug

Occurs if Assignment Operator does not check:

```cpp
if(this != &other)
```

---

# 17) Interview Notes

## Difference Between

```cpp
SmartBuffer b2 = b1;
```

and

```cpp
b2 = b1;
```

| Statement              | Meaning             |
| ---------------------- | ------------------- |
| `SmartBuffer b2 = b1;` | Copy Constructor    |
| `b2 = b1;`             | Assignment Operator |

---

## Why pass by const reference?

Because it:

* Avoids copying
* Improves performance
* Protects object from modification

---

## Why classes with raw pointers need deep copy?

Because default shallow copy copies addresses only.

This causes:

* Shared ownership
* Double delete
* Undefined behavior

---

# 18) Questions & Discoveries During Learning

## Why does pass by value invoke Copy Constructor?

Because function parameters become new objects internally.

---

## Why did Copy Constructor appear during:

```cpp
SmartBuffer b4 = b1 + b2;
```

Because `operator+` returns an object by value.

Compiler may optimize this using copy elision.

---

## Why make `operator+` const?

Because addition should not modify either object.

---

## Why return `*this` in Assignment Operator?

Allows chaining:

```cpp
a = b = c;
```

---

# 19) Relationships Between Classes

After understanding object lifecycle, memory management, and copy behavior, the next step is understanding how objects interact with each other.

Object relationships describe:

* How classes communicate
* Who owns whom
* Object lifetime dependencies
* Coupling level between classes

---

## Main Relationship Types

* Association
* Aggregation
* Composition
* Inheritance

---

# 20) Association

Association is a weak relationship between two independent classes.

The relationship exists only for a temporary usage, process, or action.

---

## Characteristics

* No ownership
* Objects are independent
* Each object manages its own lifecycle

Usually implemented using:

* Function parameters
* Method calls
* Local objects

---

## Example

```cpp
class Marker {
public:
    void Write() {
        cout << "Writing...";
    }
};

class Instructor {
public:
    void Teach(Marker& marker) {
        marker.Write();
    }
};
```

---

## Explanation

Here:

* Instructor uses Marker temporarily
* Marker can exist without Instructor
* Instructor does not own Marker

This is considered:

* Loose coupling
* Temporary interaction

---

## Why Pass by Reference in Association?

Usually objects are passed by reference:

```cpp
void Teach(Marker& marker)
```

instead of:

```cpp
void Teach(Marker marker)
```

because pass by value creates a copy object.

This means:

* Copy Constructor invoked
* Extra memory allocation
* Unnecessary object creation
* Worse performance for large objects

Reference avoids:

* Copying
* Temporary object creation

and allows working with the original object directly.

---

# 21) Dependency Injection (DI)

Dependency Injection is a design technique where an object receives its dependencies from outside instead of creating them internally.

---

## Tight Coupling Example

```cpp
class Service {
private:
    Database db;
};
```

### Problems

* Service creates Database itself
* Hard to replace Database
* Hard to test
* Tightly coupled

---

## Using Dependency Injection

```cpp
class Service {
private:
    Database& db;

public:
    Service(Database& database)
        : db(database) {}
};
```

---

## Benefits

* Service does not create Database
* Dependency injected from outside
* Lower coupling
* Easier testing
* Easier maintenance

---

# Association vs Dependency Injection

| Association                  | Dependency Injection                    |
| ---------------------------- | --------------------------------------- |
| Temporary usage relationship | Long-term dependency                    |
| Used during method execution | Stored as member variable               |
| No ownership                 | Dependency becomes part of object state |
| Weak relationship            | Architectural design technique          |

DI is built on top of association concepts but is more architectural and long-term.

---

# Future Extension (SOLID / Interfaces)

Dependency Injection becomes more powerful when combined with abstractions.

```cpp
class IDatabase {
public:
    virtual void Save() = 0;
};
```

Now `Service` depends on abstraction instead of concrete implementation:

```cpp
class Service {
private:
    IDatabase& db;
};
```

## Benefits

* Open/Closed Principle
* Easier database replacement
* Better scalability
* Cleaner architecture
* Lower coupling

---

# 22) Common Mistakes

* Association != ownership
* Pass by reference is not the relationship itself
* Pass by reference is only a passing mechanism
* DI is not only for memory optimization
* The main purpose of DI is reducing coupling
* Constructor injection affects object initialization and lifecycle
