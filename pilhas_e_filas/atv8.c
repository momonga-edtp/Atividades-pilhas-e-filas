#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio;
    int fim;
} Fila;

void inicializar(Fila *f) { f->inicio = 0; f->fim = 0; }
int  vazia(Fila *f)       { return f->inicio == f->fim; }
int  cheia(Fila *f)       { return f->fim == MAX; }

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

void adicionarTrabalho(Fila *f, int id) {
    if (cheia(f)) { printf("Fila de impressao cheia. Trabalho %d recusado.\n", id); return; }
    f->dados[f->fim++] = id;
    printf("Trabalho %d enviado para a fila.\n", id);
}

int removerTrabalho(Fila *f, int *id) {
    if (vazia(f)) return 0;
    *id = f->dados[f->inicio++];
    return 1;
}

void imprimirProximo(Fila *f) {
    int id;
    if (!removerTrabalho(f, &id)) { printf("Nenhum trabalho pendente.\n"); return; }
    printf("Imprimindo trabalho %d...\n", id);
}

void listarPendentes(Fila *f) {
    if (vazia(f)) { printf("Nenhum trabalho pendente.\n"); return; }
    printf("Pendentes (proximo -> ultimo): ");
    for (int i = f->inicio; i < f->fim; i++) printf("%d ", f->dados[i]);
    printf("\n");
}

void imprimirTodos(Fila *f) {
    int id, total = 0;
    if (vazia(f)) { printf("Nenhum trabalho pendente.\n"); return; }
    while (removerTrabalho(f, &id)) {
        printf("Imprimindo trabalho %d...\n", id);
        total++;
    }
    printf("%d trabalho(s) impresso(s). Fila vazia.\n", total);
}

int main(void) {
    Fila f;
    int op, id;
    inicializar(&f);

    do {
        printf("\n=== Impressora ===\n");
        printf("1-Adicionar trabalho 2-Imprimir proximo 3-Listar pendentes 4-Imprimir todos 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: if (lerInt("Id do trabalho: ", &id)) adicionarTrabalho(&f, id); break;
            case 2: imprimirProximo(&f); break;
            case 3: listarPendentes(&f); break;
            case 4: imprimirTodos(&f); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}