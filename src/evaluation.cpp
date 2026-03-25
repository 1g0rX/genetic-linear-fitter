#include "../include/evaluation.hpp"

Individual::Individual(double a_val, double b_val) {
    a = a_val;
    b = b_val;
    error = 0;
    fitness = 0;
}

void Individual::calculateFitness(std::vector<double>& x_points, std::vector<double>& y_points) {

    double sum_error = 0;
    int n = x_points.size();

    for (int i = 0; i < n; i++) {
        double y_pred = a * x_points[i] + b; // estimed y = a * x + b
        double diff = y_points[i] - y_pred; //diff between real value and estimed value
        sum_error += (diff * diff); // MSE (Medium Square Evaluation)
    }

    error = sum_error / n; // medium error;

    fitness = 1.0 / (error + 1e-6);
}

void Individual::mutate(double delta, bool mutate_a) {
    if (mutate_a) {
        a += delta;
    } else {
        b+= delta;
    }
}