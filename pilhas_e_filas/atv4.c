#include <stdio.h>

#define MAX 32

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
    if (vazia(p)) return 0;
    *valor = p->dados[p->topo--];
    return 1;
}

int main(void) {
    Pilha p;
    int n, bit;
    inicializar(&p);

    printf("Numero inteiro nao negativo: ");
    if (scanf("%d", &n) != 1) { printf("Entrada invalida.\n"); return 1; }
    if (n < 0) { printf("Entrada negativa rejeitada.\n"); return 1; }

    if (n == 0) {
        empilhar(&p, 0);           
    } else {
        int q = n;                 
        while (q > 0) {
            empilhar(&p, q % 2); 
            q /= 2;
        }
    }

    printf("%d em binario: ", n);
    while (desempilhar(&p, &bit)) printf("%d", bit);
    printf("\n");
    return 0;
}