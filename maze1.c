#include <stdio.h>
#include <stdlib.h>

char M[3],
J[40],
T[40];

int main(int argc, char **argv){
	int C;
	scanf("%d",&C);
	
	for(int i=40; --i; ) {
		printf("._");
		J[i] =T[i]= i;
	}
	J[0]=1;
	
	int Z;
	int E;
	int A=1;
	for( ;(A-=Z=!Z)  ||  (printf("\n|") , A = 39,C--);  ) {
		// 27 assumes 31 bit random no. replace with 11 if 15 bit random no. instead
		char *s = A-(E=A[J-Z])&&!C & A == T[A] |6<<27<rand()||!C&!Z ? (J[T[E]=T[A]]=E,J[T[A]=A-Z]=A,"_.") : (" |");
		M[Z]=s[Z];
		if (!Z) {
			printf(M);
		}
	}
	
	return(0);
}