#ifndef _ALGORITHMS_
#define _ALGORITHMS_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

void fillmatrix(matrix<double>&, vector<double>);
void step(vector<double>& x, vector<double> b, matrix<double> A) {
  double epsilon = 0.000001;
  unsigned int i = 0;
  unsigned int i_max = 100;
  vector<double> r = b - prod(A,x);
  double delta = inner_prod(r,r);
  double delta_0 = delta;  
  while (i < i_max && delta > pow(epsilon,2)*delta_0) {
    vector<double> q = prod(A,r);
    double alpha = delta/inner_prod(r,q);
    x = x + alpha*r;
    if (i%50 == 0)
      r = b - prod(A,x);
    else
      r = r - alpha*q; //saves one vector-matrix multiplication but every 50th step we compute the correct residual (see line above)

    delta = inner_prod(r,r);
    i += 1;

  }
  std::cout << "Number if iterations i: " << i << std::endl;
}

void step_nonlin(vector<double> (*deriv)(vector<double>), vector<double>& x) {

  unsigned int i = 0;
  unsigned int i_max = 100000;
  double epsilon = 0.0000001;
  unsigned int k = 0;
  vector<double> r = -(*deriv)(x); //residual
  vector<double> d = r; // direction of the search
  double delta = inner_prod(r,r);
  double delta_0 = delta;
  matrix<double> H(2,2); //Hessian matrix
  while (i<i_max && delta > pow(epsilon,2)*delta_0) {
    fillmatrix(H,x);
    vector<double> q = prod(H,r);
    double alpha = delta/inner_prod(r,q); // find an alpha such that the function along the direction of search gets minimized
    x = x + alpha*r;    
    r = -(*deriv)(x);
    delta= inner_prod(r,r); 
    i += 1;

  }
  std::cout << "Number of iterations i: "  << i << std::endl;

}

/* Conjugate gradient method - real residual calculated every 50th step */
void congrad(boost::numeric::ublas::vector<double>& x, boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::vector<double> b) {
  using namespace boost::numeric::ublas;
  double epsilon = 0.00001;
  unsigned int i_max = 10000;
  unsigned int i = 0;
  vector<double> r = b - prod(A,x);
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

/* Following 4 functions define the entries of the Hessian matrix of the Rosenbrock function. The function fillmatrix fills a matrix with the calculated entries of the matrix */

double A00(vector<double> x) {
  return 800*pow(x[0],2) - 400*pow((x[1]-pow(x[0],2)),2) - 2;
}

double A01(vector<double> x) {
  return -400*x[0];
}

double A10(vector<double> x) {
  return -400*x[0];
}

double A11(vector<double> x) {
  return 200;
}


void fillmatrix(matrix<double>& A, vector<double>x) {
  A(0,0) = A00(x);
  A(0,1) = A01(x);
  A(1,0) = A10(x);
  A(1,1) = A11(x);
}

/* Nonlinear conjugate gradient method with Newton-Raphson and Fletcher-Reeves */

void nonlin_congrad(vector<double> (*deriv)(vector<double>), vector<double>& x) {
  unsigned int i = 0;
  unsigned int i_max = 100000;
  double epsilon = 0.0000001;
  unsigned int k = 0;
  vector<double> r = -(*deriv)(x); //residual
  vector<double> d = r; // direction of the search
  double delta_new = inner_prod(r,r);
  double delta_0 = delta_new;
  matrix<double> H(2,2); //Hessian matrix
  while (i<i_max && delta_new > pow(epsilon,2)*delta_0) {
    unsigned int j = 0;
    unsigned int j_max = 1000;
    double delta_d = inner_prod(d,d);
    double alpha; // find an alpha such that the function along the direction of search gets minimized

    do {
      fillmatrix(H,x);
      alpha = -inner_prod((*deriv)(x),d) / inner_prod( d, prod( H , d) );
      x = x + alpha*d;
      j += 1;
    } while (j < j_max && pow(alpha,2) * delta_d > pow(epsilon,2));
    
    r = -(*deriv)(x);
    double delta_old = delta_new;
    delta_new = inner_prod(r,r);
    double beta = delta_new/delta_old;
    d = r + beta*d;
    k += 1;
    if (k = 5 || inner_prod(r,d) <= 0) {
      d = r;
      k = 0;
    }

    i += 1;

  }
  std::cout << "Number of iterations i: "  << i << std::endl;
}

/* f' of the Rosenbrock function */
vector<double> deriv_rosenbrock(vector<double> x) {
  vector<double> result(2);
  result(0) = 2 * (200 * pow(x[0],3) - 200 * x[0] * x[1] + x[0] - 1);
  result(1) = 200*(x[1] - pow(x[0],2));
  return result;
}


/* Test function, not finished */
vector<double> deriv_func(vector<double> x) {
  vector<double> result(2);
  result(0) = x[0]*cos( 2*x[0] - exp(x[1]) + 1) * cos(pow(x[0],2)/2 - pow(x[1],2)/4 + 3) - 2*sin(2*x[0] - exp(x[1]) + 1)*sin(pow(x[0],2)/2 - pow(x[1],2)/4 + 3);
  result(1) = exp(x[1]) * sin( 2*x[0] - exp(x[1]) +1  ) * sin( pow(x[0],2)/2 - pow(x[1],2)/4 + 3 ) - 1/2*x[1]*cos( 2*x[0] - exp(x[1]) + 1 ) * cos( pow(x[0],2)/2 - pow(x[1],2)/4 + 3  ) ;
}
#endif
