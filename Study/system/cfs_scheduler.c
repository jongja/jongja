/* CFS scheduler
 *
 * This code include slicetime, vruntime of CFS scheduler.
 * It was made by referring on actual CFS kernel code ( ~/kernel/sched/fair.c)
 * 
 */

#include <stdio.h>

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

struct sched_entity{
	int on_rq;
	int load;
	int inv_load;
};


int main(void){
	return 0;
}
