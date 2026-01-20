#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Egy egyszeru struktura
typedef struct {
    char* name;
    int age;
} Person;

// Ez a fuggveny memoriat foglal
Person* create_person(const char* name, int age) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL;
    }
    
    p->name = (char*)malloc(strlen(name) + 1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    
    strcpy(p->name, name);
    p->age = age;
    
    return p;
}

// Ez a fuggveny is foglal
char* create_greeting(const char* name) {
    char* greeting = (char*)malloc(100);
    if (greeting == NULL) {
        return NULL;
    }
    
    sprintf(greeting, "Hello, %s!", name);
    return greeting;
}

int main() {
    printf("Memory leak demonstracio\n");
    printf("========================\n\n");
    
    // Letrehozunk egy szemelyt
    Person* john = create_person("John Doe", 25);
    if (john == NULL) {
        fprintf(stderr, "Hiba: nem sikerult szemelyt letrehozni\n");
        return 1;
    }
    
    printf("Szemely letrehozva: %s, %d eves\n", john->name, john->age);
    
    // Letrehozunk egy udvozletet
    char* greeting = create_greeting(john->name);
    if (greeting == NULL) {
        // Ha itt hiba van, a john-t meg fel kellene szabaditani!
        free(john->name);
        free(john);
        fprintf(stderr, "Hiba: nem sikerult udvozletet letrehozni\n");
        return 1;
    }
    
    printf("%s\n", greeting);
    
    // JAVITAS: Itt szabaditjuk fel a memoriait!
    // Fontos a sorrend: elobb a struktura belsejet, aztan magat a strukturat
    free(greeting);    // A greeting felszabaditasa
    free(john->name);  // A nev felszabaditasa a strukturán belul
    free(john);        // Maga a Person struktura felszabaditasa
    
    printf("\nProgram vege. (Most mar minden memoria felszabaditva!)\n");
    
    return 0;
}
