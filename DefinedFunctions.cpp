//
//  DefinedFunctions.cpp
//  SteepestDescent
//
//  Created by ladmin on 06.06.13.
//  Copyright (c) 2013 Philipp Gloor. All rights reserved.
//

#include "DefinedFunctions.h"
#include <math.h>
class DefinedFunctions {
public:
static double polynom(double x) {
    return 4*x*x*x-9*x*x;
}

static double sine(double x) {
    return sin(x);
}
};