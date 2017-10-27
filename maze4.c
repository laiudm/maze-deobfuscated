// http://tromp.github.io/pearls.html source
// http://tromp.github.io/maze.html explanation of the algorithm

#include <stdio.h>
#include <stdlib.h>

char opStr[3];
int J[40];		// the left and right doubly linked lists. Left-most cell displayed is at highest index
int	T[40];

int main(int argc, char **argv){
	int noLines = 10;	// simplify testing
	//scanf("%d",&noLines);
	
	for(int i=40; --i; ) {
		printf("._");
		J[i] =T[i]= i;
	}
	J[0]=1;	// dummy cell. ensures last cell doesn't try to connect to the right
	
	// unroll the Z loops; start in the main loop first
	// There's a bunch of tests for the last line; extract line line processing into a separate loop
	// Z alternates between 1, 0. When 0, no other part of the loop is affected. So move inside
	// Likewise, noLines only dec's when A = 0, so put inside too. Need extra printf() at the end tho.
	while( --noLines) {
		printf("\n|");
		for (int A = 39; A > 0; A--) {
			//for (int Z = 1; Z >= 0; Z--) {
				int Z;
				int E;
				char *str;
				
				// Z = 1
				Z = 1;
				E = J[A-1];
				if (  (A != E) &&  ( (6<<27)<rand()) ) {
					J[T[E]=T[A]]=E;
					J[T[A]=A-1]=A;
					str = "_.";
				} else {
					str = " |";
				}
				opStr[1]=str[1];
				
				// Z = 0
				Z = 0;
				E = J[A-0];
				if (  (A != E) &&  ( (6<<27)<rand()) ) {
					J[T[E]=T[A]]=E;
					J[T[A]=A-0]=A;
					str = "_.";
				} else {
					str = " |";
				}
				opStr[0]=str[0];				
			//}   
			printf("%s", opStr);
		}
	}
	
	printf("\n|");
	for (int A = 39; A > 0; A--) {		// last line processing
		for (int Z = 1; Z >= 0; Z--) {
			int E = J[A-Z];
			char *str;
			// 27 assumes 31 bit random no. replace with 11 if 15 bit random no. instead
			if ( (  (A != E) && ( ( (A == T[A])) | ( (6<<27)<rand()) )  )
					|| (!Z) ) {
						
				J[T[E]=T[A]]=E;
				J[T[A]=A-Z]=A;
				str = "_.";
			} else {
				str = " |";
			}
			opStr[Z]=str[Z];
		}   
		printf("%s", opStr);
	}
	
	printf("\n");
	
	return(0);
}