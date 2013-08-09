#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <fstream>

int main(int argc, char* argv[]) {
  using namespace boost::numeric::ublas;
  std::ifstream infile(argv[1]);

  unsigned int N = 0;
  std::cout << "Enter the dimensionality of the matrix" << std::endl;
  std::cin >> N;
  matrix<double> A(N,N);

    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++) {
	infile >> A(i,j);
      }
    }
    infile.close();
    std::cout << A << std::endl;


}
