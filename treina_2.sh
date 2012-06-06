
#xor
cp rede_1.rna Nature/rede_1.rna
./rnat Nature/rede_1.rna Nature/xor.dat 1 1

mv treino.log treino.xor.rede_1
mv Nature/rede_1.rna xor.rna.rede_1

cp rede_2.rna Nature/rede_2.rna
./rnat Nature/rede_2.rna Nature/xor.dat 1 1

mv treino.log treino.xor.rede_2
mv Nature/rede_2.rna xor.rna.rede_2


#and
cp rede_2.rna Nature/rede_2.rna
./rnat Nature/rede_2.rna Nature/and.dat 1 1

mv treino.log treino.and.rede_2
mv Nature/rede_2.rna and.rna.rede_2

cp rede_1.rna Nature/rede_1.rna
./rnat Nature/rede_1.rna Nature/and.dat 1 1

mv treino.log treino.and.rede_1
mv Nature/rede_1.rna and.rna.rede_1



#or
cp rede_2.rna Nature/rede_2.rna
./rnat Nature/rede_2.rna Nature/or.dat 1 1

mv treino.log treino.or.rede_2
mv Nature/rede_2.rna or.rna.rede_2

cp rede_1.rna Nature/rede_1.rna
./rnat Nature/rede_1.rna Nature/or.dat 1 1

mv treino.log treino.or.rede_1
mv Nature/rede_1.rna or.rna.rede_1



echo "xor Result Nature rede_2"
./rna xor.rna.rede_2 Nature/xor.dat

echo "or Result Nature rede_2"
./rna or.rna.rede_2 Nature/or.dat

echo "and Result Nature rede_2"
./rna and.rna.rede_2 Nature/and.dat


echo "--------------------"

echo "xor Result Nature rede_1"
./rna xor.rna.rede_1 Nature/xor.dat

echo "or Result Nature rede_1"
./rna or.rna.rede_1 Nature/or.dat

echo "and Result Nature rede_1"
./rna and.rna.rede_1 Nature/and.dat

