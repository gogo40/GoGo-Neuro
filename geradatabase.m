m = 3000; % Numero de amostras

a = 0.2;
b = 0.1;
c = 10;
s = 17;

V = 0.1; % Variância do ruido

for i=1:30
	x(i) = 0;
end

k = 1;

f = fopen("t7.dat","w+");

ptr = 0.7; % porcentagem do sinal gerado que será utilizado pra treinamento
pv = 0.2; % porcentagem do sinal gerado que será utilizado pra validação
pt = 0.1; % porcentagem do sinal gerado que será utilizado pra teste

mtr = ptr * m;
mv = mtr + pv * m;
mt = mv + pt * m;

ftr = fopen("t7.dat.tr","w+"); % conjunto de treino
ftrf = fopen("t7.dat.tr.f","w+"); % conjunto de treino filtrado
fv = fopen("t7.dat.v","w+"); % conjunto de validacao
ft = fopen ("t7.dat.t","w+"); % conjunto de teste

ftr1(1) = fopen("t9.dat.tr.1", "w+"); % conjunto de treino X[k-1] X[k]
ftr1f(1) = fopen("t9.dat.tr.1.f", "w+"); % conjunto de treino X[k-1] X[k]

ftr1(2) = fopen("t9.dat.tr.2", "w+"); % conjunto de treino X[k-1] X[k-2] X[k]
ftr1f(2) = fopen("t9.dat.tr.2.f", "w+"); % conjunto de treino X[k-1] X[k-2] X[k]

ftr1(3) = fopen("t9.dat.tr.3", "w+"); % conjunto de treino X[k-1] ... X[k-3] X[k]
ftr1f(3) = fopen("t9.dat.tr.3.f", "w+"); % conjunto de treino X[k-1] ... X[k-3] X[k]

ftr1(4) = fopen("t9.dat.tr.4", "w+"); % conjunto de treino X[k-1] ... X[k-4] X[k]
ftr1f(4) = fopen("t9.dat.tr.4.f", "w+"); % conjunto de treino X[k-1] ... X[k-4] X[k]
 
fr = fopen("r.dat", "w+");

ant =[0, 0, 0];

ant1 =[ [0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0]
		];

Ntr = 0.0;
Ntrf = 0.0;

Tc = 0.1; % Taxa de corte para amostra entrar no conjunto de treinamento

fprintf(fr, "%d\n", m - 30);

for i=1:4
	fprintf(ftr1(i), "%d\n", mtr-2);
	fprintf(ftr1f(i), "%d\n", mtr-2);
end

for i=30:m
	N = V * randn; % ruido gaussiano
	
	x(i) = x(i-1) + (a * x(i-s) / (1 + x(i-s) ^ c)) - b * x(i-1) + 0.1 * N;
	
	if (mod(i,1) == 0)
		printf("x(%d) = %e\n", i, x(i));
		fprintf(fr,"%e\n", x(i));
		y(k) = x(i);
		k++;
	end
	
	dant(1) = x(i - 1) - ant(1);
	dant(2) = x(i - s) - ant(2);
	dant(3) = x(i) - ant(3);
	
	for k=1:4
		for p=1:k
			dant1(k,p) = x(i-p) - ant1(k,p);
		end
		
		dant1(k, k+1) = x(i) - ant1(k, k+1);
	end
	
	dist = sqrt(dant(1) * dant(1) + dant(2) * dant(2) + dant(3) * dant(3));
	
	if (i <= mtr)
		if (dist > Tc)
			fprintf(ftrf, "%e %e %e\n", x(i-1), x(i-s), x(i));
			
			Ntrf += 1.0;
			
			ant(1) = x(i - 1);
			ant(2) = x(i - s);
			ant(3) = x(i);
			
		end
		
		for k=1:4
			dist = 0;
			for p=1:k
				dist += dant1(k,p) * dant1(k,p);
			end
			
			dist = sqrt(dist);
			
			if (dist > Tc)
				for p=1:k
					fprintf (ftr1f(k), "%e ", x(i-p));
					ant1(k, p) = x(i-p);
				end
				fprintf(ftr1f(k), "%e\n", x(i));
				
				ant1(k, k + 1) = x(i);
			end
			
			for p=1:k
				fprintf(ftr1(k),"%e ", x(i-p));
			end
			
			fprintf(ftr1(k),"%e\n", x(i));
			
		end
		
		fprintf(ftr, "%e %e %e\n", x(i-1), x(i-s), x(i));
		Ntr += 1.0;
	elseif (i <= mv)
		fprintf(fv, "%e %e %e\n", x(i-1), x(i-s), x(i));
	elseif (i <= mt)
		fprintf(ft, "%e %e %e\n", x(i-1), x(i-s), x(i));
	end
	
	fprintf(f, "%e %e %e\n", x(i-1), x(i-s), x(i));
end


fclose(f);
fclose(fr);
fclose(ftr);
fclose(ftrf);
fclose(ft);
fclose(fv);

for i=1:4
	fclose(ftr1(i));
	fclose(ftr1f(i));
end

printf("Filtragem dos dados de treinamento = %.2f %%\n", 100 * (Ntr - Ntrf) / Ntr);
