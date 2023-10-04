#include <stdlib.h>
#include <time.h>

int InitRandomNumberGenerator(void) {
    srand(time(NULL));
}

int GenerateRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

float GenerateRandomFloat(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}