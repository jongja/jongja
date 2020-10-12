/* [SWEA] 4408
 * Completed!
 * 
 * Memory : 296 KB
 * Time   : 1 ms
 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

int T, N;

int main(void) {
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        int ans = 0;
        int room[201] = { 0 };
        scanf("%d", &N);
        while (N--) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a > b) { int t = a; a = b; b = t; }

            if (a & 1) a++;
            a /= 2;

            if (b & 1) b++;
            b /= 2;

            for (int i = a; i <= b; i++)
                room[i]++;
        }
        for (int i = 1; i <= 200; i++)
            if (ans < room[i])
                ans = room[i];
        printf("%d\n", ans);
    }

    return 0;

}