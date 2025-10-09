#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POP_SIZE 5
#define MAX_ITER 30
#define DIM 1
#define LOWER -10.0
#define UPPER 10.0

typedef struct {
    double position[DIM];
    double fitness;
} Whale;

double fitness(double *pos) {
    return pos[0] * pos[0];
}

double rand_double(double a, double b) {
    return a + (b - a) * ((double) rand() / RAND_MAX);
}

Whale* findBestWhale(Whale *pop){
    int best = 0;
    for (int i = 1; i < POP_SIZE; i++){
        if (pop[i].fitness < pop[best].fitness)
            best = i;
    }
    return &pop[best];
}

int main() {
    srand(time(NULL));

    Whale population[POP_SIZE];
    Whale *best_whale;

    for (int i = 0; i < POP_SIZE; i++) {
        for (int d = 0; d < DIM; d++) {
            population[i].position[d] = rand_double(LOWER, UPPER);
        }
        population[i].fitness = fitness(population[i].position);
    }

    best_whale = find_best(population);

    for (int iter = 0; iter < MAX_ITER; iter++) {
        double a = 2.0 - iter * (2.0 / MAX_ITER);

        for (int i = 0; i < POP_SIZE; i++) {
            for (int d = 0; d < DIM; d++) {
                double r1 = rand_double(0, 1);
                double r2 = rand_double(0, 1);
                double A = 2.0 * a * r1 - a;
                double C = 2.0 * r2;

            }
        }
    }

}