cp t7_final/t7.rnao t7_final/t7.rnat

rm -f "log.v.dat"

for ((  i = 1 ;  i <= 5;  i++  ))
do

########################################################################
	echo "etapa aprendendo com a natureza 1"

		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 1 1
		mv treino.log t7_final/treino.nat.batch.1.$i

			echo "Validação nat batch 1"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			mv out.dat t7_final/t7.out.v.nat.batch.1.$i
			mv sol.dat t7_final/t7.sol.v.nat.batch.1.$i
		
		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 0 1
		mv treino.log t7_final/treino.nat.online.1.$i
		
			echo "Validação nat online 1"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			mv out.dat t7_final/t7.out.v.nat.online.1.$i
			mv sol.dat t7_final/t7.sol.v.nat.online.1.$i


########################################################################
	
	echo "etapa std batch 1"
	
		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 1 0
		mv treino.log t7_final/treino.std.batch.1.$i
		
			echo "Validação std bacth 1"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			
			mv out.dat t7_final/t7.out.v.std.batch.1.$i
			mv sol.dat t7_final/t7.sol.v.std.batch.1.$i

		

########################################################################

	echo "etapa std online 1"
	
		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 0 0
		mv treino.log t7_final/treino.std.online.1.$i
		
			echo "Validação std online 1"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			
			mv out.dat t7_final/t7.out.v.std.online.1.$i
			mv sol.dat t7_final/t7.sol.v.std.online.1.$i


########################################################################

	echo "etapa aprendendo com a natureza 2"

		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 1 1
		mv treino.log t7_final/treino.nat.batch.2.$i

			echo "Validação nat batch 2"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			
			mv out.dat t7_final/t7.out.v.nat.batch.2.$i
			mv sol.dat t7_final/t7.sol.v.nat.batch.2.$i
		
		./rnat.exe t7_final/t7.rnat t7_final/t7.dat.tr.f 0 1
		mv treino.log t7_final/treino.nat.online.2.$i
		
			echo "Validação nat online 2"
			./rna.exe t7_final/t7.rnat t7_final/t7.dat.v
			
			mv out.dat t7_final/t7.out.v.nat.online.2.$i
			mv sol.dat t7_final/t7.sol.v.nat.online.2.$i
	mv log.v.dat t7_final/log.v.dat.$i
done

cp t7_final/t7.rnat t7_final/t7.rna

echo "test"
./rna.exe t7_final/t7.rna t7_final/t7.dat.t
mv out.dat t7_final/t7.out.t
mv sol.dat t7_final/t7.sol.t

mv log.v.dat t7_final/log.t.dat
