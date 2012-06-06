echo "Compilando utils.cpp..."

#g++ -ggdb -c utils.cpp

g++ -O2 -c utils.cpp

echo "Compilando rbf.cpp..."

#g++ -ggdb -c rbf.cpp
g++ -O2 -c rbf.cpp

echo "Compilando rbfde.cpp..."

#g++ -ggdb -c rbfde.cpp
g++ -O2 -c rbfde.cpp

echo "Compilando mainRbf.cpp..."

#g++ -ggdb -c mainRbf.cpp
g++ -O2 -c mainRbf.cpp

echo "Montando rbf..."

g++ -ggdb -o rbf mainRbf.o rbf.o utils.o rbfde.o
#g++ -o rbf mainRbf.o rbf.o utils.o rbfde.o

