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

     unsigned int N = 2;
     //std::cout << "Enter the dimensionality of the matrix" << std::endl;
     //std::cin >> N;
     matrix<double> A(N,N);
     vector<double> x1(N), x2(N), x3(N), x4(N);
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


     std::cout << "Enter x1*: " << std::endl;
      std::cin >> x1(0) >> x1(1);
     
     nonlin_congrad(deriv_rosenbrock, x1);
     std::cout << x1 << std::endl;
     
     std::cout << "Enter x2*: " << std::endl;
     std::cin >> x2(0) >> x2(1);
     

     nonlin_steep(deriv_rosenbrock, x2);
     std::cout << x2 << std::endl;


     std::cout << "Enter x3*: " << std::endl;
     std::cin >> x3(0) >> x3(1);
     

     steep(x3, b, A);
     std::cout << x3 << std::endl;

     std::cout << "Enter x4*: " << std::endl;
     std::cin >> x4(0) >> x4(1);
     

     congrad(x4, b, A);
     std::cout << x4 << std::endl;

     return 0;
}
