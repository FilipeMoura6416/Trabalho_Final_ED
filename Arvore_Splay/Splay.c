#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int comp = 0, zig_rot = 0, zag_rot = 0, zigzig_rot = 0, zagzag_rot, zigzag_rot = 0, zagzig_rot = 0, nodos = 0;


Arvore* insere_splay(Arvore* a,char id[30], char info[30])
{
    //Essa função recebe as informações a serem incluídas na estrutura e as insere na árvore
    //Crie um nodo com as informações
    //Insere o nodo na árvore
    //Faz as rotações para trazer o nodo para a raiz
        //
    if(a == NULL)
    {
        a = (Arvore* )malloc(sizeof(Arvore));
        strcpy(a->id_palavra, id);
        strcpy(a->info_sinonimo,  info);
        a->esq = NULL;
        a->dir = NULL;
        a->pai = NULL;
        a->FB = 0;
    }else
    {
        a = consulta_splay(a, id);
        a = split(a, id, info);
    }

    return a;
}

Arvore* consulta_splay(Arvore *a, char *id)
{
    //Essa função consulta um id na árvore e retorna o nodo correspondente
    //Se não houver o nodo retorna o último consultado
    Arvore* ant;
	while (a!=NULL) //Enquanto não chegar em uma folha
	{
        comp++;
		if (!strcmp(a->id_palavra, id)) //Se achar o nodo procurado
		{
            a = move_para_raiz(a);  //Move ele para a raiz
			return a;
		}
		else
		{
            ant  = a; //Backup do ponteiro
			if (strcmp(a->id_palavra,id) > 0) //Verifica se é para ir para a direita ou para a esquerda
			a = a->esq;
			else
			a = a->dir;
		}
	}
    //Se chegou aqui é pq chegou em uma folha sem achar o nodo procurado
    ant = move_para_raiz(ant); //Move o último nodo consultado para a raiz

 return ant;
}

Arvore* move_para_raiz(Arvore* nodo)
{
    //Essa função recebe um nodo e o move para raiz
    while(nodo->pai != NULL)
    {
        if(nodo->pai->pai == NULL) //Se o pai do nodo for a raiz é zag ou zig
        {
            //caso1
            nodo = caso1(nodo);
        }else                       //Senão deve-se fazer rotação dupla
        {

            if(nodo->pai->dir == nodo) //Se o nodo for o filho direito faz zag zag ou zag zig
            {
                //caso2
                nodo = caso2(nodo);

            }else                       //Senão faz zigzig ou zigzag
            {
                //caso3
                nodo = caso3(nodo);
            }
        }
    }

    return nodo;
}

Arvore* caso1(Arvore* nodo)
{
    if(nodo->pai->dir == nodo) //Se o nodo for o filho direito faz zag
    {
        nodo = zag(nodo);
        zag_rot++;  //Incrementa Contador de rotações zag
    }else                       //Se for o filho esquerdo faz zig
    {
        nodo = zig(nodo);
        zig_rot++; //Incrementa Contador de rotações zig
    }

    return nodo;

}

Arvore* caso2(Arvore* nodo)
{
    if(nodo->pai->pai->dir == nodo->pai) //Se o pai for filho dereito do avô faz zag zag
    {
        nodo = zagzag(nodo);
        zagzag_rot++; //Incrementa Contador de rotações zagzag
    }else                                //Senão faz zagzig
    {
        nodo = zagzig(nodo);
        zagzig_rot++; //Incrementa Contador de rotações zagzig
    }

    return nodo;
}

Arvore* caso3(Arvore* nodo)
{
    if(nodo->pai->pai->dir == nodo->pai) //Se o pai for filho dereito do avô faz zig zag
    {
        nodo = zigzag(nodo);
        zigzag_rot++; //Incrementa Contador de rotações zigzag
    }else                                //Senão faz zigzig
    {
        nodo = zigzig(nodo);
        zigzig_rot++;  //Incrementa Contador de rotações zigzig
    }
    return nodo;

}

Arvore* zig(Arvore* nodo)
{
    //O nodo vira pai, o pai vira filho direito do nodo e o filho direito do nodo vira filho esquerdo do pai
    Arvore* x = nodo;
    Arvore* p = nodo->pai;
    Arvore* t2 = nodo->dir;

    x->dir = p;
    x->pai = p->pai;
    p->pai = x;
    p->esq = t2;
    if(t2)
    t2->pai = p;
    return x;

}

Arvore* zag( Arvore* nodo)
{
    Arvore* x = nodo;
    Arvore* p = nodo->pai;
    Arvore* t2 = nodo->esq;

    x->esq = p;
    x->pai = p->pai;
    p->pai = x;
    p->dir = t2;
    if(t2)
    t2->pai = p;
    return x;

}

Arvore* zigzig(Arvore* nodo)
{
    Arvore* x = nodo;
    Arvore* p = nodo->pai;
    Arvore* v = nodo->pai->pai;
    Arvore* t2 = nodo->pai->dir;
    Arvore* t3 = nodo->dir;
    x->pai = v->pai;
    x->dir = p;
    v->pai = p;
    v->esq = t2;
    p->pai = x;
    p->dir = v;
    p->esq = t3;
    if(t2)
    t2->pai = v;
    if(t3)
    t3->pai = p;
    if(x->pai)
    {
       if(x->pai->dir == v)
        {
            x->pai->dir = x;
        }else
        {
            x->pai->esq = x;
        }
    }

    return x;


}

Arvore* zagzag(Arvore* nodo)
{
    Arvore* x = nodo;
    Arvore* p = nodo->pai;
    Arvore* v = nodo->pai->pai;
    Arvore* t2 = nodo->pai->esq;
    Arvore* t3 = nodo->esq;
    x->pai = v->pai;
    x->esq = p;
    v->pai = p;
    v->dir = t2;
    p->pai = x;
    p->esq = v;
    p->dir = t3;
    if(t2)
    t2->pai = v;
    if(t3)
    t3->pai = p;
    if(x->pai)
    {
        if(x->pai->esq == v)
        {
            x->pai->esq = x;
        }else
        {
            x->pai->dir = x;
        }
    }

    return x;

}

Arvore* zigzag(Arvore* nodo)
{
    Arvore* n1 = nodo->pai->pai;
    Arvore* n2 = nodo->pai;
    Arvore* n5 = nodo;
    Arvore* n6 = nodo->esq;
    Arvore* n7 = nodo->dir;

    if(n6)
    n6->pai = n1;
    if(n7)
    n7->pai = n2;
    n5->pai = n1->pai;
    n1->pai = n5;
    n2->pai = n5;
    if(n5->pai)
    {
        if(n5->pai->dir == n1)
        {
            n5->pai->dir = n5;
        }else
        {
            n5->pai->esq = n5;
        }
    }
    n2->esq = n7;
    n1->dir = n6;
    n5->esq = n1;
    n5->dir = n2;

    return n5;

}

Arvore* zagzig(Arvore* nodo)
{
    Arvore* n1 = nodo->pai->pai;
    Arvore* n2 = nodo->pai;
    Arvore* n5 = nodo;
    Arvore* n6 = nodo->dir;
    Arvore* n7 = nodo->esq;

    if(n6)
    n6->pai = n1;
    if(n7)
    n7->pai = n2;
    n5->pai = n1->pai;
    n1->pai = n5;
    n2->pai = n5;
    if(n5->pai)
    {
        if(n5->pai->esq == n1)
        {
            n5->pai->esq = n5;
        }else
        {
            n5->pai->dir = n5;
        }
    }
    n2->dir = n7;
    n1->esq = n6;
    n5->dir = n1;
    n5->esq = n2;

    return n5;

}

Arvore* split(Arvore* nodo, char *id, char* info)
{ 
    //Essa função executa um split, ela é uma função auxiliar logo se parte do princípio que
    //O foi executado um consulta_splay antes de executar a split
    //Para que o nodo que está na raiz seja o filho direito ou esquerdo no novo nodo

    Arvore* novo_nodo = (Arvore*)malloc(sizeof(Arvore));
    strcpy(novo_nodo->id_palavra, id);
    strcpy(novo_nodo->info_sinonimo, info);
    novo_nodo->pai = NULL;
    if(strcmp(novo_nodo->id_palavra, nodo->id_palavra) > 0) //Verifica se o nodo vai ser filho direito ou esquerdo do novo_nodo
    {
        novo_nodo->dir = nodo->dir;
        nodo->dir = NULL;
        novo_nodo->esq = nodo;
        if(novo_nodo->dir)
        novo_nodo->dir->pai = novo_nodo;
        nodo->pai = novo_nodo;
    }else
    {
        novo_nodo->esq = nodo->esq;
        nodo->esq = NULL;
        //
        novo_nodo->dir = nodo;
        if(novo_nodo->esq)
        novo_nodo->esq->pai = novo_nodo;
        nodo->pai = novo_nodo;
    }

    return novo_nodo;
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



/*
 Arvore* insere_auxiliar(Arvore* a, Arvore* nodo)//Essa função recebe a árvore e o nodo a ser inserido
 {
    //
    Arvore* ant;
    while (a!=NULL)
	{
        ant  = a;
        if (strcmp(a->id_palavra, nodo->id_palavra) > 0)
        a = a->esq;
        else
        a = a->dir;
	}
    if(strcmp(ant->id_palavra, nodo->id_palavra) > 0)
    {
        ant->esq = nodo;
        nodo->pai = ant;

    }else
    {
        ant->dir = nodo;
        nodo->pai = ant;
    }

 }*/
