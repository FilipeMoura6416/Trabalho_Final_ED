#ifndef Splay_h
#define Splay_h

typedef struct dicionario{
   char id_palavra[30];
   char info_sinonimo[30];
   int FB;
   struct dicionario *pai;
   struct dicionario *esq;
   struct dicionario *dir;
} Arvore;

extern long int zig_rot, zag_rot, zigzag_rot, zigzig_rot, zagzig_rot, zagzag_rot, comp, nodos; 

Arvore* insere_splay(Arvore* a,char id[30], char info[30]);
Arvore* consulta_splay(Arvore *a, char *id);
Arvore* move_para_raiz(Arvore* nodo);
Arvore* caso1(Arvore* nodo);
Arvore* caso2(Arvore* nodo);
Arvore* caso3(Arvore* nodo);
Arvore* zig(Arvore* nodo);
Arvore* zag( Arvore* nodo);
Arvore* zigzig(Arvore* nodo);
Arvore* zagzag(Arvore* nodo);
Arvore* zigzag(Arvore* nodo);
Arvore* zagzig(Arvore* nodo);
Arvore* split(Arvore* nodo, char *id, char* info);
int altura_arvore(Arvore* a);

#endif
