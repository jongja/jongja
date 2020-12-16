#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_LOC_SIZE 11
#define MAX_PRICE_SIZE 1001
#define MAX_FRIEND_SIZE 1001
#define MAX_TOUR_HASE_SIZE 1000000
#define PN 23
#define MAX_TOUR_POOL 40010
#define MAX_FNODE_POOL 1000000
#define NULL 0

//TODO 링크드리스트 다시 재조정해야함


// struct area //
typedef struct TourStruct {
	int pid, area, price;
	struct TourStruct* next;
	struct TourStruct* prev;
	struct TourStruct* next_price;
	struct TourStruct* prev_price;
	struct TourStruct* next_pid;
	struct TourStruct* prev_pid;
}tour_t;

typedef struct FriendNode {
	int user;
	struct FriendNode* next;
}fnode;

typedef struct UserStruct {
	tour_t* reserved_tour;
	fnode* list;
}user_t;


// tour allocate area //
tour_t tour_data_pool[MAX_TOUR_POOL] = { 0 };
int tour_data_pool_idx = 0;
tour_t* tour_alloc() {
	return &tour_data_pool[tour_data_pool_idx++];
}

fnode fnode_data_pool[MAX_FNODE_POOL] = { 0 };
int fnode_data_pool_idx = 0;
fnode* fnode_alloc() {
	return &fnode_data_pool[fnode_data_pool_idx++];
}


// global area //
tour_t* tour_list[MAX_LOC_SIZE] = { 0 };
tour_t* price_list[MAX_PRICE_SIZE] = { 0 };
user_t user_data[MAX_FRIEND_SIZE] = { 0 };
tour_t* tour_hash[MAX_TOUR_HASE_SIZE] = { 0 };

void tour_hash_insert(tour_t* newData) {
	unsigned long long idx = newData->pid * 23;
	int hash_idx = idx % MAX_TOUR_HASE_SIZE;
	tour_t* head = tour_hash[hash_idx];
	if (!head) {
		tour_hash[hash_idx] = newData;
	}
	else {
		newData->next_pid = head;
		head->prev_pid = newData;
		head = newData;
	}
}

tour_t* tour_hash_find(int pid) {
	unsigned long long idx = pid * 23;
	int hash_idx = idx % MAX_TOUR_HASE_SIZE;
	tour_t* walker = tour_hash[hash_idx];
	while (walker) {
		if (walker->pid == pid) break;
		walker = walker->next_pid;
	}
	return walker;
}

void friend_list_insert(fnode* newFriend, int head_idx) {
	if (!user_data[head_idx].list) {
		user_data[head_idx].list = newFriend;
	}
	else {
		newFriend->next = user_data[head_idx].list;
		user_data[head_idx].list = newFriend;
	}
	return;
}

void price_list_insert(tour_t* newData) {
	if (!price_list[newData->price]) {
		price_list[newData->price] = newData;
	}
	else {
		tour_t* walker = price_list[newData->price];
		while (walker->next_price) {
			if (walker->pid > newData->pid) { // insert middle node.

				if(walker->prev_price)
					walker->prev_price->next_price = newData;
				newData->prev_price = walker->prev_price;
				newData->next_price = walker;
				walker->prev_price = newData;
				return;
			}
			walker = walker->next_price;
		}
		if (walker->pid > newData->pid && walker == price_list[newData->price]) { // insert head node.

			newData->next_price = walker;
			walker->prev_price = newData;
			price_list[newData->price] = newData;
			return;
		}
		walker->next_price = newData; // insert last node.
		newData->prev_price = walker;
	}
	return;
}

void tour_list_insert(tour_t* newData) {
	if (!tour_list[newData->area]) {
		tour_list[newData->area] = newData;
		price_list_insert(newData);
	}
	else {
		tour_t* walker = tour_list[newData->area];
		while (walker->next) {
			if (walker->price >= newData->price) { // insert middle node.

				if (walker->prev)
				walker->prev->next = newData;
				newData->prev = walker->prev;
				newData->next = walker;
				walker->prev = newData;

				price_list_insert(newData);
				return;
			}
			walker = walker->next;
		}
		if (walker->price >= newData->price && walker == tour_list[newData->area]) { // insert head node.

			newData->next = walker;
			walker->prev = newData;
			tour_list[newData->area] = newData;

			price_list_insert(newData);
			return;
		}
		walker->next = newData; // insert last node.
		newData->prev = walker;
		price_list_insert(newData);
	}
	return;
}

void init(int N, int M)
{
	tour_data_pool_idx = 0;
	fnode_data_pool_idx = 0;
	for (int i = 0; i < MAX_TOUR_HASE_SIZE; i++) {
		if (i < MAX_LOC_SIZE)
			tour_list[i] = NULL;
		if (i < MAX_PRICE_SIZE) {
			price_list[i] = NULL;
			user_data[i].reserved_tour = NULL;
			user_data[i].list = NULL;
		}
		tour_hash[i] = NULL;
	}
}


void befriend(int uid1, int uid2)
{
	fnode* f1 = fnode_alloc();
	f1->user = uid1;
	f1->next = NULL;
	fnode* f2 = fnode_alloc();
	f2->user = uid2;
	f2->next = NULL;

	friend_list_insert(f2, uid1);
	friend_list_insert(f1, uid2);

}

void add(int pid, int area, int price)
{
	tour_t* newData = tour_alloc();
	newData->area = area;
	newData->pid = pid;
	newData->price = price;
	newData->next = NULL;
	newData->prev = NULL;
	newData->next_price = NULL;
	newData->prev_price = NULL;
	newData->next_pid = NULL;
	newData->prev_pid = NULL;
	tour_list_insert(newData);
	tour_hash_insert(newData);
}

void delete_tour(int pid) {
	tour_t* dnode = tour_hash_find(pid);

	if (!dnode->prev) {
		if (dnode->next) {
			tour_list[dnode->area] = dnode->next;
			dnode->next->prev = NULL;
		}
		else 
			tour_list[dnode->area] = NULL;
	}
	else {
		if (dnode->prev)
			dnode->prev->next = dnode->next;
		if (dnode->next)
			dnode->next->prev = dnode->prev;
	}

	if (!dnode->prev_pid) {
		unsigned long long idx = pid * 23;
		int hash_idx = idx % MAX_TOUR_HASE_SIZE;
		if (dnode->next_pid) {
			tour_hash[hash_idx] = dnode->next_pid;
			dnode->next_pid->prev_pid = NULL;
		}
		else
			tour_hash[hash_idx] = NULL;
	}
	else {
		if (dnode->prev_pid)
			dnode->prev_pid->next_pid = dnode->next_pid;
		if (dnode->next)
			dnode->next_pid->prev_pid = dnode->prev_pid;
	}

	if (!dnode->prev_price) {
		if (dnode->next_price) {
			price_list[dnode->price] = dnode->next_price;
			dnode->next_price->prev_price = NULL;
		}
		else
			price_list[dnode->price] = NULL;
	}
	else {
		if (dnode->prev_price)
			dnode->prev_price->next_price = dnode->next_price;
		if (dnode->next_price)
			dnode->next_price->prev_price = dnode->prev_price;
	}
	
	dnode->prev = NULL;
	dnode->next = NULL;
	dnode->prev_price = NULL;
	dnode->next_price = NULL;
	dnode->prev_pid = NULL;
	dnode->next_pid = NULL;
	return;
}



void reserve(int uid, int pid)
{
	user_data[uid].reserved_tour = tour_hash_find(pid);
	delete_tour(pid);
	return;
}

int recommend(int uid)
{
	user_t user = user_data[uid];
	fnode* walker = user.list;
	int result = 0, total = 0;
	bool reserv = false;
	int cnt[MAX_FRIEND_SIZE] = { 0 };

	if (user.reserved_tour) {
		cnt[user.reserved_tour->area]++;
		total++;
		reserv = true;
	}

	while (walker) {
		if (user_data[walker->user].reserved_tour) {
			int idx = user_data[walker->user].reserved_tour->area;
			cnt[idx]++;
			total++;
			reserv = true;
		}
		walker = walker->next;
	}

	if (!reserv) {
		int i;
		for (i = 1; i < MAX_PRICE_SIZE; i++) {
			if (price_list[i]) break;
		}
		result = price_list[i]->pid;
	}
	else {
		int max_cnt = 0, pre_max_idx = 1e9, max_idx = 0, loop = total, max_idx_pid = 1e11;
		bool done = false;
		while (total--) {
			max_cnt = 0;
			max_idx = 0;
			max_idx_pid = 1e11;
			for (int k = 1; k <= MAX_LOC_SIZE; k++) {
				if (!tour_list[k]) continue;
				if (cnt[k] >= 1 && max_cnt <= cnt[k] && pre_max_idx > cnt[k] && max_idx_pid > tour_list[k]->pid) {
					if (max_cnt == cnt[k] && total) 
						total--;
					max_cnt = cnt[k];
					max_idx = k;
					max_idx_pid = tour_list[k]->pid;
				}
			}
			pre_max_idx = max_cnt;	
		}
		if (tour_list[max_idx]) {
			done = true;
			result = tour_list[max_idx]->pid;
		}
		if (!done) {
			int i;
			for (i = 1; i < MAX_PRICE_SIZE; i++) {
				if (price_list[i]) break;
			}
			result = price_list[i]->pid;
		}
	}
	return result;
}

#define INIT			100
#define BEFRIEND		200
#define ADD				300
#define RESERVE			400
#define RECOMMEND		500

static bool run()
{
	int L, N, M;
	bool okay = false;

	int pid, uid;
	int uid1, uid2;
	int area, price;

	int ans;
	int cmd, ret;

	scanf("%d", &L);

	for (int l = 0; l < L; ++l)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			scanf("%d %d", &N, &M);
			init(N, M);
			okay = true;
			break;
		case BEFRIEND:
			scanf("%d %d", &uid1, &uid2);
			befriend(uid1, uid2);
			break;
		case ADD:
			scanf("%d %d %d", &pid, &area, &price);
			add(pid, area, price);
			break;
		case RESERVE:
			scanf("%d %d", &uid, &pid);
			reserve(uid, pid);
			break;
		case RECOMMEND:
			scanf("%d %d", &uid, &ans);
			ret = recommend(uid);
			if (ret != ans)
				okay = false;
			break;
		}
	}

	return okay;
}

int main() {
	int TC, MARK;

	freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d %d", &TC, &MARK);

	for (int testcase = 1; testcase <= TC; ++testcase) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", testcase, score);
	}

	return 0;
}