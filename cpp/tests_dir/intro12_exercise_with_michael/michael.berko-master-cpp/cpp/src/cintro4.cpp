#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
	int age;
    char name[10];
} Person_t;

typedef struct List {
	int count;
    void** items;
} List_t;

void list_init(List_t* list) {
    list->items = (void**)malloc(sizeof(void*) * 10);  // fixed size for demo
    list->count = 0;
}

void list_add(List_t* list, void* item) {
    list->items[list->count++] = item;
}

void* ll_find(List_t* list, int key) {
    // For simplicity: key == index
    if (key >= 0 && key < list->count) {
        return list->items[key];
    }
    return NULL;
}




int main() {
    List_t list;
    list_init(&list);
    

    Person_t* person = (Person_t*)malloc(sizeof(Person_t));
    strcpy(person->name, "Alice");
    person->age = 30;

    list_add(&list, person);

    printf("Before foo: person->age = %d\n", person->age);
    printf("List count: %d\n", list.count);  // May be corrupted
    // Call with wrong assignment in foo()
    foo(&list, 0, 99);

    printf("After foo: person->age = %d\n", person->age);
    printf("List count: %d\n", list.count);  // May be corrupted

    free(person);
    free(list.items);

    return 0;
}

void foo(List_t* ll, int key, int age) {
    void* vv = ll_find(ll, key);

    // Mistake: this should be Person_t* p = (Person_t*)vv;
    // now doing static_cast
    Person_t *p = reinterpret_cast<Person_t*>(ll);

    //This writes into the List_t structure, not the person!
    p->age = age;
}
