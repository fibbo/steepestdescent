//
//  main.cpp
//  SteepestDescent
//
//  Created by ladmin on 06.06.13.
//  Copyright (c) 2013 Philipp Gloor. All rights reserved.
//

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "DefinedFunctions.cpp"

#include "PNVector.hpp"

//using namespace boost::numeric::ublas;
double step(double (*func)(double), double x, double h);
void congrad(boost::numeric::ublas::vector<double> x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b);
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
        x_new = step(DefinedFunctions::polynom,x_old, eps);
        std::cout << x_old << "\t" << x_new << "\t" << fabs(x_old - x_new) << std::endl;
    }
    std::cout << "the minimum is at: " <<  x_new << std::endl;
    return 0;
}

double step(double (*func)(double), double x, double h) {
        return x-h*(*func)(x);
}


