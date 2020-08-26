/* MERGE SORT
 * 
 * This sorting algorithm need addtional space for MERGING
 * TIME COMPLEXITY : O(NlogN)
 *
 */

int* sort; 

void _msort(int l, int r, int* a) {
	if (l < r) {
		int m = (l + r) >> 1;
		int i = l, j = m + 1, k = l, u;
		_msort(l, m, a);
		_msort(m + 1, r, a);
		while (i <= m && j <= r) {
			if (a[i] <= a[j])
				sort[k++] = a[i++];
			else
				sort[k++] = a[j++];
		}
		if (i > m) {
			for (u = j; u <= r; u++)
				sort[k++] = a[u];
		}
		else {
			for (u = i; u <= m; u++)
				sort[k++] = a[u];
		}
		for (u = l; u <= r; u++)
			a[u] = sort[u];
	}
}