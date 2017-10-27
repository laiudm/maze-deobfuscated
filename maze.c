// http://tromp.github.io/pearls.html source
// http://tromp.github.io/maze.html explanation of the algorithm

/*
Gather my thoughts on the maze...

* Every cell is part of the maze
* No cell or group of cells is isolated from the rest of the maze. In other words all cells are connected.
* This means that the top-left entry cell is connected somehow to the bottom-right exit cell (and every other cell!).
* There is an additional constraint that there can't be loops - there must be just one route between 2 cells.

The algorithm starts with each cell on the first row just being connected to itself.
Then cell by cell it decides how to connect:

If it decides to connect 2 adjacent cells, those are chained together. Since this proceeds left to right, 
adjacent cells are directly connected. e.g. if the cells are ...ab..., then a points to b. 

So, when processing a cell to decide whether to connect to the adjacent cell:
	if a is _already_ pointing to b, it must not connect it again; instead it must put a wall up. 
	If they _aren't_ connected, it can randomly choose to do so. 
That's exactly what the code does:
	int adj = head[col - 1]; if ( (col != adj) && random() ) ....

The next question is whether to connect down. If it is to do so, then the data structure is unchanged.
However if it decides to _not_ connect down (ie there's a wall), then the cell on the next row is just
connected to itself (with this cell removed from the rest of the list it's attached to). 

But it has to be careful when deciding to _not_ connect - it can't leave it isolated.
I initially thought that "it" would mean that cell, and any other cells it's connected to. But it 
actually only needs to consider when it's alone. On further thought, if it's connected to other cells
then it's not isolated. The other cells it's connected to will always be on the right of this cell
(and therefore not yet processed). 

Hmm, so although I now understand the algorithm, I do find it surprising that this guarantees a
compliant maze.


*/

#include <stdio.h>
#include <stdlib.h>

char opStr[3];
int head[40];		// the left and right doubly linked lists. 
int	tail[40];

int random(void) {	// done repeatedly so pull out as a function
	// returns 0 around 6200 times out of 10000 (and 1 the remainder of the time)
	// equivalent is return (rand() % 10) < 6;	// but this will give different random sequences
	return (6<<27)<rand();
}

int debugCount;

void dump(void) {
	
	printf("\n");
	for (int i=40; --i;) {
		printf("%2i ", i);
	}
	printf("\n");
	
	for (int i=40; --i;) {
		printf("%2i ", head[i]);
	}
	printf("\n");
	
	for (int i=40; --i;) {
		printf("%2i ", tail[i]);
	}
	printf("\n");

}	
	

int main(int argc, char **argv){
	// temp code - calculate probabilities.
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
		head[i] = tail[i] = i;
	}
	head[0] = 1;	// dummy cell. ensures last cell doesn't try to connect to the right
	
	// unroll the Z loops; start in the main loop, then expand the loop for the last line
	// There's a bunch of tests for the last line; extract line line processing into a separate loop
	// Z alternates between 1, 0. When 0, no other part of the loop is affected. So move inside
	// Likewise, noLines only dec's when A = 0, so put inside too. Need extra printf() at the end tho.
	while( --noLines) {
		printf("\n|");
		for (int col = 39; col > 0; col--) {
			
			int adj = head[col-1];
			if ( (col != adj) && random() ) {
				// the cell isn't already pointing to the adjacent cell, so can randomly leave a wall out.
				// join the 2x linked-lists. 4 links need changing - on 4 separate nodes.
				// Call the 2x linked-lists A and B.
				// Since the linked-list is circular we can choose where to break & rejoin them. The following
				// puts the cell at [col-1] at the very end of the linked-list (wrt to [col]).
				tail[adj] = tail[col];		// B: join the tail-ptr of head the second queue to the end of the first queue
				head[tail[col]] = adj;		// A: join the tail-ptr of the tail of the 1st queue to the beginning of the 2nd queue
				tail[col] = col-1;			// A: put [col-1] at the end of the list
				head[col-1] = col;			// B: update the entry at [col-1] so it's head points to the front.
				
				opStr[1]='.';
			} else {
				opStr[1]='|';
			}
			
			int down = head[col];
			if ( (col != down) && random() ) {
				// the cell isn't pointing to itself (and therefore isolated); can randomly put a horizonal wall in.
				//if (++debugCount < 5) {
				//	printf("col = %i, down = %i\n", col, down);
				//	dump();
				//}
				// separate the head from the remainder of the linked-list. The remainder starts at down.
				tail[down] = tail[col];	// down becomes the new head; it's tail now points to where the old head pointed.
				head[tail[col]] = down;	// the tail entry's head now points to the new head.
				tail[col] = col;			// make the head point to itself.
				head[col] = col;
				
				//if (debugCount < 5) {
				//	printf("\nAfter:\n");
				//	dump();
				//}
				opStr[0] = '_';
			} else {
				opStr[0] = ' ';
			}
			printf("%s", opStr);
		}
	}
	
	printf("\n|");
	opStr[0]='_';	// lifted this out of the loop
	for (int col = 39; col > 0; col--) {		// last line processing
			
		int adj = head[col-1];
		if ( (col != adj) && (  (col == tail[col]) | random() )  ) {
			// differs from every other line's processing by addition of (col == tail[col]) 
			// this says the cell points to itself. So this check is to ensure the cell
			// is connected to the right by leaving the wall out.
			tail[adj] = tail[col];
			head[tail[col]] = adj;
			tail[col] = col-1;
			head[col-1] = col;
			opStr[1] = '.';
		} else {
			opStr[1] = '|';
		}
		
		int down = head[col];
		// could remove this "if" as it always succeeds. However it screws up the rand seq
		// & therefore gives different (valid) results. Therefore leave for the moment...
		// There must always be a wall inserted, hence this if always succeeding.
		if ( (  (col != down) && (  (col == tail[col]) | random() )  ) || 1) {
			tail[down] = tail[col];
			head[tail[col]] = down;
			tail[col] = col;
			head[col] = col;
			
		} // else never executes 
		
		printf("%s", opStr);		
	}
	
	printf("\n");
	
	return(0);
}