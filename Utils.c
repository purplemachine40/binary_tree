#include <stdlib.h>
#include <time.h>

void InitRandomNumberGenerator(void) {
    srand((unsigned int)time(NULL));
}

int GenerateRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

float GenerateRandomFloat(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}