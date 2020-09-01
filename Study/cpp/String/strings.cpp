/* STRING SERIES
 * strcpy(), strcmp(), strlen()
 * 
 *
*/

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
            return *(str1) > *(str2) ? 1 : -1;
        }
        str1++; str2++;
    }
    return *(str2) == '\0' ? 0 : -1;
}