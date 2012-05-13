m = 10000; % Numero de amostras

a = 0.2;
b = 0.1;
c = 10;
s = 17;

V = 0.1; % Vari�ncia do ruido

for i=1:17
	x(i) = 0;
end

k = 1;

f = fopen("t7.dat","w+");

ptr = 0.7; % porcentagem do sinal gerado que ser� utilizado pra treinamento
pv = 0.2; % porcentagem do sinal gerado que ser� utilizado pra valida��o
pt = 0.1; % porcentagem do sinal gerado que ser� utilizado pra teste

mtr = ptr * m;
mv = mtr + pv * m;
mt = mv + pt * m;

ftr = fopen("t7.dat.tr","w+"); % conjunto de treino
ftrf = fopen("t7.dat.tr.f","w+"); % conjunto de treino filtrado
fv = fopen("t7.dat.v","w+"); % conjunto de validacao
ft = fopen ("t7.dat.t","w+"); % conjunto de teste
 
fr = fopen("r.dat", "w+");

ant =[0, 0, 0];
Ntr = 0.0;
Ntrf = 0.0;

Tc = 0.1; % Taxa de corte para amostra entrar no conjunto de treinamento

for i=18:m
	N = V * randn; % ruido gaussiano
	
	x(i) = x(i-1) + (a * x(i-s) / (1 + x(i-s) ^ c)) - b * x(i-1) + 0.1 * N;
	
	if (mod(i,300) == 0)
		printf("x(%d) = %e\n", i, x(i));
		fprintf(fr,"%d %e\n", i, x(i));
		y(k) = x(i);
		k++;
	end
	
	dant(1) = x(i - 1) - ant(1);
	dant(2) = x(i - s) - ant(2);
	dant(3) = x(i) - ant(3);
	
	dist = sqrt(dant(1) * dant(1) + dant(2) * dant(2) + dant(3) * dant(3));
	
	if (i <= mtr)
		if (dist > Tc)
			fprintf(ftrf, "%e %e %e\n", x(i-1), x(i-s), x(i));
			
			Ntrf += 1.0;
			
			ant(1) = x(i - 1);
			ant(2) = x(i - s);
			ant(3) = x(i);
			
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

printf("Filtragem dos dados de treinamento = %.2f %%\n", 100 * (Ntr - Ntrf) / Ntr);