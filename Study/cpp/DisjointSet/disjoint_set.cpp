/* Disjoint Set
 *
 * This code is Disjoint Set of union and find function
 * array p need to initialize the value '-1'
 */

#define MAX_UNION_SIZE 200000

int p[MAX_UNION_SIZE] = { 0 }; // init to '-1'

int find(int n) {
	if (p[n] < 0) return n;
	
	p[n] = find(p[n]);
	return p[n];
}

void uni(int a, int b) {

	int ap = find(a);
	int bp = find(b);

	if (ap < bp) p[bp] = ap;
	else p[ap] = p[bp];  // bp < ap
}
