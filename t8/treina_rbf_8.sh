echo "Numero de neuronios:"$1
echo "Beta:"$2

../rbf 1 ../t7_final/t7.dat.tr.f 2 1 $1 $2 t8.rbf.rna

sh testa_rbf_8.sh $1 $2
