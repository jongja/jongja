/* KMP algorithm (Knuth–Morris–Pratt Algorithm)
 *
 * The KMP algorithm is an algorithm that counts how many words B are in the corresponding string A.
 * If one of the existing words is wrong, rather than counting one by one again, keep the correct part instead of going back for the first time.
 *
 * N : length of A
 * A : string
 * M : length of B
 * B : word
 *
 */

#define MAX_STR_LEN 100000

int KMP(int N, char* A, int M, char* B) {
	int cnt = 0;
	int j = 0;
	int pi[MAX_STR_LEN] = { 0 };
	for (int i = 1; i < M; i++) {
		while (j > 0 && B[i] != B[j])
			j = pi[j - 1];
		if (B[i] == B[j])
			pi[i] = ++j;
	}
	j = 0;
	for (int i = 0; i < N; i++) {
		while (j > 0 && A[i] != B[j])
			j = pi[j - 1];
		if (A[i] == B[j]) {
			if (j == M - 1) {
				cnt++;
				j = pi[j];
			}
			else
				j++;
		}
	}
	return cnt;
}
}