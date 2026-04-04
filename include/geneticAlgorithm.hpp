#ifndef GENETICALGORITHM_HPP
#define GENETICALGORITHM_HPP

#include <random>
#include <vector>

#include "evaluation.hpp"

class GeneticAlgorithm {
    private:
        std::vector<Individual> population;
        std::vector<double> x_data;
        std::vector<double> y_data;

        int population_size;
        int generations;
        double delta;

        std::mt19937 generator;

        int findWorseIndividual();
        int findBestIndividual();

    public:
        GeneticAlgorithm(int m, int g, std::vector<double>& x, std::vector<double>& y, double mut_delta, int seed);

        void initializePopulation(double min_val, double max_val);
        void evaluatePopulation();
        void selectBest(int &parent1_idx, int &parent2_idx);
        Individual crossover(Individual &p1, Individual &p2);
        void mutate(Individual &individual);
        void replaceWorst(Individual &child);

};

#endif