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
