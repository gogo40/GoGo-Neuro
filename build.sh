#Script para compilar a tarefa

echo "Compilando misc.cpp..."
g++ -O2 -fno-inline -ggdb -c misc.cpp
echo "Compilando neuro.cpp..."
g++ -O2 -fno-inline -ggdb -c neuro.cpp
echo "Compilando rna.cpp..."
g++ -O2 -fno-inline -ggdb -c rna.cpp

echo "______________________"

echo "Gerando programa de treino:rnat"
g++ -O2 -fno-inline -ggdb -c rnat.cpp
g++ -O2 -fno-inline -ggdb -o rnat rnat.o rna.o neuro.o misc.o -lm

echo "Gerando programa de execução da rede:rna"
g++ -O2 -fno-inline -ggdb -c rna_exec.cpp
g++ -O2 -fno-inline -ggdb -o rna rna_exec.o rna.o neuro.o misc.o -lm

echo "______________________"

