all:
	g++ main.cpp DefinedFunctions.cpp SteepestDescent.cpp -o SD

c:
	g++ -I /opt/local/include/ conjugate.cpp -o cgm