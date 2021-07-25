//Declaração do tipo Abstrato Lista
//Assinaturas das funções de Lista

struct list{
    char *sub;
    int complexidade;
    struct list *prox;
};

typedef struct list Lista;

Lista* create(void);

Lista* add(Lista*, char *);

void print_list(Lista*);

int busca(Lista*, char *);

int tam_list(Lista *);

void free_list(Lista *node);