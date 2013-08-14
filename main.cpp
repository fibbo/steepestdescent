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
#include "algorithms.hpp"
#include <math.h>
#include <fstream>
#include <cstdio>

using namespace boost::numeric::ublas;


int main(int argc, char * argv[])
{

  //    // insert code here...

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


     // std::cout << "Enter x*: " << std::endl;
     // std::cin >> x(0) >> x(1);
     
     // nonlin_congrad(deriv_rosenbrock, x);
     // std::cout << x << std::endl;
     
     std::cout << "Enter x*: " << std::endl;
     std::cin >> x(0) >> x(1);
     
     step_nonlin(deriv_rosenbrock, x);
     std::cout << x << std::endl;
     
     return 0;
}
