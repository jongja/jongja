/* STRING FUNCTION PERFORMANCE TEST
 *
 * strcpy() vs _strcpy()
 * strcmp() vs _strcmp()
 *
 * Result :
 *      (stl)strcpy > 0.013 sec.
 *      (my)strcpy > 0.055 sec.
 *
 *      (stl)strcmp > 0.008 sec.
 *      (my)strcmp > 0.053 sec.
 *
 *      (stl)strlen > 0.006 sec.
 *      (my)strlen > 0.05 sec.
 *
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

#define MAX_STR_SIZE 1000000
#define MAX_STR_LEN 30

char stl_data1[MAX_STR_SIZE][MAX_STR_LEN];
char my_data1[MAX_STR_SIZE][MAX_STR_LEN];

char stl_data2[MAX_STR_SIZE][MAX_STR_LEN];
char my_data2[MAX_STR_SIZE][MAX_STR_LEN];

char stl_data3[MAX_STR_SIZE][MAX_STR_LEN];
char my_data3[MAX_STR_SIZE][MAX_STR_LEN];


int _strlen(char* str) { // Simple string length function
    int len = 0;
    while (*(str++)) len++;
    return len;
}

void _strcpy(char* dest, char* src) { // Simple string copy function
    while (*(src)) *(dest++) = *(src++);
    *dest = '\0';
    return;
}


int _strcmp(char* str1, char* str2) { // Simple string compare function
    while (*(str1)) {
        if (*(str1) != *(str2)) {
            return *(str1) > * (str2) ? 1 : -1;
        }
        str1++; str2++;
    }
    return *(str2) == '\0' ? 0 : -1;
}

char mc() { // make char
    return 'A' + (rand() % 24 + 1);
}

void MakeData(char(*str1)[30], char(*str2)[30]) { // Make Data (length : 24)
    char data[MAX_STR_LEN] = { 0 };
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        sprintf(data, "%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c %c%c%c%c%c%c%c",
            mc(), mc(), mc(), mc(), mc(), mc(), mc(), mc(), mc()
            , mc(), mc(), mc(), mc(), mc(), mc()
            , mc(), mc(), mc(), mc(), mc(), mc(), mc());
        strcpy(str1[i], data);
        strcpy(str2[i], data);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    time_t st, ed;

    /* STEP 1 STRCPY TEST*/
    MakeData(stl_data1, my_data1);
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strcpy(stl_data2[i], stl_data1[i]);
    }
    ed = clock();
    cout << "(stl)strcpy > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strcpy(my_data2[i], my_data1[i]);
    }
    ed = clock();
    cout << "(my)strcpy > " << (double)(ed - st) / CLOCKS_PER_SEC << endl << endl;


    /* STEP 2 STRCMP TEST*/
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strcmp(stl_data2[i], stl_data1[i]);
    }
    ed = clock();
    cout << "(stl)strcmp > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strcmp(my_data2[i], my_data1[i]);
    }
    ed = clock();
    cout << "(my)strcmp > " << (double)(ed - st) / CLOCKS_PER_SEC << endl << endl;

    /* STEP 3 STRLEN TEST*/
    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        strlen(stl_data2[i]);
    }
    ed = clock();
    cout << "(stl)strlen > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    st = clock();
    for (int i = 0; i < MAX_STR_SIZE; i++) {
        _strlen(my_data2[i]);
    }
    ed = clock();
    cout << "(my)strlen > " << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    return 0;
}