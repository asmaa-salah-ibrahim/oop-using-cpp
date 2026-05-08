# OOP using C++

Learning OOP using practical examples and implementing concepts manually (without STL) to deeply understand memory management, copy behavior, and object lifecycle.

---

## 1) Stack vs Heap

- لما بعمل:

```cpp
MyList x;
```

الـ object نفسه بيتcreate على **Stack**.

- لكن لو جواه dynamic allocation زي:

```cpp
arr = new int[size];
```

فالـ array نفسها بتتحجز على **Heap**.

- وبالتالي object ممكن يكون على Stack لكن جواه data على Heap.

- هنا لازم أهتم بـ:
    - Constructor → allocate memory
    - Destructor → deallocate memory
    - Copy Constructor → deep copy
    - Assignment Operator → deep copy

---

## 2) Shallow Copy

- لو عملت copy عادي لobject فيه pointer:

```cpp
MyList b = a;
```

- فاللي بيتcopy هو **address فقط**.

- يعني الاتنين بيشاوروا على نفس المكان في Heap.

- لو واحد عدل → التاني هيتأثر.

- ولو Destructor اشتغل → هيحصل double delete.

**Problem:** shared memory unintentionally.

---

## 3) Deep Copy

- بدل ما أنقل address، بعمل allocate memory جديدة.

- وبعد كده أنقل values.

- كده كل object يبقى له address خاص بيه.

```cpp
a ---> heap1
b ---> heap2
```

- نفس values لكن different addresses.

**Benefit:** no shared memory / safe destruction.

---

## 4) Copy Constructor

- وظيفته:

create new object based on already existing object.

```cpp
MyList b = a;
```

هنا بيتنادى Copy Constructor.

- كمان لو object اتبعت **pass by value**:

```cpp
Process(a);
```

بيتcreate copy → Copy Constructor invoked.

- لازم ياخد:

```cpp
const MyList& other
```

ليه؟

- لو by value → infinite recursion.
- const → عشان أضمن عدم تعديل source object.

---

## 5) Assignment Operator

لو object already exists:

```cpp
b = a;
```

دي مش Copy Constructor.

دي Assignment Operator.

لازم أعمل overload لـ:

```cpp
MyList& operator=(const MyList& other)
```

وأراعي:

### self assignment

```cpp
a = a;
```

لازم check:

```cpp
if(this != &other)
```

### steps:

- delete old memory
- allocate new memory
- copy values
- return *this

---

## 6) Pass by Value vs Pass by Reference

## Pass by Value

```cpp
void Process(MyList x)
```

- object copy created
- Copy Constructor invoked
- slower
- extra memory

---

## Pass by Reference

```cpp
void Process(MyList& x)
```

- no copy
- faster
- works on same object

---

## Const Reference

```cpp
void Process(const MyList& x)
```

best choice if only reading.

- no copy
- safe
- fast

---

## 7) Destructor

وظيفته cleanup.

```cpp
~MyList()
{
    delete[] arr;
}
```

مسؤول عن deallocate dynamic memory.

لو نسيت destructor → memory leak.

لو shallow copy موجود → double delete.

---

## 8) Static Members

static member belongs to class itself not object.

مش لكل object نسخة.

نسخة واحدة shared.

Example:

```cpp
static int objectsCount;
```

كل object يتcreate:

```cpp
++objectsCount;
```

كل object يتdestroy:

```cpp
--objectsCount;
```

والوصول له:

```cpp
MyList::GetObjectsCount()
```

---

## 9) Friend Function

function outside class.

لكن له access على private members.

```cpp
friend void PrintInfo(const MyList& x);
```

مفيد لما أحتاج utility function برا class لكن محتاج private access.

---

## 10) My Notes / Common Mistakes

- shallow copy = copying address only.
- deep copy = copying values into new memory.
- Copy Constructor → create new object.
- Assignment Operator → assign existing object.
- pass by value invokes Copy Constructor.
- const reference is safer + faster.
- any `new` must have matching `delete`.
- always protect against self assignment.
