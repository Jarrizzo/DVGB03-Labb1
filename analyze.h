#ifndef ANALYZE_H
#define ANALYZE_H

#define SIZE_START 512
#define ITERATIONS 4
#define WARMUP 999999
#define BILLION 1E9
#define BESTCASE 10
#define WORSTCASE 2
#define AVARAGECASE 5
#define _POSIX_C_SOURCE 199309L
#define BUBBLEITTERATIONS 50
#define INSERTIONITTERATIONS 50
#define QUICKITTERATIONS 50
#define SEARCHITTERATIONS 1000000

// algorithm_t defines different algorithms
typedef enum {
	bubble_sort_t,
	insertion_sort_t,
	quick_sort_t,
	linear_search_t,
	binary_search_t
} algorithm_t;

//enum för att hålla koll på alla O-notationer
typedef enum {
	O_one_t,
	O_n_t,
	O_n2_t,
	O_n3_t,
	O_logn_t,
	O_nlogn_t,
}O_NOTATION_t;

// case_t defines different cases
typedef enum {
	best_t,
	worst_t,
	average_t,
} case_t;

// result_t defines a timed measurement for a given array size
typedef struct {
	int size;
	double time;
	double big_O_notation_value ;
	double faster_O_notation_value;
	double slower_O_notation_value;
	O_NOTATION_t faster_O_notation_t;
	O_NOTATION_t slower_O_notation_t;
	O_NOTATION_t big_O_notation_t;

} result_t;

// benchmark benchmarks an algorithm a for a specific case c, writing n results
// to the result buffer buf
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n);

#endif
