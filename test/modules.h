#ifndef MODULES_H
#define MODULES_H

#include "utils/types.h"
#include "operation.h"
#include "core.h"
#include "genetic.h"

#include "double.h"

using Object = mep::Object;
using Gene = mep::Gene<Double>;
using Terminal = mep::Terminal<Double>;
using Function = mep::Function<Double>;
using Operation = mep::Operation<Double>;
using OperationPtr = mep::OperationPtr<Double>;
using Chromosome = mep::Chromosome<Double>;
using Color = mep::Color;
using Random = mep::Random;
using UintRandom = mep::UintRandom;
using BinomialUintRandom = mep::BinomialUintRandom;
using DoubleRandom = mep::DoubleRandom;
template<typename Type>
using PtrSet = mep::PtrSet<Type>;
using OperationSet = mep::OperationSet<Double>;
using Fitness = mep::Fitness<Double>;
using TournamentSelection = mep::TournamentSelection;
using RankRouletteSelection = mep::RankRouletteSelection;
using FitnessRouletteSelection = mep::FitnessRouletteSelection;
using Selection = mep::Selection;
using Mutation = mep::Mutation<Double>;
using ArgumentMutation = mep::ArgumentMutation<Double>;
using AttributeMutation = mep::AttributeMutation<Double>;
using CombinedMutation = mep::CombinedMutation<Double>;
using Crossover = mep::Crossover<Double>;
using OnePointCrossover = mep::OnePointCrossover<Double>;
using TwoPointCrossover = mep::TwoPointCrossover<Double>;
using UniformCrossover = mep::UniformCrossover<Double>;
using Population = mep::Population<Double>;

#endif // MODULES_H
