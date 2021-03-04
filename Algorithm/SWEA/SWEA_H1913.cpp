/* Completed!!
 *
 *
 */

#define MAX_N 1000
#define MAX_M 20

struct Result {
	int y, x;
};

typedef struct PAIR
{
	int x, y;
}pair_t;

typedef struct StarMap {
	int cnt, cx, cy, size;
	pair_t rotate[20][4];  // 0 : original
						   // 1 : 90
						   // 2 : 180
						   // 3 : 270
}star;

int Map[MAX_N][MAX_N];
int Stars[MAX_M][MAX_M];
int star_cnt = 0;
pair_t star_pool [MAX_M];
star s;
int star_map[MAX_N][MAX_N];
int n, m;

void init(int N, int M, int Map[MAX_N][MAX_N])
{

	n = N;
	m = M;
	star_cnt = 0;
	for (register int i = 0; i < n; i++) {
		for (register int j = 0; j < n; j++) {
			star_map[i][j] = Map[i][j];
		}
	}
}

Result findConstellation(int stars[MAX_M][MAX_M])
{
	Result res;
	star_cnt = 0;
	int M = 0, curx = 0, cury = 0;

	for (register int i = 0; i < m; i++) {
		for (register int j = 0; j < m; j++) {
			if (stars[i][j] == 9) {
				s.cx = i;
				s.cy = j;
				star_pool[star_cnt].x = i;
				star_pool[star_cnt++].y = j;
			}
			else if (stars[i][j] == 1) {
				star_pool[star_cnt].x = i;
				star_pool[star_cnt++].y = j;
			}
		}
	}
	s.size = m;
	s.cnt = star_cnt;
	int movx, movy, movcx = s.cx, movcy = s.cy;
	for (register int i = 0; i < star_cnt; i++) {
		curx = star_pool[i].x;
		cury = star_pool[i].y;
		s.rotate[i][0].x = curx - s.cx;
		s.rotate[i][0].y = cury - s.cy;
		s.rotate[i][1].x = s.rotate[i][0].y;
		s.rotate[i][1].y = (-1) * s.rotate[i][0].x;
		s.rotate[i][2].x = (-1) * s.rotate[i][0].x;
		s.rotate[i][2].y = (-1) * s.rotate[i][0].y;
		s.rotate[i][3].x = (-1) * s.rotate[i][0].y;
		s.rotate[i][3].y = s.rotate[i][0].x;
	}

	movx = movy = 0;

	for (register int i = 0; i < n; i++) {
		for (register int j = 0; j < n; j++) {
			if (star_map[i][j]) {
				for (register int u = 0; u < 4; u++) {
					bool find = true;
					int find_cnt = 0;
					for (register int k = 0; k < s.cnt && find; k++) {
						movx = i + s.rotate[k][u].x;
						movy = j + s.rotate[k][u].y;
						if (movx < 0 || movx >= n || movy < 0 || movy >= n || !star_map[movx][movy]) find = false;
						find_cnt++;
					}
					if (find && find_cnt == s.cnt) {
						for (register int k = 0; k < s.cnt && find; k++) {
							movx = i + s.rotate[k][u].x;
							movy = j + s.rotate[k][u].y;
							star_map[movx][movy] = 0;
							
						}
						res.y = i; res.x = j;
						return res;
					}
					find_cnt = 0;
				}
			}
		}
	}

	res.y = res.x = 0;
	return res;
}