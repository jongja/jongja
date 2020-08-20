/* HASHING
 * 
 * Hashing algorithm that has minimum collision
 * TIME COMPLEXITY : O(1)
 * 
 */

#include <iostream>
using namespace std;

#define HASH_SIZE 1000000
#define PRIME_NUM 23
#define	PRIME_NUM2 29

unsigned int hasing(char* str) { // hasing function for string
	unsigned key = 0, p = 1;
	for (int i = 0; str[i]; i++) {
		key += str[i] * p;
		p *= PRIME_NUM;
	}
	return key % HASH_SIZE;
}

int main(void) {
	char str1[] = "Goooood!";
	int idx = hasing(str1);
	cout << "STR : " << str1 << endl;
	cout << "IDX : " << idx << endl;
	return 0;
}