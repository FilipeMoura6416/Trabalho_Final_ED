#ifndef AVL_h
#define AVL_h

extern int comp, rotacoes, nodos;

//Estrutura da AVL
typedef struct dicionario{
   char id_palavra[30];
   char info_sinonimo[30];
   int FB;
   struct dicionario *esq;
   struct dicionario *dir;
} Arvore;

//Funções da AVL
Arvore* consulta(Arvore *a, char *chave);
Arvore* Caso2(Arvore *a, int *ok);
Arvore* Caso1(Arvore *a, int *ok);
Arvore* InsereAVL(Arvore *a, char id[30], char info[30], int *ok);
Arvore* rotacao_dupla_esquerda(Arvore *p);
Arvore* rotacao_dupla_direita(Arvore *p);
Arvore* rotacao_direita(Arvore *p);
Arvore* rotacao_esquerda(Arvore *p);
int altura_arvore(Arvore* a);

#endif