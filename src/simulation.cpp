#include "../include/simulation.hpp"
#include "../include/io.hpp"
#include "../include/geneticAlgorithm.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Simulation::Simulation() {}

void Simulation::start() {
    std::cout << "Starting..." << std::endl;

    FileManager fm;

    if (!fm.openForReading("data/input.dat")) {
        std::cerr << "Failed to open data/input.dat" << std::endl;
        return;
    }

    if (!fm.openForWriting("data/output.dat")) {
        std::cerr << "Failed to open data/output.dat" << std::endl;
        return;
    }

    std::string line;
    if (!fm.readLine(line)) {
        std::cerr << "Empty input file" << std::endl;
    }

    std::stringstream ss_config(line);
    int n, population_size, generations;
    ss_config >> n >> population_size >> generations;

    std::vector<double> x_data;
    std::vector<double> y_data;

    for (int i = 0; i < n; i++) {
        if (fm.readLine(line)) {
            std::stringstream ss_points(line);
            double x, y;
            ss_points >> x >> y;
            x_data.push_back(x);
            y_data.push_back(y);

        }
    }

    double delta = 0.1;
    int seed = 42;


    GeneticAlgorithm ga(population_size, generations, x_data, y_data, delta, seed);
    ga.initializePopulation(-1.0, 1.0);
    ga.run(fm);

    fm.closeFiles();
    std::cout << "Concluded!" << std::endl;
}

