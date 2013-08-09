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


using namespace boost::numeric::ublas;
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

    vector<double> x(2), y(2), w(2);
    matrix<double> A(2,2);
    for (unsigned int i = 0; i<A.size1(); ++i) {
      for (unsigned int j = 0; j<A.size2(); ++j) {
	A(i,j) = 3*i+j;
      }
    }
    std::cout << A << std::endl;
    double z;
    x(0) = 1;
    x(1) = 2;
    y(0) = 1;
    y(1) = 2;
    z = inner_prod(x,y);
    w = prod(A,x);
    std::cout << z << std::endl;
    std::cout << w << std::endl;
    return 0;
}

double step(double (*func)(double), double x, double h) {
        return x-h*(*func)(x);
}

void congrad(boost::numeric::ublas::vector<double> x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b) {
  using namespace boost::numeric::ublas;
  unsigned int i_max = 10000;
  unsigned int i = 0;
  vector<double> r ((int)(x.size()));
  r = b - prod(A,x);

}
