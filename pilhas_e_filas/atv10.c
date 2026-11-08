#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio; 
    int fim;    
} Fila;

void inicializar(Fila *f) { f->inicio = 0; f->fim = 0; }
int  vazia(Fila *f)       { return f->fim == 0; }
int  cheia(Fila *f)       { return f->fim == MAX; }

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

int inserir(Fila *f, int valor) {
    if (cheia(f)) return 0;
    f->dados[f->fim++] = valor;
    return 1;
}

int remover(Fila *f, int *valor) {
    if (vazia(f)) return 0;
    *valor = f->dados[0];
    for (int i = 1; i < f->fim; i++) f->dados[i - 1] = f->dados[i];
    f->fim--;
    f->inicio = 0;
    return 1;
}

void mostrar(Fila *f) {
    if (vazia(f)) { printf("Nenhuma tarefa na fila.\n"); return; }
    printf("Tarefas (proxima -> ultima): ");
    for (int i = f->inicio; i < f->fim; i++) printf("%d ", f->dados[i]);
    printf("\n");
}

void executarRodada(Fila *f) {
    int id, resp;
    if (!remover(f, &id)) { printf("Nenhuma tarefa para executar.\n"); return; }
    printf("Executando tarefa %d.\n", id);

    
    while (!lerInt("Tarefa concluida? (1-Sim / 0-Nao): ", &resp) || (resp != 0 && resp != 1)) {
        if (feof(stdin)) { resp = 0; break; } 
        printf("Responda 1 ou 0.\n");
    }

    if (resp == 1) {
        printf("Tarefa %d concluida e removida do rodizio.\n", id);
    } else {
        inserir(f, id); 
        printf("Tarefa %d nao concluida; voltou para o final da fila.\n", id);
    }
    mostrar(f);
}

int main(void) {
    Fila f;
    int op, id;
    inicializar(&f);

    do {
        printf("\n1-Adicionar tarefa 2-Executar rodada 3-Mostrar fila 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1:
                if (lerInt("Id da tarefa: ", &id)) {
                    if (inserir(&f, id)) printf("Tarefa %d adicionada.\n", id);
                    else printf("Fila cheia! Tarefa %d nao adicionada.\n", id);
                }
                break;
            case 2: executarRodada(&f); break;
            case 3: mostrar(&f); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}