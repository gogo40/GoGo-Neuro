g++ -O2 -o geras geras.cpp
g++ -O2 -o normal normal.cpp

rm *.dat

for (( i = 1 ; i < $1 ; i++ )) 
do
	echo "Gerando caso " $i "...";
	./geras $1 > r.dat
	./normal < r.dat > r.n.dat
	#mv r.n.dat r.$i.dat
done;

