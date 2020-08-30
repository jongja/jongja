/* atoi()
 * ASCII string to integer
 *
 */

int _atoi(char* str) {
    int s = 1;
    int res = 0;

    if (*str == '-')
        s = -1;

    while (*str) {
        if (*str >= '0' && *str <= '9')
            res = res * 10 + *str - '0';
        str++;
    }
    return res * s;
}