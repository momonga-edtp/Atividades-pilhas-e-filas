#include <stdio.h>

#define MAX 10

typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

void inicializar(Pilha *p) { p->topo = -1; }
int  vazia(Pilha *p)       { return p->topo == -1; }
int  cheia(Pilha *p)       { return p->topo == MAX - 1; }

int empilhar(Pilha *p, int valor) {
    if (cheia(p)) { printf("Pilha cheia!\n"); return 0; }
    p->dados[++p->topo] = valor;
    return 1;
}

int desempilhar(Pilha *p, int *valor) {
    if (vazia(p)) { printf("Pilha vazia!\n"); return 0; }
    *valor = p->dados[p->topo--];
    return 1;
}

int main(void) {
    Pilha p;
    int n, v;
    inicializar(&p);

    do {
        printf("Quantidade de numeros (1 a %d): ", MAX);
        if (scanf("%d", &n) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            if (feof(stdin)) return 1;
            n = 0;
        }
        if (n < 1 || n > MAX) printf("Quantidade invalida.\n");
    } while (n < 1 || n > MAX);

    for (int i = 0; i < n; i++) {
        printf("Valor %d: ", i + 1);
        while (scanf("%d", &v) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            if (feof(stdin)) return 1;
            printf("Valor invalido, digite novamente: ");
        }
        empilhar(&p, v);
    }

    printf("Ordem inversa: ");
    int primeiro = 1;
    while (!vazia(&p)) {         
        desempilhar(&p, &v);
        printf(primeiro ? "%d" : ", %d", v);
        primeiro = 0;
    }
    printf("\nPilha vazia ao final? %s\n", vazia(&p) ? "sim" : "nao");
    return 0;
}