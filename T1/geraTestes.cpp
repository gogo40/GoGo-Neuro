#include <stdio.h>


double f(double x, double y)
{
	return x*x+y*y+x*y+4;
}

int main()
{
	int N, NI, k;
	double xo, yo, dx, x;
	double x1, y1, dy, y;
	
	fprintf(stderr,"NxN casos: N= ");
	scanf("%d",&N);
	
	fprintf(stderr,"Retangulo em que f está definido:(xo,yo)X(x1,y1)  (com x1>=xo e y1>=yo): ");
	scanf("%lf%lf%lf%lf",&xo,&yo,&x1,&y1);
	
	dx=(x1-xo)/N;
	dy=(y1-yo)/N;
	
	k=0;
	for(x=xo;x<x1;x+=dx)
		for(y=yo;y<y1;y+=dy){
			fprintf(stderr,"%lf %lf %lf\n",x,y,f(x,y));
			k++;
		}
	fprintf(stderr,"k=%d\n",k);
	
	printf("%d\n",k);
	
	k=0;
	for(x=xo;x<x1;x+=dx)
		for(y=yo;y<y1;y+=dy){
			printf("%lf %lf %lf\n",x,y,f(x,y));
			k++;
		}
		
	fprintf(stderr,"Numero de iterações para treinar: ");
	scanf("%d",&NI);
	printf("%d\n",NI);
	fprintf(stderr,"k=%d\n",k);
	return 0;
}
