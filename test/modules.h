#ifndef MODULES_H
#define MODULES_H

#include "types.h"
#include "object.h"
#include "gene.h"
#include "operation/operation.h"
#include "operation/terminal.h"
#include "operation/function.h"
#include "chromosome.h"
#include "color.h"

#include "double.h"

using Object = mep::Object;
using Gene = mep::Gene<Double>;
using Terminal = mep::Terminal<Double>;
using Function = mep::Function<Double>;
using OperationPtr = mep::OperationPtr<Double>;
using Chromosome = mep::Chromosome<Double>;
using Color = mep::Color;

#endif // MODULES_H
