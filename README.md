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

---

# 20) Association

Association is a weak relationship between two independent objects.

The relationship exists only to perform a temporary action or process.

---

## Main Characteristics

* No ownership
* Independent lifecycles
* Temporary interaction

Usually exists inside:

* Function parameters
* Local scope
* Method execution

---

## Example

```cpp
class Marker {
public:
    void Write() {}
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

* Instructor does NOT own Marker
* Marker lifecycle is independent
* Relationship exists only during `Teach()`

This is considered:

* Loose coupling
* Temporary interaction

---

## Why Pass by Reference Here?

Usually objects are passed by reference:

```cpp
void Teach(Marker& marker)
```

instead of:

```cpp
void Teach(Marker marker)
```

because pass-by-value creates a copy object.

That means:

* Copy Constructor invoked
* Extra object creation
* Extra memory usage
* Extra destruction later

Architecturally:

`Instructor` is NOT responsible for creating or owning `Marker`.

So copying it makes no sense conceptually.

The relationship is only temporary usage.

---

## Important Clarification

The main reason for pass-by-reference is NOT only memory optimization.

It is also semantic correctness.

Meaning:

> "I want to USE this object, not OWN or COPY it."

---

# 21) Aggregation

Aggregation is a longer-lived relationship between independent objects.

One object stores a reference or pointer to another object without owning it.

---

## Example

```cpp
class Instructor {
public:
    string name;
};

class Room {
private:
    Instructor* inst;

public:
    Room() {
        inst = nullptr;
    }

    void SetInstructor(Instructor* i) {
        inst = i;
    }
};
```

---

## What Happens Here?

* Room does NOT create Instructor
* Room does NOT destroy Instructor
* Both objects have independent lifecycles
* Relationship can last longer than a single function scope

This is the key difference from association.

---

## Important Insight

The relationship happens AFTER object creation.

Example:

```cpp
Instructor ins;
Room room;

room.SetInstructor(&ins);
```

Both objects already exist independently.

Then the relationship is formed later.

---

## Difference Between Association and Aggregation

### Association

Temporary usage relationship.

Usually implemented using:

* Function parameters
* Local interaction
* Short-lived method calls

The relationship is tied to method execution.

---

### Aggregation

Longer-lived relationship.

One object stores a reference or pointer to another object.

The relationship is tied to:

* Member variables
* Stored references
* Object state

But still:

* No ownership
* Independent destruction
* Independent object lifecycles

---

## Important C++ Memory Note

In C++:

Raw pointers do NOT become `nullptr` automatically.

Example:

```cpp
Instructor* ptr = &ins;
```

If `ins` is destroyed, then:

```cpp
ptr
```

becomes a:

* Dangling Pointer

NOT `nullptr`.

So the pointer should be reset manually when appropriate:

```cpp
ptr = nullptr;
```

---

## C# Difference

In C#:

* Garbage Collector handles managed memory
* Objects are destroyed automatically when unreachable
* Less manual memory management is required

However:

Garbage Collector does NOT instantly destroy objects.

The runtime decides when collection should happen based on optimization and application state.

---

# 22) Dependency Injection (DI)

Dependency Injection (DI) is NOT a relationship type.

It is a:

* Design Pattern
* Architectural Technique

used to reduce coupling between components.

---

## Core DI Idea

Instead of this:

```cpp
class Service {
private:
    Database db;
};
```

which creates tight coupling,

we do this:

```cpp
class Service {
private:
    IDatabase& db;

public:
    Service(IDatabase& database)
        : db(database) {}
};
```

---

## Why Is This Powerful?

Now:

* Service does NOT know the concrete database type
* Service depends on abstraction
* Database implementation can change without modifying Service

This supports:

* Open/Closed Principle
* Testability
* Scalability
* Loose Coupling

---

## Extremely Important Clarification

Dependency Injection is NOT mainly about memory optimization.

The MAIN purpose is:

* Reducing coupling
* Depending on abstractions instead of concrete implementations

Memory reuse or singleton usage can be side effects in some systems, but they are NOT the primary goal of DI.

---

## Another Important Clarification

Dependency Injection often USES aggregation internally.

Because:

```cpp
IDatabase& db;
```

means the service stores a reference to an external object.

However:

| Concept     | Type              |
| ------------| ----------------- |
| DI          | Design Pattern    |
| Aggregation | Relationship Type |

DI may be implemented USING aggregation, but they are not the same thing.
------------------------------




# 23) Composition

Composition is a strong ownership relationship between classes.

It represents:

```txt
Has-A Relationship
```

Example:

```txt
Room HAS walls
```

The owned object is considered part of the owner object itself.

---

## Main Idea

Unlike:

* Association
* Aggregation

In Composition:

* Owner object is responsible for:
  * Creation
  * Lifetime
  * Destruction

of the contained objects.

Meaning:

If `Room` is destroyed,
its `Wall` objects must also be destroyed.

The owned objects cannot logically exist independently from the owner.

---

# Two Common Composition Implementations

---

## 1) Static Member Composition

Used when size/count is known at compile time.

### Example

```cpp
class Wall {
};

class Room {
private:
    Wall walls[4];
};
```

---

### Important Behavior

The `walls` objects are created automatically before entering:

```txt
Room constructor body
```

because member objects are constructed first.

---

### Destruction Order

When `Room` is destroyed:

1. Room destructor executes
2. Member destructors execute automatically

No manual deletion required.

---

### Characteristics

* Fixed size
* Automatic lifetime management
* No manual memory handling
* Safer
* Stack-style ownership

---

## 2) Dynamic Composition

Used when size is determined at runtime.

### Example

```cpp
class Room {
private:
    Wall* walls;
    int count;

public:
    Room(int c)
    {
        count = c;
        walls = new Wall[count];
    }

    ~Room()
    {
        delete[] walls;
    }
};
```

---

### Important Difference

Here:

```cpp
new Wall[count]
```

allocates memory dynamically on the Heap.

So now `Room` becomes responsible for:

* Allocation
* Deallocation
* Ownership

---

## Why Destructor Is Required?

Because:

```cpp
walls = new Wall[count];
```

allocates Heap memory.

Without:

```cpp
delete[] walls;
```

a memory leak occurs.

---

## Why Composition Leads to Deep Copy Problems?

Because:

```cpp
walls
```

is a raw pointer.

Default copy behavior performs:

```txt
Shallow Copy
```

Meaning:

```txt
room1.walls ----\
                 ---> same heap memory
room2.walls ----/
```

Now both objects think they own the same memory.

---

# Resulting Problems

## 1) Dangling Pointer

When first object is destroyed:

```cpp
delete[] walls;
```

second object still points to deleted memory.

---

## 2) Double Delete

When second destructor runs:

```cpp
delete[] walls;
```

same memory gets deleted again.

This causes:

* Undefined Behavior
* Crashes
* Memory corruption

----
Classes that use dynamic composition with raw pointers usually require proper copy control.
# Solution → Deep Copy

You must implement:

* Copy Constructor
* Assignment Operator
* Destructor

This is called:

```txt
Rule of Three
```

---

## Deep Copy Goal

Instead of:

```txt
room1.walls ----\
                 ---> heap1
room2.walls ----/
```

we want:

```txt
room1.walls ---> heap1
room2.walls ---> heap2
```

Each object owns independent memory.

---

## Why Assignment Operator Also Matters?

Because:

```cpp
room2 = room1;
```

does NOT invoke Copy Constructor.

Both objects already exist.

So Assignment Operator must also perform:

```txt
Deep Copy
```

instead of shallow pointer copying.

---

# Key Architectural Difference

| Relationship | Ownership | Lifetime Dependency |
| --- | --- | --- |
| Association | No | Independent |
| Aggregation | No | Independent |
| Composition | Yes | Dependent |

---

# Most Important Concept

Composition means:

```txt
"If owner dies,
owned objects must die too."
```

That is the core idea behind composition.


## Important Note

Static composition usually avoids shallow copy problems automatically because member objects are copied individually.

Problems mainly appear when composition uses raw pointers and dynamic memory allocation.
------------------------------------
## Real World Example — Composition vs Aggregation

This example demonstrates the difference between:

* Composition → Natural Arms
* Aggregation → Prosthetic Arm

---

# Composition Example → Natural Arms

Natural arms are considered part of the Human itself.

Meaning:

* Human creates them
* Human owns them
* Human destroys them automatically

If Human dies, the natural arms also die.

This represents:

```txt
Strong Ownership
Composition Relationship
```

### Example

```cpp
#include <iostream>
using namespace std;

class NaturalArm {
public:
    NaturalArm() {
        cout << "Natural Arm Created\n";
    }

    ~NaturalArm() {
        cout << "Natural Arm Destroyed\n";
    }
};

class Human {
private:
    NaturalArm* arms;

public:
    Human() {
        cout << "Human Created\n";

        // Human creates its own natural arms
        arms = new NaturalArm[2];
    }

    ~Human() {
        // Human destroys its own natural arms
        delete[] arms;

        cout << "Human Destroyed\n";
    }
};

int main() {
    Human h;
}
```

---

## Important Notes

Here:

```cpp
arms = new NaturalArm[2];
```

means:

* Human allocated memory
* Human owns memory
* Human must deallocate memory

This is:

```txt
Dynamic Composition
```

Because ownership exists.

---

# Aggregation Example → Prosthetic Arm

A prosthetic arm is NOT created by Human.

Human only uses it temporarily.

Meaning:

* Human does NOT own it
* Human does NOT destroy it
* Prosthetic arm can exist independently

This represents:

```txt
Aggregation Relationship
```

---

### Example

```cpp
#include <iostream>
using namespace std;

class ProstheticArm {
public:
    ProstheticArm() {
        cout << "Prosthetic Arm Created\n";
    }

    ~ProstheticArm() {
        cout << "Prosthetic Arm Destroyed\n";
    }

    void Use() {
        cout << "Using Prosthetic Arm\n";
    }
};

class Human {
private:
    ProstheticArm* prosthetic;

public:
    Human() {
        prosthetic = nullptr;
    }

    void AttachArm(ProstheticArm* arm) {
        prosthetic = arm;
    }

    void UseArm() {
        if(prosthetic != nullptr) {
            prosthetic->Use();
        }
    }

    void RemoveArm() {
        prosthetic = nullptr;
    }
};

int main() {

    ProstheticArm arm;

    Human h;

    // Aggregation relationship formed here
    h.AttachArm(&arm);

    h.UseArm();

    h.RemoveArm();
}
```

---

# Key Difference

| Relationship | Ownership | Responsible For Creation | Responsible For Destruction |
| --- | --- | --- | --- |
| Composition | Yes | Owner Object | Owner Object |
| Aggregation | No | External Object | External Object |

---

# Core Idea

## Composition

```txt
"If owner dies,
owned objects must also die."
```

---

## Aggregation

```txt
"Objects can exist independently."
```
-----------------------------------------------
