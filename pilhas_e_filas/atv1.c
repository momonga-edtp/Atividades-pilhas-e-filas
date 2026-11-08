#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int topo;       
} Pilha;

void inicializar(Pilha *p) { p->topo = -1; }
int  vazia(Pilha *p)       { return p->topo == -1; }
int  cheia(Pilha *p)       { return p->topo == MAX - 1; }

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

void empilhar(Pilha *p, int valor) {
    if (cheia(p)) { printf("Pilha cheia! Nao foi possivel empilhar %d.\n", valor); return; }
    p->dados[++p->topo] = valor;
    printf("%d empilhado.\n", valor);
}

void desempilhar(Pilha *p) {
    if (vazia(p)) { printf("Pilha vazia! Nada a remover.\n"); return; }
    printf("%d desempilhado.\n", p->dados[p->topo--]);
}

void mostrar(Pilha *p) {
    if (vazia(p)) { printf("Pilha vazia.\n"); return; }
    printf("Pilha (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) printf("%d ", p->dados[i]);
    printf("\n");
}

void consultarTopo(Pilha *p) {
    if (vazia(p)) { printf("Pilha vazia: nao ha topo para consultar.\n"); return; }
    printf("Topo: %d\n", p->dados[p->topo]);
}

int quantidade(Pilha *p) { return p->topo + 1; }

int main(void) {
    Pilha p;
    int op, valor;
    inicializar(&p);

    do {
        printf("\n1-Empilhar 2-Desempilhar 3-Mostrar 4-Consultar topo 5-Quantidade 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: if (lerInt("Valor: ", &valor)) empilhar(&p, valor); break;
            case 2: desempilhar(&p); break;
            case 3: mostrar(&p); break;
            case 4: consultarTopo(&p); break;
            case 5: printf("Quantidade de elementos: %d\n", quantidade(&p)); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}