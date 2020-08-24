/* [BOJ] 14889
 * Complete!
 *
 */

#include <iostream>
using namespace std;

int p[20][20];
int team[20] = { 0 };
int N = 0;

void startlink(int pnum, int ct, int &min) {
	team[pnum] = 1;
	if (N / 2 == ct) {
		int s_t = 0;
		int l_t = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (team[i] == team[j]) {
					if (team[j])
						s_t += p[i][j];
					else
						l_t += p[i][j];
				}
			}
		}
		s_t = s_t - l_t;
		if (s_t < 0)
			s_t *= (-1);
		if (min > s_t)
			min = s_t;
		team[pnum] = 0;
		return;
	}
	for (int i = pnum + 1; i < N; i++) {
		if (!team[i])
			startlink(i, ct + 1, min);
	}
	team[pnum] = 0;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> p[i][j];
	int min = 100;
	startlink(0, 1, min);
	cout << min << endl;
	return 0;
}