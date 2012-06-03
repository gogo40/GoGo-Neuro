echo "Treina RNA 1"

../rbf 1 t9.dat.tr.1.f 1 1 $1 $2 t9.rbf.1.rna

echo "Treina RNA 2"

../rbf 1 t9.dat.tr.2.f 2 1 $1 $2 t9.rbf.2.rna

echo "Treina RNA 3"

../rbf 1 t9.dat.tr.3.f 3 1 $1 $2 t9.rbf.3.rna

echo "Treina RNA 4"

../rbf 1 t9.dat.tr.4.f 4 1 $1 $2 t9.rbf.4.rna

echo "Treina RNA 5 (3 23)"
../rbf 1 t9.dat.3.23.tr.f 2 1 $1 $2 t9.rbf.3.23.rna

sh teste.sh $1 $2



