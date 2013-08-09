all:
	g++ -I /opt/local/include main.cpp DefinedFunctions.cpp -o SD

read:
	g++ -I /opt/local/include readfile.cpp -o readfile
