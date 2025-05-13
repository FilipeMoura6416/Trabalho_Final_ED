#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp = 0, rotacoes = 0, nodos = 0;

//Funções predefinidas do moodle, comentários feitos nas alterações relevantes
Arvore* rotacao_esquerda(Arvore *p)
{
    Arvore *z;
    z = p->dir;
    p->dir = z->esq;
    p->FB = 0;
    z->esq = p;
    p = z;
    return p;
}

Arvore* rotacao_direita(Arvore *p)
{
    Arvore *u;
    u = p->esq;
    p->esq = u->dir;
    p->FB = 0;
    u->dir = p;
    p = u;
    return p;
}

Arvore* rotacao_dupla_direita(Arvore *p)
{
    Arvore *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}

Arvore* rotacao_dupla_esquerda(Arvore *p)
{
    Arvore *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}

//Adicionado um parâmetro extra e, alterado o código para o tratamento de strings
Arvore* InsereAVL(Arvore *a, char id[30], char info[30], int *ok)
{
    if (a == NULL)
    {
        a = (Arvore *)malloc(sizeof(Arvore));
        
        strcpy(a->id_palavra,  id);
        strcpy(a->info_sinonimo,  info);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp(id, a->id_palavra) > 0)
    {
        a->esq = InsereAVL(a->esq, id, info, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                rotacoes++;
                a = Caso1(a, ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir, id, info, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                rotacoes++;
                a = Caso2(a, ok);
                break;
            }
        }
    }
    return a;
}

Arvore* Caso1(Arvore *a, int *ok)
{
    Arvore *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);

    else
        a = rotacao_dupla_direita(a);

    a->FB = 0;
    *ok = 0;
    return a;
}

Arvore* Caso2(Arvore *a, int *ok)
{
    Arvore *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);

    else
        a = rotacao_dupla_esquerda(a);

    a->FB = 0;
    *ok = 0;
    return a;
}

//Alterado o código para o tratamento de strings
Arvore* consulta(Arvore *a, char *chave)
{
	while (a!=NULL)
	{
		comp++;
		if (!strcmp(a->id_palavra,chave) )
		{
			comp++;
			return a;
		}
		else
		{
			comp++;
			if (strcmp(a->id_palavra,chave) < 0)
			a = a->esq;
			else
			a = a->dir;
		}
	}
 return NULL;
 }

 int altura_arvore(Arvore* a)
 {
    if(a == NULL)
        return 0;
    else
    {
        int esq = altura_arvore(a->esq);
        int dir = altura_arvore(a->dir);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }

 }