#include <stdio.h>
#include "vector.h"

int main() {
    // Test Create function
    Vector* vector = Create(5);
    if (vector == NULL) {
        printf("Create function failed\n");
        return 1;
    }

    // Test PushBack function
    PushBack(vector, 10);
    PushBack(vector, 20);
    PushBack(vector, 30);
    PushBack(vector, 40);
    PushBack(vector, 50);

    // Test Print function
    printf("Vector after PushBack: ");
    Print(vector); // Expected output: size: 5, capacity: 5, 10 20 30 40 50

    // Test Get function
    int value = Get(vector, 2);
    printf("Value at index 2: %d\n", value); // Expected output: Value at index 2: 30

    // Test Set function
    Set(vector, 2, 35);
    printf("Vector after Set: ");
    Print(vector); // Expected output: size: 5, capacity: 5, 10 20 35 40 50

    // Test PopBack function
    int poppedValue = PopBack(vector);
    printf("Popped value: %d\n", poppedValue); // Expected output: Popped value: 50

    // Test Clear function
    Clear(vector);
    printf("Vector after Clear: ");
    Print(vector); // Expected output: size: 0, capacity: 5

    // Test Destroy function
    Destroy(vector);

    return 0;
}