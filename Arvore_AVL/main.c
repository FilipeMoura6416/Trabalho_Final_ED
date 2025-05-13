//----------------------------------------------- INCLUDES -----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "AVL.h"

//---------------------------------------- CABEÇALHOS DAS FUNÇÕES ----------------------------------------
Arvore* le_dicionario(FILE* dicionario, Arvore *a_dicionario);
void substitui(FILE *entrada, FILE* saida, Arvore *a_dicionario);
int abre_arquivos(int argc, char* argv[], FILE** entrada, FILE** dicionario, FILE** saida);

//------------------------------------------ PROGRAMA PRINCIPAL ------------------------------------------
int main(int argc, char* argv[]){

    // Libera o uso de acentos
    setlocale(LC_ALL, "Portuguese");

    //----------VARIÁVEIS DO PROGRAMA---------
    Arvore *a_dicionario = NULL;
    FILE   *dicionario = fopen("dict_33K_sorted.txt", "r"), *entrada = fopen("pata_da_gazelaCap1.txt", "r"), *saida = fopen("saida.txt", "w");
    FILE*  relatorio = fopen("relatorio.txt", "w");
    clock_t start, end; //para contar o tempo decorrido
    start = clock();

    if(!abre_arquivos(argc, argv, &entrada, &dicionario, &saida)) //Verifica se todos os arquivos foram abertos corretamente
    {
       return 0;
    } 
    else
    {
        a_dicionario = le_dicionario(dicionario, a_dicionario);

        //Enquanto não chegar no fim do texto
        substitui(entrada, saida, a_dicionario);
        fprintf(relatorio, "Numero de Nodos: %d\n Numero de Rotações: %d\n Comparações feitas na inserção: %d\n", nodos, rotacoes, comp);
        end = clock(); // finaliza contagem do tempo
        float tempo = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
        printf("Tempo: %.5lf ms\n",tempo);
        fprintf(relatorio, "Tempo: %.5lf ms\n", tempo);
        fprintf(relatorio, "Altura da árvore: %d\n", altura_arvore(a_dicionario));
        fputs("\n", relatorio);
    }

    //fecha os arquivos
    _fcloseall();
	return 1;
}


//----------------------------------------------- FUNÇÕES ------------------------------------------------
Arvore* le_dicionario(FILE* dicionario, Arvore *a_dicionario)
{
    //Essa função lê as palavras e seus sinônimos e os coloca na árvore AVL
    char *id, *info, linha_dicionario[1000], separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    int ok= 0;
    while(!feof(dicionario))
    {
        //Lê uma linha
        fgets(linha_dicionario, 64, dicionario);

        //Separa o id e a info
        id = strtok (linha_dicionario, separador); //considera qquer caractere n�o alfab�tico como separador
        info = strtok (NULL, separador);

        //insere na AVL
        nodos++;
        if(id && info)
            a_dicionario = InsereAVL(a_dicionario, id, info, &ok);

    }
        
        return a_dicionario;
}

void substitui(FILE *entrada, FILE* saida, Arvore *a_dicionario)
{

    char linha[1000] = {}, separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"}, *id;
    Arvore *aux_dicionario = NULL;

    //Enquanto não chegar no fim do arquivo
    while(!feof(entrada))
    {
        //Le a linha do texto 
            fgets(linha, 1000, entrada);
            //Tokeniza as palavras
            id = strtok (linha, separador); //considera qualquer caractere n�o alfab�tico como separador
            while (id != NULL)
            {
                id = strlwr(id);
                //Verifica se estão no dicionário

                aux_dicionario = consulta(a_dicionario, id);
                //Escreve na saída
                if(aux_dicionario && !strcmp(aux_dicionario->id_palavra, id))
                {
                    fprintf(saida, "%s ", aux_dicionario->info_sinonimo);
                }else
                {
                    fprintf(saida, "%s ", id);
                }
                id = strtok (NULL, separador);
            }
            fputs("\n", saida);

    }

}

int abre_arquivos(int argc, char* argv[], FILE** entrada, FILE** dicionario, FILE** saida)
{
    printf("Abre_arquivos\n");
    int flag = 1;
    if(argc == 4)
    {
        *entrada = fopen(argv[1], "r");
        if(entrada == NULL)
        {
            printf("Erro ao abrir arquivo de entrada\n");
            flag = 0;
        }else
        {
            if(ferror(*entrada))
            {
                printf("Error");
            }else
            printf("Sucesso na abertura da entrada\n");
        }
        *dicionario = fopen(argv[2], "r");
        if(dicionario == NULL)
        {
            printf("Erro ao abrir dicionario\n");
            flag = 0;
        }else
        {
            if(ferror(*dicionario))
            {
                printf("Error");
            }else
            printf("Sucesso na abertura do dicionario\n");
        }
        *saida = fopen(argv[3], "w");
        if(saida == NULL)
        {
            printf("Erro ao criar arquivo de saida\n");
            flag = 0;
        }else
        {
            if(ferror(*saida))
            {
                printf("Error");
            }else
            printf("Sucesso na abertura da saida\n");
        }
    
    }else
    {
        printf("Número incorreto de parâmetros\n");
        flag = 0;
    }

    return flag;
}
