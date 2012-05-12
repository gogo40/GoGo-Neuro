
#xor
cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/xor.dat 1 0

mv treino.log treino.xor.batch
mv xor/xor.rna xor.rna.batch

cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/xor.dat 0 0
mv treino.log treino.xor.online
mv xor/xor.rna xor.rna.online

#and
cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/and.dat 1 0
mv treino.log treino.and.batch
mv xor/xor.rna and.rna.batch

cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/and.dat 0 0
mv treino.log treino.and.online
mv xor/xor.rna and.rna.online

#or

cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/or.dat 0 0
mv treino.log treino.or.online
mv xor/xor.rna or.rna.online

cp xor.rnao xor/xor.rna
./rnat xor/xor.rna xor/or.dat 1 0
mv treino.log treino.or.batch
mv xor/xor.rna or.rna.batch



echo "xorResult online"
./rna xor.rna.online xor/xor.dat

echo "xorResult batch"
./rna xor.rna.batch xor/xor.dat

echo "andResult online"
./rna and.rna.online xor/and.dat

echo "andResult batch"
./rna and.rna.batch xor/and.dat

echo "orResult online"
./rna or.rna.online xor/or.dat

echo "orResult batch"
./rna or.rna.batch xor/or.dat

