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
#include <fstream>
#include "DefinedFunctions.cpp"


using namespace boost::numeric::ublas;

double step(double (*func)(double), double x, double h);
void congrad(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b);
void steepdesc(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b);


int main(int argc, char * argv[])
{

  //    // insert code here...
  //    double x_old = 0;
  //    double x_new = 6;
  //    double precision = 0.0001;
  //    double eps = 0.01;
  //    while ( fabs(x_new-x_old) > precision) {
  //        x_old = x_new;

  //        x_new = step(DefinedFunctions::polynom,x_old, eps);
  //        std::cout << x_old << "\t" << x_new << "\t" << fabs(x_old - x_new) << std::endl;
  //    }
  //   std::cout << "the minimum is at: " <<  x_new << std::endl;
  // 
  // backup
    unsigned int N = 0;
    std::cout << "Enter the dimensionality of the matrix" << std::endl;
    std::cin >> N;
    matrix<double> A(N,N);
    vector<double> x(N);
    vector<double> b(N);
    std::ifstream matrixfile(argv[1]);
    std::ifstream bfile(argv[2]);
    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++) {
	matrixfile >> A(i,j);
      }
    }
    matrixfile.close();

    for (int i = 0; i<N; i++) {
      bfile >> b(i);
    }


    double z;
    x(0) = 2.;
    x(1) = 1.;

    congrad(x, A, b);

    std::cout << x << std::endl;
    return 0;
}

double step(double (*func)(double), double x, double h) {
        return x-h*(*func)(x);
}

void steepdesc(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b) {
  using namespace boost::numeric::ublas;
  double epsilon = 0.001;
  unsigned int i_max = 10000;
  unsigned int i = 0;
  vector<double> r ((int)(x.size()));
  r = b - prod(A,x);
  double delta = inner_prod(r,r);
  double delta_0 = delta;
  while (i < i_max && delta > pow(epsilon,2)) {
    vector<double> q = prod(A,r);
    double alpha = delta/inner_prod(r,q);
    x = x + alpha*r;
    if (i%50==0)
      r = b - prod(A,x);
    else
      r = r - alpha*q;

    delta = inner_prod(r,r);
    i += 1;
  }
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
