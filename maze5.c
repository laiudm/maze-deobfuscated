// http://tromp.github.io/pearls.html source
// http://tromp.github.io/maze.html explanation of the algorithm

/*
Gather my thoughts on the maze...
Every cell is part of the maze
No cell or group of cells is isolated from the rest of the maze. In other words all cells are connected.
This means that the top-left entry cell is connected somehow to the bottom-right exit cell (and every other!).
There is an additional constraint that there can't be loops - there must be just one route between 2 cells.

The algorithm starts with each cell on the first row just being connected to itself.
Then cell by cell it decides how to connect.
If it decides to connect 2 adjacent cells, those are chained together. Since this proceeds left to right, 
adjacent cells are directly connected. e.g. if the cells are ...ab..., then a points to b. 

So, if when processing a cell, it turns out a is _already_ pointing to b, it must not connect it again; instead
it must put a wall up. If they _aren't_ connected, it can randomly choose to do so. That's exactly what the code does:
	int adj = Left[col - 1]; if ( (col != adj) && random() ) ....






*/

#include <stdio.h>
#include <stdlib.h>

char opStr[3];
int Left[40];		// the left and right doubly linked lists. Left-most cell displayed is at highest index
int	Right[40];

int random(void) {	// done repeatedly so pull out as a function
	// returns 0 around 6200 times out of 10000 (and 1 the remainder of the time)
	return (6<<27)<rand();
}

int main(int argc, char **argv){
	//printf("start\n");
	//int c = 0;
	//for (int i = 0; i<10000; i++) {
	//	int r = random();
	//	c += r;
	//	//printf("rand: %i\n", r );
	//}
	//printf("count = %i\n", c);
	//exit(0);
	
	int noLines = 10;	// simplify testing
	//scanf("%d",&noLines);
	
	for(int i = 40; --i; ) {
		printf("._");
		Left[i] = Right[i] = i;
	}
	Left[0] = 1;	// dummy cell. ensures last cell doesn't try to connect to the right
	
	// unroll the Z loops; start in the main loop, then expand the loop for the last line
	// There's a bunch of tests for the last line; extract line line processing into a separate loop
	// Z alternates between 1, 0. When 0, no other part of the loop is affected. So move inside
	// Likewise, noLines only dec's when A = 0, so put inside too. Need extra printf() at the end tho.
	while( --noLines) {
		printf("\n|");
		for (int col = 39; col > 0; col--) {
			
			int adj = Left[col - 1];
			if ( (col != adj) && random() ) {
				Right[adj] = Right[col];
				Left[Right[col]] = adj;
				Right[col] = col-1;
				Left[col-1] = col;
				opStr[1]='.';
			} else {
				opStr[1]='|';
			}
			
			int down = Left[col];
			if ( (col != down) && random() ) {
				Right[down] = Right[col];
				Left[Right[col]] = down;
				Right[col] = col;
				Left[col] = col;
				opStr[0] = '_';
			} else {
				opStr[0] = ' ';
			}
			printf("%s", opStr);
		}
	}
	
	printf("\n|");
	opStr[0]='_';	//can lift this out of the loop
	for (int col = 39; col > 0; col--) {		// last line processing
			
		int adj = Left[col-1];
		if ( (col != adj) && (  (col == Right[col]) | random() )  ) {
			Right[adj] = Right[col];
			Left[Right[col]] = adj;
			Right[col] = col-1;
			Left[col-1] = col;
			opStr[1] = '.';
		} else {
			opStr[1] = '|';
		}
		
		int down = Left[col];
		// could remove this "if" as it always succeeds. However it screws up the rand seq
		// & therefore gives different (valid) results. Therefore leave for the moment...
		if ( (  (col != down) && (  (col == Right[col]) | random() )  ) || 1) {
			Right[down] = Right[col];
			Left[Right[col]] = down;
			Right[col] = col;
			Left[col] = col;
			
		} // else never executes 
		
		printf("%s", opStr);		
	}
	
	printf("\n");
	
	return(0);
}