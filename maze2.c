// http://tromp.github.io/pearls.html source
// http://tromp.github.io/maze.html explanation of the algorithm

#include <stdio.h>
#include <stdlib.h>

char opStr[3];
int J[40];		// the left and right doubly linked lists. Left-most cell displayed is at highest index
int	T[40];

int main(int argc, char **argv){
	int noLines;
	scanf("%d",&noLines);
	
	for(int i=40; --i; ) {
		printf("._");
		J[i] =T[i]= i;
	}
	J[0]=1;	// dummy cell. ensures last cell doesn't try to connect to the right
	
	int Z = 1;
	int A = 1;
	while( (A -= Z)  ||  (printf("\n|"), A = 39, noLines--)  ) {
		int E = J[A-Z];
		char *str;
		// 27 assumes 31 bit random no. replace with 11 if 15 bit random no. instead
		if ( (  (A != E) && ( (!noLines & (A == T[A])) | ( (6<<27)<rand()) )  )
				|| (!noLines & !Z) ) {
					
			J[T[E]=T[A]]=E;
			J[T[A]=A-Z]=A;
			str = "_.";
		} else {
			str = " |";
		}
		opStr[Z]=str[Z];
		if (!Z) {
			printf("%s", opStr);
		};
		Z=!Z;
	}
	
	return(0);
}