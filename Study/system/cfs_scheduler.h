/* CFS scheduler simulator
 *
 * [header]
 *
 * This code include slicetime, vruntime of CFS scheduler.
 * It was made by referring on actual CFS kernel code ( ~/kernel/sched/fair.c)
 *
 */

#define WMULT_CONST (~0U)
#define WMULT_SHIFT 32
#define MAX_TASK 100

typedef unsigned long long 	u64;
typedef unsigned int 		u32;

u64 sysctl_sched_latency = 6000000; // 6 ms
int sched_nr_latency = 8;
u64 sysctl_sched_min_granularity = 750000; // 0.75 ms

static const int prio_to_weight[40] = {
	/* -20 */     88761,     71755,     56483,     46273,     36291,
	/* -15 */     29154,     23254,     18705,     14949,     11916,
	/* -10 */      9548,      7620,      6100,      4904,      3906,
	/*  -5 */      3121,      2501,      1991,      1586,      1277,
	/*   0 */      1024,       820,       655,       526,       423,
	/*   5 */       335,       272,       215,       172,       137,
	/*  10 */       110,        87,        70,        56,        45,
	/*  15 */        36,        29,        23,        18,        15,
};

struct load_weight {
	unsigned long weight;
	u32 inv_weight;
};

// CFS run queue struct
struct cfs_rq {
	int nr_running;
	struct load_weight load;
	struct sched_entity* curr;

};

struct sched_entity {
	int task_idx;
	int called;
	int on_rq;
	int nice;
	struct load_weight load;
	struct cfs_rq* cfs_rq;
	u64 vruntime;
};

struct cfs_rq cfs_pool;
struct sched_entity se_list[MAX_TASK] = { 0 };
static int sched_entity_idx = 0;
struct cfs_rq* cfs_queue;

struct sched_entity* se_alloc(void) {
	return &se_list[sched_entity_idx++];
}

u64 __sched_period(int nr_running);
void update_load_add(struct load_weight* lw, unsigned long inc);
void __update_inv_weight(struct load_weight* lw);
u64 __calc_delta(u64 delta_exec, unsigned long weight, struct load_weight* lw);
u64 sched_slice(struct cfs_rq* cfs_rq, struct sched_entity* se);



