//
//  main.cpp
//  SteepestDescent
//
//  Created by ladmin on 06.06.13.
//  Copyright (c) 2013 Philipp Gloor. All rights reserved.
//

#include <iostream>
#include "DefinedFunctions.cpp"
#include "SteepestDescent.cpp"
#include "PNVector.hpp"


int main()
{

    // insert code here...
    double x_old = 0;
    double x_new = 6;
    double precision = 0.0001;
    double eps = 0.01;
    while ( fabs(x_new-x_old) > precision) {
        x_old = x_new;
//        x_new = x_old - eps * polynom(x_old);
        x_new = SteepestDescent::step(DefinedFunctions::polynom,x_old, eps);
        std::cout << x_old << "\t" << x_new << "\t" << fabs(x_old - x_new) << std::endl;
    }
    std::cout << "the minimum is at: " <<  x_new << std::endl;
    return 0;
}

