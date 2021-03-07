////////////////////////////////////////////////////////////////////////////////

#define salloc() &nodes[sidx]

#define MALE   0
#define FEMALE 1

#define COUPLE  0
#define PARENT  1
#define CHILD   2

#define MAXN 200
#define MAXH 13003
#define MAXLEN 20
#define MAXHEAP 400
#define INF 1000000000
#define NULL 0

int sidx = 0;
int distance_map[MAXN][MAXN];
bool visit[MAXN];
int dtable[MAXN];

struct Person {
	int idx;
	char name[MAXLEN];
	int sex;
	Person* parent[2]; // 0: father, 1: mother
	Person* couple;
	Person* child;
	Person* next;
	Person* c_next;
}nodes[MAXN], *htable[MAXH];

//	 The below commented functions are for your reference. If you want 
//	 to use it, uncomment these functions.

/* STRING FUNCTIONS */
int mstrcmp(const char a[], const char b[])
{
	register int i;
	for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
	return a[i] - b[i];
}

void mstrcpy(char dest[], const char src[])
{
	register int i = 0;
	while (src[i] != '\0') { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}

/* STRING FUNCTIONS END */

/* HEAP */

struct Pair {
	int dist;
	int idx;
};

struct Heap {
	int size;
	Pair data[MAXHEAP];
	void init() {
		size = 0;
	}
	void push(Pair val) {
		if (size == MAXHEAP)
			return;
		register int cur = ++size;
		while (cur != 1 && val.dist < data[cur >> 1].dist) {
			data[cur] = data[cur >> 1];
			cur >>= 1;
		}
		data[cur] = val;
	}

	void pop() {
		if (size == 0)
			return;
		register Pair e = data[size--];
		register int cur = 1, ch = 2;
		while (ch <= size) {
			if (ch < size && data[ch].dist > data[ch + 1].dist) ch++;
			if (e.dist <= data[ch].dist) break;
			data[cur] = data[ch];
			cur = ch; ch <<= 1;
		}
		data[cur] = e;
	}

	Pair top() {
		return data[1];
	}

}h;

/* HEAP END*/

/* HASH FUNCTIONS */

int hashing(register char* s) {
	register unsigned int key = 0, step = 1, pn = 23;
	for (; *s; s++) {
		key += (*s * step);
		step *= pn;
	}
	return  key % MAXH;
}

void insert_hash(Person* newNode) {
	int key = hashing(newNode->name);
	Person* head = htable[key];
	if (!head) {
		htable[key] = newNode;
	}
	else {
		newNode->next = head;
		htable[key] = newNode;
	}
}

int search_hash(char* name) {
	int key = hashing(name);
	register Person* walker = htable[key];
	while (walker) {
		if (!mstrcmp(walker->name, name)) {
			return walker->idx;
		}
		walker = walker->next;
	}
	return -1;
}

/* HASH FUNCTIONS END */

/* DIJKSTRA */

void dijkstra_connect(int cur) {
	h.init();
	for (register int i = 0; i < sidx; i++) {
		visit[i] = false;
		dtable[i] = INF;
	}
	visit[cur] = true;
	dtable[cur] = 0;
	h.push({ 0, cur });
	while (h.size) {
		int curr_dist = h.top().dist;
		int curr = h.top().idx;
		h.pop();

		// Parent search
		if (nodes[curr].parent[0]) {
			if (dtable[nodes[curr].parent[0]->idx] > curr_dist + 1) {
				dtable[nodes[curr].parent[0]->idx] = curr_dist + 1;
				h.push({ curr_dist + 1, nodes[curr].parent[0]->idx });
			}
		}
		if (nodes[curr].parent[1]) {
			if (dtable[nodes[curr].parent[1]->idx] > curr_dist + 1) {
				dtable[nodes[curr].parent[1]->idx] = curr_dist + 1;
				h.push({ curr_dist + 1, nodes[curr].parent[1]->idx });
			}
		}

		// Couple search
		if (nodes[curr].couple) {
			if (dtable[nodes[curr].couple->idx] > curr_dist) {
				dtable[nodes[curr].couple->idx] = curr_dist;
				h.push({ curr_dist, nodes[curr].couple->idx });
			}
		}

		// child
		if (nodes[curr].child) {
			Person* c = nodes[curr].child;
			while (c) {
				if (dtable[c->idx] > curr_dist + 1) {
					dtable[c->idx] = curr_dist + 1;
					h.push({ curr_dist + 1, c->idx });
				}
				c = c->c_next;
			}
		}
	}

	for (register int i = 0; i < sidx; i++) {
		if (cur == i) distance_map[cur][cur] = -1;
		else {
			distance_map[i][cur] = dtable[i];
			distance_map[cur][i] = dtable[i];
		}
	}
}

/* DIJKSTRA END*/

bool can_i_join(int idx, int nms, int rel) {
	if (rel == CHILD) 
		return true;
	else if (rel == COUPLE) {
		if (nodes[idx].couple) {
			return false;
		}
		else if (nodes[idx].sex == nms)
			return false;
	}
	else if (rel == PARENT) {
		if (nms == FEMALE && nodes[idx].parent[FEMALE])
			return false;
		if (nms == MALE && nodes[idx].parent[MALE])
			return false;
	}
	return true;
}


void init(char initialMemberName[], int initialMemberSex)
{
	sidx = 0;
	for (register int i = 0; i < MAXH; i++) {
		htable[i] = NULL;
	}
	for (register int i = 0; i < MAXN; i++) {
		for (register int j = 0; j < MAXN; j++) {
			distance_map[i][j] = INF;
		}
	}

	register Person* newNode = salloc();
	newNode->child = newNode->couple = newNode->parent[0] = newNode->parent[1] = newNode->next = newNode->c_next = NULL;
	newNode->idx = sidx++;
	mstrcpy(newNode->name, initialMemberName);
	newNode->sex = initialMemberSex;
	insert_hash(newNode);
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
	int dst = search_hash(existingMemberName);
	if (dst < 0) {
		return false;
	}

	if (!can_i_join(dst, newMemberSex, relationship)) {
		return false;
	}
	
	Person* exmem = &nodes[dst];

	// init newNode
	Person* newNode = salloc();
	newNode->child = newNode->couple = newNode->parent[0] = newNode->parent[1] = newNode->next = newNode->c_next = NULL;
	newNode->idx = sidx++;
	mstrcpy(newNode->name, newMemberName);
	newNode->sex = newMemberSex;
	insert_hash(newNode);

	// connect relationship
	if (relationship == PARENT) {
		exmem->parent[newMemberSex] = newNode;
		if (exmem->parent[!newMemberSex]) {
			exmem->parent[!newMemberSex]->couple = newNode;
			newNode->couple = exmem->parent[!newMemberSex];
			register Person* walker = exmem->parent[!newMemberSex]->child;
			while (walker) {
				walker->parent[newMemberSex] = newNode;
				walker = walker->c_next;
			}
			newNode->child = exmem->parent[!newMemberSex]->child;
		}
		else {
			newNode->child = exmem;
		}
	}
	else if (relationship == COUPLE) {
		exmem->couple = newNode;
		newNode->couple = exmem;
		if (exmem->child) {
			newNode->child = exmem->child;
			register Person* walker = exmem->child;
			while (walker) {
				walker->parent[newMemberSex] = newNode;
				walker = walker->c_next;
			}
		}
	}
	else if(relationship == CHILD){
		register Person* walker = exmem->child;
		if (!walker) {
			exmem->child = newNode;
		}
		else {
			newNode->c_next = exmem->child;
			exmem->child = newNode;
		}
		newNode->parent[exmem->sex] = exmem;
		if (exmem->couple) {
			newNode->parent[exmem->couple->sex] = exmem->couple;
		}

	}

	dijkstra_connect(newNode->idx);
	return true;
}

int getDistance(char nameA[], char nameB[])
{
	int a = search_hash(nameA);
	int b = search_hash(nameB);
	if (a < 0 || b < 0)
		return -1;
	return distance_map[a][b];
}

int countMember(char name[], int dist)
{
	int a = search_hash(name);
	int cnt = 0;
	for (int i = 0; i < sidx; i++)
		if (dist == distance_map[a][i])
			cnt++;
	return cnt;
}