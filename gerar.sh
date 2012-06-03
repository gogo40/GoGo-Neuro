g++ -O2 -o geras geras.cpp
g++ -O2 -o normal normal.cpp
for (( i = 1 ; i < 5000 ; i++ )) 
do
	echo "Gerando caso " $i "...";
	./geras > r.dat
	./normal < r.dat > r.n.dat
	mv r.n.dat r.$i.dat
done;
