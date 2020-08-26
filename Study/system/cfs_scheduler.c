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

u64 __calc_delta_fair(u64 delta, struct sched_entity* se) {
	if (se->load.weight != 1024)
		delta = __calc_delta(delta, 1024, &se->load);
	return delta;
}

u64 sched_vslice(struct cfs_rq* cfs_rq, struct sched_entity* se) {
	return __calc_delta_fair(sched_slice(cfs_rq, se), se);
}

/// Simulator API functions ///

void qsort(int l, int r, struct sched_entity* a) {
	if (l < r) {
		u64 p = a[l].vruntime;
		int i = l, j = r + 1;
		do {
			do i++; while (i <= r && a[i].vruntime < p);
			do j--; while (j >= 0 && a[j].vruntime > p);
			if (i < j) {
				struct sched_entity t = a[i]; a[i] = a[j]; a[j] = t;
			}
		} while (i < j);
		struct sched_entity t = a[l]; a[l] = a[j]; a[j] = t;
		qsort(l, j - 1, a);
		qsort(j + 1, r, a);
	}
}

void init() {
	cfs_queue = &cfs_pool;
	cfs_queue->nr_running = 0;
	cfs_queue->load.weight = 0;
	cfs_queue->load.inv_weight = 0;
	cfs_queue->curr = se_list;
}

int printMenu() {
	int input;
	printf("==== CFS scheduler simulator ====\n");
	printf(" 1. Insert Task\n 2. Start\n 3. Status\n 4. Exit\n");
	printf("=================================\n");
	printf("Input > ");
	scanf("%d", &input);
	if (input == 4) input = 0;
	return input;
}

void enqueue_entity(struct cfs_rq* cfs_rq) {
	struct sched_entity* se = se_alloc();
	int nice = 0;
	printf("Input nice(-20 to 19) > ");
	scanf("%d", &nice);
	while (nice < -20 || nice > 19) {
		printf("\nERROR: WRONG INPUT\n");
		printf("Input nice(-20 to 19) > ");
		scanf("%d", &nice);
	}

	se->task_idx = sched_entity_idx;
	se->nice = nice;
	se->load.weight = prio_to_weight[nice + 20];
	se->load.inv_weight = WMULT_CONST / se->load.weight;
	se->on_rq = 0;
	se->called = 0;
	se->cfs_rq = cfs_rq;
	se->vruntime = 0;
}

void status() {
	printf("\n[CFS status]\n");
	printf("Tasks\t%d\n", sched_entity_idx);
	printf("\n");
	return;
}

void start(struct cfs_rq* cfs_rq) {
	u64 delta = 312342; // random value
	int scheduling;
	printf("Input Sched time > ");
	scanf("%d", &scheduling);
	while (scheduling--) {
		cfs_rq->curr->vruntime += __calc_delta_fair(delta, cfs_rq->curr);
		cfs_rq->curr->called++;
		//printf("wow!, %d, %lld\n", cfs_rq->curr->task_idx, cfs_rq->curr->vruntime);
		qsort(0, sched_entity_idx - 1, se_list);
	}

	printf("\n-------------------------------------------\n");
	printf("task\tnice\tvruntime\tcall\n");
	printf("-------------------------------------------\n");

	for (int i = 0; i < sched_entity_idx; i++) {
		printf(" %d\t%3d\t%lld\t %d\n", se_list[i].task_idx, se_list[i].nice, se_list[i].vruntime, se_list[i].called);
	}
	printf("\n");
	return;
}


int main(void) {
	init();
	int ip;
	while (ip = printMenu()) {
		switch (ip) {
		case 1:
			enqueue_entity(cfs_queue);
			break;
		case 2:
			start(cfs_queue);
			break;
		case 3:
			status();
			break;
		}
	}
	return 0;
}