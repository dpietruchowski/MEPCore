#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#include "image.h"
#include "functions.h"
#include "hammingfitness.h"

#include "core.h"
#include "genetic.h"
#include "operation.h"
#include "morphology.h"

using Operation = mep::Operation<Image>;
using Function = mep::Function<Image>;
using Terminal = mep::Terminal<Image>;
using Gene = mep::Gene<Image>;
using Chromosome = mep::Chromosome<Image>;
using Fitness = mep::Fitness<Image>;
using OperationSet = mep::OperationSet<Image>;
using Mutation = mep::Mutation<Image>;
using ArgumentMutation = mep::ArgumentMutation<Image>;
using AttributeMutation = mep::AttributeMutation<Image>;
using CombinedMutation = mep::CombinedMutation<Image>;
using Crossover = mep::Crossover<Image>;
using OnePointCrossover = mep::OnePointCrossover<Image>;
using TwoPointCrossover = mep::TwoPointCrossover<Image>;
using UniformCrossover = mep::UniformCrossover<Image>;
using Population = mep::Population<Image>;

int main()
{
    mep::Log::MAX_LEVEL = mep::DEBUG;
    Fitness *fitness = new HammingFitness(imread("auto_bin_ref.png",CV_8U));
    mep::Selection* selection = new mep::RankRouletteSelection();
    Terminal terminal(imread("auto_bin.png", CV_8U), "input_img");
    Population population(100, terminal, selection, fitness);
    population.operationSet.registerPtr(
                0.05, new Terminal(imread("auto_bin.png", CV_8U), "input_img"));
    population.operationSet.registerPtr(
                0.1, new Function(bitwiseNot, "not", 1));
    population.operationSet.registerPtr(
                0.05, new Function(bitwiseAnd, "and", 2));
    population.operationSet.registerPtr(
                0.05, new Function(bitwiseXor, "xor", 2));
    population.operationSet.registerPtr(
                0.2, new Function(recall, "recall", 2));
    population.operationSet.registerPtr(
                0.05, new Function(fillHoles, "fill", 1));
    for(int i = 0; i < 10; ++i) {
        population.operationSet.registerPtr(
                0.05, new Morphology(MorphParams::random()));
    }
    population.crossoverSet.registerPtr(0.4, new OnePointCrossover());
    population.crossoverSet.registerPtr(0.4, new TwoPointCrossover());
    population.crossoverSet.registerPtr(0.2, new UniformCrossover());
    population.mutationSet.registerPtr(0.2, new ArgumentMutation());
    population.mutationSet.registerPtr(0.2, new AttributeMutation());
    population.mutationSet.registerPtr(0.6, new CombinedMutation());

    population.init(25);

    std::vector<uint> scores;
    std::vector<uint> bscores;
    fitness = new HammingFitness(imread("auto_bin_ref.png",CV_8U));
    Population tmpPopulation(100, terminal, nullptr, fitness);

    for(int gen = 0; gen < 100; ++gen) {
        scores.push_back(population.avScore());
        bscores.push_back(population.bestScore());
        for(int i = 0; i < 100; ++i) {
            bool added;
            do {
                auto child = population.reproduce();
                added = tmpPopulation.add(std::move(child));
            } while(added);
        }
        std::cout << "///////////// Gen nr " << gen << " /////////" << std::endl;
        auto result = population.best().result();
        result.show("Result");
        population.movePopulation(std::move(tmpPopulation));
    }


    for(const auto score : scores)
        std::cout << score << " ";
    std::cout << endl;
    std::cout << endl;
    for(const auto score : bscores)
        std::cout << score << " ";
    std::cout << endl;
    std::cout << endl;

    Image result = population.best().result();
    imshow("output", result.img);
    waitKey();
    return 0;
}
