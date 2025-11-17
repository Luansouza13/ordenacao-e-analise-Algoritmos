#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>

typedef struct {
    long long cmp;
    long long swap;
} Metrics;

#define COUNT_CMP(m)   ((m)->cmp++)
#define COUNT_SWAP(m)  ((m)->swap++)

void reset_metrics(Metrics *m);

void insertion_sort(int *v, size_t n, Metrics *m);
void merge_sort(int *v, size_t n, Metrics *m);  
void quick_sort(int *v, size_t n, Metrics *m);  // partição Lomuto

#endif
