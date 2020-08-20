/* HASHING TEST
 *
 * Hashing algorithm that has minimum collision
 * TIME COMPLEXITY : O(1)
 * datas_size : input data
 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
using namespace std;

char datas[200][200] = {
	"Amelia",
"Aaron",
"Abigail",
"Adam",
"Aisha",
"Albert",
"Alex",
"Alexander",
"Alfie",
"Alice",
"Amber",
"Amelie",
"Amy",
"Anna",
"Annabelle",
"Archie",
"Arthur",
"Austin",
"Ava",
"Beatrice",
"Bella",
"Benjamin",
"Bethany",
"Blake",
"Bobby",
"Brooke",
"Caleb",
"Callum",
"Charles",
"Charlie",
"Charlotte",
"Chloe",
"Connor",
"Daisy",
"Daniel",
"Darcey",
"Darcie",
"Darcy",
"David",
"Dexter",
"Dylan",
"Edward",
"Eleanor",
"Elijah",
"Eliza",
"Elizabeth",
"Ella",
"Ellie",
"Elliot",
"Elliott",
"Ellis",
"Elsie",
"Emilia",
"Emily",
"Emma",
"Erin",
"Esme",
"Ethan",
"Eva",
"Evelyn",
"Evie",
"Faith",
"Felix",
"Finlay",
"Finley",
"Florence",
"Francesca",
"Frankie",
"Freddie",
"Frederick",
"Freya",
"Gabriel",
"George",
"Georgia",
"Grace",
"Gracie",
"Hannah",
"Harley",
"Harper",
"Harriet",
"Harrison",
"Harry",
"Harvey",
"Heidi",
"Henry",
"Hollie",
"Holly",
"Hugo",
"Ibrahim",
"Imogen",
"Isaac",
"Isabel",
"Isabella",
"Isabelle",
"Isla",
"Ivy",
"Jack",
"Jackson",
"Jacob",
"Jake",
"James",
"Jamie",
"Jasmine",
"Jayden",
"Jenson",
"Jessica",
"Joey",
"Joseph",
"Joshua",
"Jude",
"Julia",
"Kai",
"Katie",
"Kian",
"Lacey",
"Layla",
"Leah",
"Leo",
"Leon",
"Lewis",
"Lexi",
"Liam",
"Lilly",
"Lily",
"Logan",
"Lola",
"Lottie",
"Louie",
"Louis",
"Luca",
"Lucas",
"Lucy",
"Luke",
"Lydia",
"Maisie",
"Maria",
"Martha",
"Maryam",
"Mason",
"Matilda",
"Matthew",
"Max",
"Maya",
"Megan",
"Mia",
"Michael",
"Millie",
"Mollie",
"Molly",
"Muhammad",
"Nancy",
"Nathan",
"Noah",
"Oliver",
"Olivia",
"Ollie",
"Oscar",
"Owen",
"Phoebe",
"Poppy",
"Reuben",
"Riley",
"Robert",
"Robyn",
"Ronnie",
"Rory",
"Rose",
"Rosie",
"Ruby",
"Ryan",
"Samuel",
"Sara",
"Sarah",
"Scarlett",
"Sebastian",
"Seth",
"Sienna",
"Sofia",
"Sonny",
"Sophia",
"Sophie",
"Stanley",
"Summer",
"Teddy",
"Thea",
"Theo",
"Theodore",
"Thomas",
"Toby",
"Tommy",
"Tyler",
"Victoria",
"Violet",
"William",
"Willow",
"Zachary",
"Zara",
"Zoe"
};

#define HASH_SIZE 2000000
#define PRIME_NUM 23
#define PRIME_NUM2 29
#define MAX_STR_SIZE 100
#define MAX_ALLOCATE_POOL_SIZE 2000000

int collision = 0;

typedef struct HashNode {
	char str[MAX_STR_SIZE];
	int val;
	struct HashNode* next;
	struct HashNode* prev;
}hnode;

hnode allocate_pool_array[MAX_ALLOCATE_POOL_SIZE] = { 0 };
int allocate_pool_idx = 0;
hnode* hash_table[HASH_SIZE] = { 0 }; // hash table

hnode* salloc() {
	return &allocate_pool_array[allocate_pool_idx++];
}

unsigned long long hasing(char* str) { // hasing function for string
	unsigned long long key = 0, p = 1;
	for (int i = 0; str[i]; i++) {
		key += str[i] * p;
		p *= PRIME_NUM;
	}
	return key % HASH_SIZE;
}

int hasing(int val) { // hasing function for integer value (NOT IMPLEMENTED)
	int a = val * PRIME_NUM;
	int b = val % PRIME_NUM2;
	return ((val % PRIME_NUM) * (val % PRIME_NUM2)) % HASH_SIZE;
}

void insert_hash_table(hnode* newNode) {
	int idx = hasing(newNode->str);
	//int idx = newNode->val % HASH_SIZE; 
	if (hash_table[idx] == NULL) {
		hash_table[idx] = newNode;
		return;
	}
	else {
		collision++;
		hash_table[idx]->prev = newNode;
		newNode->next = hash_table[idx];
		hash_table[idx] = newNode;
	}
}

int main(void) {
	srand((unsigned int)time(NULL));
	int datas_size = 1000000;
	char input[200] = { 0 };

	for (int i = 0; i < datas_size; i++) {
		int temp_val = rand() * PRIME_NUM2 + (i % 2) * PRIME_NUM2;
		char a = 97 + rand() % 22;
		char b = 97 + rand() % 22;
		char c = 97 + rand() % 22;
		char d = 97 + rand() % 22;
		sprintf(input, "%c%s%c %c%s%c", c, datas[rand() % 197], a, d, datas[rand() % 197], b);
		hnode* newNode = salloc();
		strcpy(newNode->str, input);
		newNode->val = temp_val;
		insert_hash_table(newNode);
	}


	cout << "Data count > " << datas_size << endl;
	cout << "Collision > " << collision << endl;

	return 0;
}

