/* Filename: spiral.cpp
 * Description: Given an integer n, print an n by n array
 *              with the numbers 1 through n^2 in a spiral.
 */

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/* Starting from position (idx, idx) in the matrix. We treat
 * the border of the matrix from position (idx, idx) as a 
 * layer and fill it. The top left corner of the layer is 
 * (idx, idx). The top right corder of the layer is
 * (idx, idx + dim - 2*idx - 1) where dim is the size of the 
 * matrix. The bottom right corner of the layer is 
 * (idx + dim - 2*idx - 1, idx + dim - 2*idx - 1). The layer
 * stops at (idx+1, idx).
 */
void FillLayer(int idx, int dim, int start, int** TwoDArray) {

	// row position of matrix
	int i = idx;

	// column position of matrix
	int j = idx;

	// number to print
	int print = start;

	/* fill the layer from the top left corner
	 * (idx, idx) to the top right corner
	 * (idx, idx + dim - 2*idx - 1)
	 */
	for( ; j < idx + (dim - 2*idx); ++j ){
		TwoDArray[i][j] = print;
		++print;
	}

	/* Remember that, at the end of the for loop,
	 * j = idx + dim - 2*idx so we need to decrement
	 * j and increase i in order to go down
	 */
	--j;
	++i;

	/* fill the layer from one position below the top
	 * right corner (idx + 1, idx + dim - 2*idx - 1)
	 * to the bottom right corner
	 * (idx + dim - 2*idx - 1, idx + dim - 2*idx - 1)
	 */
	for( ; i < idx + (dim - 2*idx); ++i ){
		TwoDArray[i][j] = print;
		++print;
	}

	/* Remember that, at the end of the for loop, 
	 * i = idx + dim - 2*idx so we need to decrement
	 * i and j in order to go left
	 */
	--i;
	--j;

	/* Fill the layer from one position to the left of
	 * the bottom right corner 
	 * (idx + dim - 2*idx - 2, idx + dim - 2*idx - 1)
	 * to the bottom left corner (idx, idx + dim - 2*idx - 1)
	 */ 
	for( ; j >= idx; --j ){
		TwoDArray[i][j] = print;
		++print;
	}

	/* Remember that, at the end of the for loop,
	 * j = idx - 1 so we need to increment j and
	 * decrement i in order to go up
	 */
	++j;
	--i;

	/* Fill the layer from one position above the 
	 * bottom left corner (idx, idx + dim - 2*idx - 2)
	 * to one position below the top left corner
	 * (idx + 1, idx)
	 */
	for( ; i > idx; --i ){
		TwoDArray[i][j] = print;
		++print;
	}
}

/* We treat the border of the matrix as a layer, 
 * fill the layer, peel it off, and repeat. There
 * are n/2 layers where n is the dimension of the
 * matrix. The ith layer has 4*(n-1-2*i) entries
 * to fill.
 */ 
void FillArray(int s, int** Matrix) {
	int layers = s/2;
	int count = 1;
        for(int i = 0; i <= s/2; ++i) {
		FillLayer(i, s, count, Matrix);
		count = count + 4*(s-1-2*i);
	}	
}

/* Print the array */
void PrintArray(int s, int** Matrix) {

	// used to set the width of cout
	int b10log = (int) log10(s);

	/* for each row and each column print
	 * Matrix[row][column] with the correct
	 * width format
	 */
	for(int i = 0; i < s; ++i) {
		for(int j = 0; j < s; ++j) {

			/* setw is not sticky so we need to set
			 * the width of each cout each time
			 */
			if ( s > 3 || b10log > 0 ) {
				cout << setfill('0') << setw(b10log + 2);
			}
			cout << Matrix[i][j] << " ";
		}
		// newline after j loop completes	
		cout << endl;
	}	
}

int main() {

	// get a positive integer n from user
	int n;
	cout << "Enter a positive integer: "; 
	scanf("%d", &n);

	// dynamically allocate an n x n array
	int ** MyArray = new int*[n];
	for(int i = 0; i < n; ++i) {
		MyArray[i] = new int[n];
	}

	// Fill array with numbers 1 through n^2
	// in a spiral
	FillArray(n, MyArray);

	// Print the array
	PrintArray(n, MyArray);

	// no memory leaks here
	for(int i = 0; i < n; ++i){
		delete[] MyArray[i];
	}	
	delete[] MyArray;
}
