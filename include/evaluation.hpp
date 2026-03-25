#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <vector>

class Individual {
    private:
        double a;
        double b;
        double error;
        double fitness;

    public:
        Individual(double a_val, double b_val);
        // calculate the error and fitness, receiving x and y vectors
        void calculateFitness(std::vector<double>& x_points, std::vector<double>& y_points);
        void mutate(double delta, bool mutate_a);

        // getters
        double getA();
        double getB();
        double getError();
        double getFitness();
};

#endif