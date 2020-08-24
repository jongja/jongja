/* CFS scheduler simulator
 *
 * This code include slicetime, vruntime of CFS scheduler.
 * It was made by referring on actual CFS kernel code ( ~/kernel/sched/fair.c)
 *
 */

#include <stdio.h>
#include "cfs_scheduler.h"


u64 __sched_period(int nr_running) {
	if (nr_running > sched_nr_latency)
		return nr_running * sysctl_sched_min_granularity;
	else
		return sysctl_sched_latency;
}

void update_load_add(struct load_weight* lw, unsigned long inc) {
	lw->weight += inc;
	lw->inv_weight = 0;
}

void __update_inv_weight(struct load_weight* lw) {
	unsigned long w;
	if (lw->inv_weight) return;
	w = lw->weight;
	lw->inv_weight = WMULT_CONST / w;
}

// Function for calculate slice time of task.
// This function can replace with this formula. (KERNEL USE)
// actual_exec_time * ((weight(task) * inv_weight(cfs_rq)) >> 32)
u64 __calc_delta(u64 delta_exec, unsigned long weight, struct load_weight* lw) {
	int shift = WMULT_SHIFT;
	__update_inv_weight(lw);
	return (delta_exec * weight * lw->inv_weight) >> shift;
}

// Function for calculte time slice of task
u64 sched_slice(struct cfs_rq* cfs_rq, struct sched_entity* se) {
	u64 slice = __sched_period(cfs_rq->nr_running + !se->on_rq);
	struct load_weight lw;
	struct load_weight* load;

	load = &cfs_rq->load;

	if (!se->on_rq) {

		lw = cfs_rq->load;
		update_load_add(&lw, se->load.weight);
		load = &lw;
		cfs_rq->load.weight = lw.weight;

		se->on_rq = 1; // not here..
	}
	slice = __calc_delta(slice, se->load.weight, load);

	return slice;
}

void init() {
	cfs_queue = &cfs_pool;
	cfs_queue->nr_running = 0;
	cfs_queue->load.weight = 0;
	cfs_queue->load.inv_weight = 0;
	cfs_queue->curr = NULL;
}


int main(void) {
	init();
	int nice;
	printf("Nice > ");
	scanf("%d", &nice);

	struct sched_entity* se = se_alloc();
	se->nice = nice;
	se->load.weight = prio_to_weight[nice + 20];
	se->load.inv_weight = WMULT_CONST / se->load.weight;
	se->on_rq = 0;
	se->cfs_rq = cfs_queue;

	printf("%lld\n", sched_slice(cfs_queue, se));

	return 0;
}