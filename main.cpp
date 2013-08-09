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
#include <math.h>
#include "DefinedFunctions.cpp"


using namespace boost::numeric::ublas;
double step(double (*func)(double), double x, double h);
void congrad(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b);
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
    x(0) = 2.;
    x(1) = 1.;
    y(0) = 1;
    y(1) = 2;
    z = inner_prod(x,y);
    w = prod(A,x);
    std::cout << z << std::endl;
    std::cout << w << std::endl;

    A(0,0) = 4.;
    A(0,1) = 1.;
    A(1,0) = 1.;
    A(1,1) = 3.;
    y(0) = 1.;
    y(1) = 2.;
    congrad(x, A, y);

    std::cout << x << std::endl;
    return 0;
}

double step(double (*func)(double), double x, double h) {
        return x-h*(*func)(x);
}

void congrad(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b) {
  using namespace boost::numeric::ublas;
  double epsilon = 0.001;
  unsigned int i_max = 10000;
  unsigned int i = 0;
  vector<double> r ((int)(x.size()));
  r = b - prod(A,x);
  vector<double> d = r;
  double delta_new = inner_prod(r,r);
  double delta_0 = delta_new;

  while (i < i_max && delta_new > pow(epsilon,2)) {
    vector<double> q = prod(A,d);
    double alpha = delta_new/inner_prod(d,q);
    x = x + alpha*d;

    if (i%50 == 0)
      r = b - prod(A,x);
    else
      r = r - alpha*q;

    double delta_old = delta_new;
    delta_new = inner_prod(r,r);
    double beta = delta_new/delta_old;
    d = r + beta*d;
    i += 1;

  }
  std::cout << "number of steps: " << i << std::endl;

}
