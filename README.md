Ordenação — Análise de Desempenho Aplicada ao RGM

Projeto em C — Estruturas de Dados / Algoritmos

1. Objetivo

Este projeto implementa e compara o desempenho de três algoritmos de ordenação em linguagem C:

Insertion Sort

Merge Sort

Quick Sort (partição Lomuto)

A análise é realizada:

Sobre os dígitos do RGM do aluno

Sobre vetores aleatórios de tamanhos 100, 1000 e 10000

Para cada algoritmo, são coletados:

Número de comparações

Número de trocas/movimentações

Tempo de execução em milissegundos

As saídas são impressas em formato CSV.

2. Estrutura do Projeto
/ordenacao-rgm-usuario
  |- src/
      |- main.c
      |- sorts.c
      |- sorts.h
  |- data/
      |- resultados.csv (opcional)
  |- README.md

3. Algoritmos Implementados
Insertion Sort

Algoritmo simples e in-place

Estável

Complexidade O(n²) no pior caso

Bom apenas para vetores pequenos

Merge Sort

Baseado em divisão e conquista

Estável

Complexidade sempre O(n log n)

Necessita vetor auxiliar (não é in-place)

Quick Sort (Lomuto)

Rápido na prática

Complexidade média: O(n log n)

Pior caso: O(n²)

Não é estável

Funciona in-place

4. Contagem de Passos

O projeto utiliza uma estrutura para contar operações:

typedef struct {
    long long cmp;
    long long swap;
} Metrics;

Política adotada:

Cada comparação conta 1 ponto em cmp

Cada troca ou movimentação conta 1 ponto em swap

Macros usadas nos algoritmos:

#define COUNT_CMP(m)   ((m)->cmp++)
#define COUNT_SWAP(m)  ((m)->swap++)

5. Medição de Tempo

Utiliza a função clock() da <time.h>:

clock_t t0 = clock();
fn(v, n, metrics);
clock_t t1 = clock();
double tempo_ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;

Cada algoritmo é executado 5 vezes por caso, e a média é registrada.

6. Conjunto de Testes
Entrada A — RGM

O RGM é lido como string

Convertido para vetor de dígitos

Ordenado pelos três algoritmos

Entrada B — Benchmarks aleatórios

Geração de vetores de:

100 elementos

1000 elementos

10000 elementos

Os valores variam entre 0 e 99999.

7. Saída em CSV

Formato utilizado:

metodo,N,caso,comparacoes,trocas,tempo_ms

Exemplo:

quick,1000,aleatorio,7560,3880,0.75

Casos possíveis:

rgm

aleatorio

8. Análise dos Resultados
Insertion Sort

Ruim para N ≥ 1000

Crescimento O(n²) evidente

Adequado apenas para o RGM (lista pequena)

Merge Sort

Desempenho estável

Crescimento O(n log n)

Precisa de memória adicional

Quick Sort

Geralmente o mais rápido

Baixo uso de memória

Risco de cair no pior caso, mas improvável em dados aleatórios

9. Conclusão

O algoritmo com melhor desempenho geral é o Quick Sort, considerando tempo médio, escalabilidade e uso de memória.

O Merge Sort é o mais consistente e estável, e pode ser a melhor escolha quando previsibilidade é importante.

O Insertion Sort só é adequado para vetores pequenos ou quase ordenados.

10. Compilação e Execução

Para compilar:

gcc src/main.c src/sorts.c -o ordena -O0

Para executar:

./ordena

Digite o RGM quando solicitado.

11. Licença

Projeto acadêmico. Livre para uso educacional.
