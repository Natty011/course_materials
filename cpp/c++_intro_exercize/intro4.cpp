#include <stdio.h>
#include <iostream>

typedef struct List
{
    int dummy;
} List_t;

typedef struct Person
{
    int age;
} Person_t;

void* ll_find(List_t *ll, int key)
{
    static Person_t dummy = {0};  // simulate a result
    return &dummy;
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);

    // cast בטוח
    Person_t *p = static_cast<Person_t*>(vv);
    p->age = age;
    std::cout << "Age set to: " << p->age << std::endl;
}

int main()
{
    List_t list;
    foo(&list, 0, 42);  // מצפה לראות: Age set to: 42
    return 0;
}


/*
typedef struct List List_t;
typedef struct Person Person_t;


typedef struct Person
{
    int age;
}Person_t;


typedef struct List
{
    int dummy;
} List_t;

void* ll_find(List_t *ll, int key)
{
    static Person_t dummy = { key };
    return &dummy;  // לצורך הדגמה בלבד
}


void foo(List_t *ll, int key, int age)
{

    void *vv = ll_find(ll, 30);
    Person_t *p = (Person_t*)ll; // טעות! היה צריך להיות vv
    p->age = age;
}


int main()
{
    List_t ll = {30};

    List_t *p_ll = &ll;
    Person_t pers = {0};


    foo(p_ll, pers, 30)

    return 0;
}

*/

/*
typedef struct List
{
    int dummy;
} List_t;

typedef struct Person
{
    int age;
} Person_t;

void* ll_find(List_t *ll, int key)
{
    static Person_t dummy = { 0 };
    return &dummy;  // לצורך הדגמה בלבד
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    Person_t *p = static_cast<Person_t*>(vv);  // תיקון נכון
    p->age = age;
}

*/