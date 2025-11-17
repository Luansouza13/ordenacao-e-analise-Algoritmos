#include "sorts.h"
#include <stdlib.h>

void reset_metrics(Metrics *m) {
    m->cmp = 0;
    m->swap = 0;
}

/* -------------------- INSERTION SORT ----------------------- */
void insertion_sort(int *v, size_t n, Metrics *m) {
    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        size_t j = i;

        while (j > 0) {
            COUNT_CMP(m);
            if (v[j - 1] <= key) break;

            v[j] = v[j - 1];
            COUNT_SWAP(m);
            j--;
        }

        v[j] = key;
        COUNT_SWAP(m);
    }
}

/* ------------------------- MERGE SORT ------------------------ */

static void merge(int *v, int *aux, size_t l, size_t m, size_t r, Metrics *met) {
    size_t i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        COUNT_CMP(met);
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++], COUNT_SWAP(met);
    }

    while (i <= m) aux[k++] = v[i++];
    while (j <= r) aux[k++] = v[j++];

    for (size_t x = l; x <= r; x++) {
        v[x] = aux[x];
        COUNT_SWAP(met);
    }
}

static void merge_sort_rec(int *v, int *aux, size_t l, size_t r, Metrics *met) {
    if (l >= r) return;

    size_t m = (l + r) / 2;

    merge_sort_rec(v, aux, l, m, met);
    merge_sort_rec(v, aux, m + 1, r, met);
    merge(v, aux, l, m, r, met);
}

void merge_sort(int *v, size_t n, Metrics *m) {
    int *aux = malloc(n * sizeof(int));
    merge_sort_rec(v, aux, 0, n - 1, m);
    free(aux);
}

/* ------------------------- QUICK SORT (Lomuto) ------------------------- */

static size_t partition(int *v, size_t l, size_t r, Metrics *m) {
    int pivot = v[r];
    size_t i = l;

    for (size_t j = l; j < r; j++) {
        COUNT_CMP(m);
        if (v[j] < pivot) {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            COUNT_SWAP(m);
            i++;
        }
    }

    int tmp = v[i];
    v[i] = v[r];
    v[r] = tmp;
    COUNT_SWAP(m);

    return i;
}

static void quick_sort_rec(int *v, size_t l, size_t r, Metrics *m) {
    if (l >= r) return;

    size_t p = partition(v, l, r, m);

    if (p > 0) quick_sort_rec(v, l, p - 1, m);
    quick_sort_rec(v, p + 1, r, m);
}

void quick_sort(int *v, size_t n, Metrics *m) {
    quick_sort_rec(v, 0, n - 1, m);
}
