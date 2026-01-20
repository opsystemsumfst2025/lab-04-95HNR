#include <stdio.h>
#include <stdlib.h>

// Ez a program szandekosan tobb hibat tartalmaz
// Futtasd GDB-vel es Valgrind-dal, hogy megtalald oket!

void null_pointer_bug() {
    printf("\n--- 1. Hiba: NULL pointer dereference ---\n");
    
    // JAVITAS: Memoriat foglalunk a pointernek a NULL helyett
    int* ptr = (int*)malloc(sizeof(int));
    
    if (ptr == NULL) {
        fprintf(stderr, "Memoriafoglalasi hiba\n");
        return;
    }
    
    // Most mar biztonsagosan irhatunk ra
    *ptr = 42;
    
    printf("A mutato altal tarolt ertek: %d\n", *ptr);
    
    // A foglalt memoriat fel kell szabaditani
    free(ptr);
}

void array_overflow_bug() {
    printf("\n--- 2. Hiba: Tomb tulinexeles ---\n");
    
    int array[10];
    
    // JAVITAS: A ciklus csak a tomb valodi mereteig (0-9) fut
    for (int i = 0; i < 10; i++) {
        array[i] = i * 10;
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    printf("Most mar nincs tulindexeles.\n");
}

void use_after_free_bug() {
    printf("\n--- 3. Hiba: Use after free ---\n");
    
    int* data = (int*)malloc(5 * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Malloc hiba\n");
        return;
    }
    
    // Feltoltjuk a tombot
    for (int i = 0; i < 5; i++) {
        data[i] = i + 100;
    }
    
    printf("Adatok: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // JAVITAS: A memoriat csak a hasznalat UTAN szabaditjuk fel
    printf("Adatok modositasa...\n");
    for (int i = 0; i < 5; i++) {
        data[i] = i + 200;  
    }

    printf("Uj adatok: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Most mar felszabadithatjuk
    free(data);
    data = NULL; // Jo gyakorlat NULL-ra allitani
    printf("Memoria felszabaditva.\n");
}

int main() {
    printf("Segmentation Fault Demonstracio\n");
    printf("================================\n");
    printf("\nFuttasd GDB-vel: gdb ./f06\n");
    printf("Vagy Valgrind-dal: valgrind ./f06\n");
    
    // Mindharom hiba ki lett javitva, igy most mar sorrendben lefutnak
    
    // 1. hiba javítva
    null_pointer_bug();
    
    // 2. hiba javítva
    array_overflow_bug();
    
    // 3. hiba javítva
    use_after_free_bug();
    
    printf("\nProgram vege hiba nelkul.\n");
    return 0;
}
