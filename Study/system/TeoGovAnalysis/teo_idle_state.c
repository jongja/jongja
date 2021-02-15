/* This code was taken from the Linux mainline for analysis and study purposes. 
 * State that it is not for commercial use.
 *
 * URL:
 * https://github.com/torvalds/linux/blob/master/drivers/cpuidle/governors/teo.c
 * 
 * Anaysis by jongja.
 *
 */

/* Teo idle state

 @early_hits    : Indicates the most likely number to be chosen. If this value of the state is high, that state can be selected.
 @hits          : Number of times that the state is correct for selection
 @misses        : Number of times that the state is not correct for selection

*/
struct teo_idle_state {
    unsigned int early_hits;
    unsigned int hits;
    unsigned int misses;
};


/* Teo cpu

@ time_span_ns      : the real time of previous state.
@ sleep_length_ns   : the predicted time of next state(until the next timer event).
@ states            : information of state for teo governor (hits, misses)


            idle                         idle        
      |--------------|running task|-----------------|
      | time_span_ns |            | sleep_length_ns |  
                                    |               |
                                 current point      |
                                                   next timer event

*/
struct teo_cpu {
    u64 time_span_ns;
    u64 sleep_length_ns;
    struct teo_idle_state states[CPUIDLE_STATE_MAX];
    int interval_idx;
    u64 intervals[INTERVALS];
};