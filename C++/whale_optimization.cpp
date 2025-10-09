// whale_optimization.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>  // for rand(), RAND_MAX
#include <ctime>    // for time()
#include <fstream>

using namespace std;

const int POP_SIZE = 10;       // number of whales
const int DIM = 3;            // dimensions of the search space
const double LOWER = -100.0;   // lower bound
const double UPPER = 100.0;    // upper bound
const int MAX_ITER = 500; // number of iterations
double a = 2.0; // parameter that decreases over iterations in full WOA

struct Whale {
    vector<double> position;
    double fitness;
};

double getFitness(const vector<double> &pos){
    double sum = 0.0;
    for (double x : pos)
        sum += x * x;
    return sum;
}

double randDouble(double low, double high) {
    return low + static_cast<double>(rand()) / RAND_MAX * (high - low);
}

vector<Whale> initializePopulation(){
    vector<Whale> population;
    population.reserve(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++){
        Whale w;
        w.position.resize(DIM);
        for (int d = 0; d < DIM; d++){
            w.position[d] = randDouble(LOWER, UPPER);
        }

        w.fitness = getFitness(w.position);
        population.push_back(w);
    }

    return population;
}

Whale& findBestWhale(vector<Whale> &population){
    Whale* best = &population[0];

    for (auto &w : population){
        if (w.fitness < best->fitness){
            best = &w;
        }
    }
    return *best;
}

vector<double> generateVector(int dim, double min, double max){
    vector<double> v(dim);
    for (int i = 0; i < dim; i++){
        v[i] = randDouble(min, max);
    }
    return v;
}

void encirclePrey(Whale &w, const Whale &bestWhale, double a){
    vector<double> A = generateVector(DIM, -a, a);
    vector<double> C = generateVector(DIM, 0.0, 2.0);

    for (int d = 0; d < DIM; d++){
        double D = fabs(C[d] * bestWhale.position[d] - w.position[d]);
        w.position[d] = bestWhale.position[d] - A[d] * D;
    }

    w.fitness = getFitness(w.position);
}

void spiralMove(Whale &w, const Whale &bestWhale){
    double b = 1.0;
    double l = randDouble(-1.0, 1.0);

    for (int d = 0; d < DIM; d++) {
        double D = fabs(bestWhale.position[d] - w.position[d]);
        w.position[d] = D * exp(b * l) * cos(2 * M_PI * l) + bestWhale.position[d];
    }

    w.fitness = getFitness(w.position);
}

void randomMove(Whale &w, const vector<Whale> &population) {
    int randIndex = rand() % population.size();
    const Whale &X_rand = population[randIndex];

    vector<double> A = generateVector(DIM, -1.0, 1.0);

    for (int d = 0; d < DIM; d++) {
        double D = fabs(X_rand.position[d] - w.position[d]);
        w.position[d] = X_rand.position[d] - A[d] * D;
    }

    w.fitness = getFitness(w.position);
}

void printWhales(const vector<Whale> &population){
    for (int i = 0; i < POP_SIZE; i++) {
        cout << "Whale " << i << " fitness: " << population[i].fitness << " position: ";
        for (double x : population[i].position) {
            cout << x << " ";
        }
        cout << endl;
    }
}

void printBestWhale(const Whale &bestWhale){
    cout << "\nBest whale fitness: " << bestWhale.fitness << " position: ";
    for (double x : bestWhale.position)
        cout << x << " ";
    cout << endl;
    cout << endl;
}

void visualize2D(const vector<Whale> &population) {
    const int width = 50;
    const int height = 20;

    vector<string> grid(height, string(width, '.'));

    for (const auto &w : population) {
        int x = static_cast<int>((w.position[0] - LOWER) / (UPPER - LOWER) * (width-1));
        int y = static_cast<int>((w.position[1] - LOWER) / (UPPER - LOWER) * (height-1));
        y = height - 1 - y; // invert y for console top
        if (x >= 0 && x < width && y >= 0 && y < height)
            grid[y][x] = 'W';
    }

    for (const auto &row : grid)
        cout << row << endl;
}

void savePositionsCSV(const vector<Whale> &population, int iter) {
    ofstream file("whales.csv", ios::app);  // append mode
    for (const auto &w : population) {
        file << iter;
        for (double x : w.position)
            file << "," << x;
        file << "," << w.fitness << endl;
    }
    file.close();
}

int main(){
    srand(time(nullptr)); // initialize random seed

    auto population = initializePopulation();

    for (int iter = 0; iter < MAX_ITER; iter++) {
        a = 2.0 - iter * (2.0 / MAX_ITER);  // linearly decreasing
    
        Whale &bestWhale = findBestWhale(population); // update best
    
        for (int i = 0; i < POP_SIZE; i++) {
            double p = randDouble(0.0, 1.0);
    
            if (p < 0.5) {
                double r = randDouble(0.0, 1.0);
                if (r < 0.5)
                    encirclePrey(population[i], bestWhale, a); // encircle
                else
                    spiralMove(population[i], bestWhale);      // spiral
            } else {
                randomMove(population[i], population);       // explore
            }
        }
    
        cout << "Iteration: " << iter << endl;
        //printWhales(population);
        printBestWhale(bestWhale);
        savePositionsCSV(population, iter);

        //visualize2D(population);
    }

    return 0;
}