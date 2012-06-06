echo "Calculo do erro de treino"

../rbf 0 t9.dat.tr.1 1 1 $1 $2 t9.rbf.1.rna
mv f_0.rna.out f_0.rna.1.out
mv f_0.rna.sol f_0.rna.1.sol

../rbf 0 t9.dat.tr.2 2 1 $1 $2 t9.rbf.2.rna
mv f_0.rna.out f_0.rna.2.out
mv f_0.rna.sol f_0.rna.2.sol

../rbf 0 t9.dat.tr.3 3 1 $1 $2 t9.rbf.3.rna
mv f_0.rna.out f_0.rna.3.out
mv f_0.rna.sol f_0.rna.3.sol

../rbf 0 t9.dat.tr.4 4 1 $1 $2 t9.rbf.4.rna
mv f_0.rna.out f_0.rna.4.out
mv f_0.rna.sol f_0.rna.4.sol


../rbf 0 t9.dat.3.23.tr 2 1 $1 $2 t9.rbf.3.23.rna
mv f_0.rna.out f_0.rna.3.23.out
mv f_0.rna.sol f_0.rna.3.23.sol


echo "Calculo do erro de teste"


../rbf 0 t9.dat.t.1 1 1 $1 $2 t9.rbf.1.rna
mv f_0.rna.out f_0.rna.1.t.out
mv f_0.rna.sol f_0.rna.1.t.sol

../rbf 0 t9.dat.t.2 2 1 $1 $2 t9.rbf.2.rna
mv f_0.rna.out f_0.rna.2.t.out
mv f_0.rna.sol f_0.rna.2.t.sol

../rbf 0 t9.dat.t.3 3 1 $1 $2 t9.rbf.3.rna
mv f_0.rna.out f_0.rna.3.t.out
mv f_0.rna.sol f_0.rna.3.t.sol

../rbf 0 t9.dat.t.4 4 1 $1 $2 t9.rbf.4.rna
mv f_0.rna.out f_0.rna.4.t.out
mv f_0.rna.sol f_0.rna.4.t.sol

../rbf 0 t9.dat.3.23.v 2 1 $1 $2 t9.rbf.3.23.rna
mv f_0.rna.out f_0.rna.3.23.v.out
mv f_0.rna.sol f_0.rna.3.23.v.sol

