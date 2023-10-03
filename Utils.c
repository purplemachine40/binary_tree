#include <stdlib.h>
#include <time.h>

int InitRandomNumberGenerator(void) {
    srand(time(NULL));
}

int GenerateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}