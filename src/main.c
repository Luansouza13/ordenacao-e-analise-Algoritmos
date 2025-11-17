#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h"

#define REPEAT 5

// Clona vetor
int *clone(const int *v, size_t n) {
    int *c = malloc(n * sizeof(int));
    memcpy(c, v, n * sizeof(int));
    return c;
}

double run_sort(
    void (*fn)(int*, size_t, Metrics*),
    int *v,
    size_t n,
    Metrics *m
) {
    reset_metrics(m);
    clock_t t0 = clock();
    fn(v, n, m);
    clock_t t1 = clock();
    return 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
}

void benchmark_case(
    char *method, 
    void (*fn)(int*,size_t,Metrics*),
    int *base,
    size_t n,
    char *caso
) {
    double tempo_sum = 0;
    long long cmp_sum = 0, swap_sum = 0;
    Metrics m;

    for (int i = 0; i < REPEAT; i++) {
        int *v = clone(base, n);
        double t = run_sort(fn, v, n, &m);
        tempo_sum += t;
        cmp_sum += m.cmp;
        swap_sum += m.swap;
        free(v);
    }

    printf("%s,%zu,%s,%lld,%lld,%.3f\n",
           method, n, caso,
           cmp_sum/REPEAT,
           swap_sum/REPEAT,
           tempo_sum/REPEAT
    );
}

int main() {
    srand(time(NULL));

    /* ------------- ENTRADA RGM ---------------- */
    char rgm_str[64];
    printf("Digite o RGM: ");
    scanf("%s", rgm_str);

    size_t n_rgm = strlen(rgm_str);
    int *rgm = malloc(n_rgm * sizeof(int));
    for (size_t i = 0; i < n_rgm; i++)
        rgm[i] = rgm_str[i] - '0';

    /* ------------- TAMANHOS DE TESTE ----------- */
    size_t Ns[] = {100, 1000, 10000};

    printf("metodo,N,caso,comparacoes,trocas,tempo_ms\n");

    /* ------------- TESTE RGM --------------------- */
    benchmark_case("insertion", insertion_sort, rgm, n_rgm, "rgm");
    benchmark_case("merge",     merge_sort,     rgm, n_rgm, "rgm");
    benchmark_case("quick",     quick_sort,     rgm, n_rgm, "rgm");

    /* ------------- TESTES ALEATÓRIOS ------------- */
    for (int i = 0; i < 3; i++) {
        size_t n = Ns[i];
        int *v = malloc(n * sizeof(int));
        for (size_t j = 0; j < n; j++)
            v[j] = rand() % 100000;

        benchmark_case("insertion", insertion_sort, v, n, "aleatorio");
        benchmark_case("merge",     merge_sort,     v, n, "aleatorio");
        benchmark_case("quick",     quick_sort,     v, n, "aleatorio");

        free(v);
    }

    free(rgm);
    return 0;
}
