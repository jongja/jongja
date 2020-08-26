/* QUICK SORT
 * TIME COMPLEXITY : O(NlogN)
 */

void _qsort(int l, int r, int* a) {
	if (l < r) {
		int i = l;
		int j = r + 1;
		int p = a[l];
		do {
			do i++; while (i <= r && a[i] < p);
			do j--; while (j >= l && a[j] > p);
			if (i < j) {
				int t = a[i]; a[i] = a[j]; a[j] = t;
			}
		} while (i < j);
		int t = a[j]; a[j] = a[l]; a[l] = t;
		_qsort(l, j - 1, a);
		_qsort(j + 1, r, a);
	}
}