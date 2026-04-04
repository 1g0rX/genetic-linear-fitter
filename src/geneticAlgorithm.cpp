#include "../include/geneticAlgorithm.hpp"
#include <random>
#include <sstream>

GeneticAlgorithm::GeneticAlgorithm(int m, int g, std::vector<double>& x, std::vector<double>& y, double mut_delta, int seed) : generator(seed) {
    this->population_size = m;
    this->generations = g;
    this->x_data = x;
    this->y_data =y;
    this->delta = mut_delta;
}

void GeneticAlgorithm::initializePopulation(double min_val, double max_val) {
    std::uniform_real_distribution<double> dist(min_val, max_val);

    for (int i = 0; i < population_size; i++) {
        double sorted_a = dist(generator);
        double sorted_b = dist(generator);
        population.push_back(Individual(sorted_a, sorted_b));
    }
}

void GeneticAlgorithm::evaluatePopulation() {
    for (int i = 0; i < population_size; i++) {
        population[i].calculateFitness(x_data, y_data);

    }
}

void GeneticAlgorithm::selectBest(int &parent1_idx, int &parent2_idx) {
    parent1_idx = 0;
    parent2_idx = 0;
    double best_fit = -1.0;
    double second_best_fit = -1.0;

    for (int i = 0; i < population_size; i++) {
        double current_fit = population[i].getFitness();
        if (current_fit > best_fit) {
            // the 2nd turn the first
            second_best_fit = best_fit;
            parent2_idx = parent1_idx;

            // now we define the best
            best_fit = current_fit;
            parent1_idx = i;
        } else if (current_fit > second_best_fit) {
            // if isn't the best, but the second
            second_best_fit = current_fit;
            parent2_idx = i;
        }
    }
}

Individual GeneticAlgorithm::crossover(Individual &p1, Individual &p2) {
    return Individual(p1.getA(), p2.getB());

    /* here, the child will get the a from parent 1 and b from parent 2*/
}

void GeneticAlgorithm::mutate(Individual &individual) {
    std::uniform_int_distribution<int> dist(0, 1);

    std::uniform_real_distribution<double> dist_delta(-delta,delta);

    // if sort 0, change A, if sort 1, change B;
    bool change_A = (dist(generator) == 0);

    double mutate_value = dist_delta(generator);
    individual.mutate(mutate_value, change_A);


}

void GeneticAlgorithm::replaceWorst(Individual &child) {
    int worst_idx = findWorseIndividual();
    population[worst_idx] = child;
}

int GeneticAlgorithm::findWorseIndividual() {
    int worst_idx = 0;
    for (int i = 1; i < population_size; i++) {
        if (population[i].getFitness() < population[worst_idx].getFitness()) {
            worst_idx = i;
        }
    }
    return worst_idx;
}

int GeneticAlgorithm::findBestIndividual() {
    int best_idx = 0;
    for (int i = 1; i < population_size; i++) {
        if (population[i].getFitness() > population[best_idx].getFitness()) {
            best_idx = i;
        }
    }
    return best_idx;
}

void GeneticAlgorithm::run(FileManager &fm) {
    for (int g = 0; g < generations; g++) {
        evaluatePopulation(); // evalute

        int parent1_idx, parent2_idx;
        selectBest(parent1_idx, parent2_idx); // select the relatives

        Individual child = crossover(population[parent1_idx], population[parent2_idx]); // cruze

        mutate(child); // mutation

        child.calculateFitness(x_data, y_data); // evalute the new child

        replaceWorst(child); // remove the worst and put the new one child

        // write the file
        int best_idx = findBestIndividual();
        std::stringstream ss;
        ss << population[best_idx].getFitness() << " " << population[best_idx].getError() << " "
            << population[best_idx].getA() << " "<< population[best_idx].getB();
        
        fm.writeLine(ss.str());
    }
}