/* BINARY SEARCH CODE
 * 
 * This is binary search code. So, it must use the array that sorted.
 * COMPLEXITY = O(logn)
 */

int _bsearch(int val, int l, int r, int *a){
	int m;
	while (l <= r) {
		m = (l + r) >> 1;
		if (a[m] == val)
			return m;
		else if (a[m] > val)
			r = m - 1;
		else
			l = m + 1;
	}
	return -1; //not found!
}