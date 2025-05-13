#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Splay.h"
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int abre_arquivos(int argc, char* argv[], FILE** entrada, FILE** dicionario, FILE** saida);


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "portuguese");

    //Abre os arquivos
    FILE* entrada = NULL;
    FILE* dicionario = NULL;
    FILE* saida;
    FILE* relatorio = fopen("relatorio.txt", "w");
    int flag = 1;

    if(!abre_arquivos(argc, argv, &entrada, &dicionario, &saida)) //Verifica se todos os arquivos foram abertos corretamente
    {
        return 0;
    }


    clock_t start, end; //para contar o tempo decorrido
    start = clock();

    //Lê dicionario e coloca na árvore
    char linha_dicionario[64];
    char *id;
    char *info;
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"};
    char linha[1000] = {};
    Arvore* a_dicionario = NULL;

    //Enquanto não chegar no fim do dicionario
    while(!feof(dicionario))
    {
        //Lê uma linha
        fgets(linha_dicionario, 64, dicionario);

        //Separa o id e a info
        id = strtok (linha_dicionario, separador); //considera qquer caractere n�o alfab�tico como separador
        info = strtok (NULL, separador);
        
        //Insere na árvore
        if(id && info)
        {
            nodos++;
            a_dicionario = insere_splay(a_dicionario, id, info);
        }
        

    }
    fprintf(relatorio, "Comparações feitas na inserção: %d\n", comp);
    fprintf(relatorio, "Rotações feitas na insere zig: %d, zag: %d, zigzig: %d, zagzag: %d, zigzag: %d, zagzig: %d\n", zig_rot, zag_rot, zigzig_rot, zagzag_rot, zigzag_rot, zagzig_rot);

    comp = 0;
    zig_rot = zag_rot = zigzig_rot = zagzag_rot = zigzag_rot = zagzig_rot = 0;
    //Enquanto não chegar no fim do texto
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
            a_dicionario = consulta_splay(a_dicionario, id);
            //Escreve na saída
            if(!strcmp(a_dicionario->id_palavra, id))
            {
                fprintf(saida, "%s ", a_dicionario->info_sinonimo);
            }else
            {
                fprintf(saida, "%s ", id);
            }
            id = strtok (NULL, separador);
        }
        fputs("\n", saida);
    }

    fprintf(relatorio, "Comparações feitas na parafrase: %d\n", comp);
    fprintf(relatorio, "Rotações feitas na parafrase zig: %d, zag: %d, zigzig: %d, zagzag: %d, zigzag: %d, zagzig: %d\n", zig_rot, zag_rot, zigzig_rot, zagzag_rot, zigzag_rot, zagzig_rot);
    
    end = clock(); // finaliza contagem do tempo
    float tempo = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
    printf("Tempo: %.5lf ms\n",tempo);
    fprintf(relatorio, "Tempo: %.5lf ms\n", tempo);
    fprintf(relatorio, "Altura da árvore: %d\n", altura_arvore(a_dicionario));
    fprintf(relatorio, "Número de nodos: %d\n", nodos);
    fputs("\n", relatorio);


    fclose(entrada);
    fclose(saida);
    fclose(dicionario);
    fclose(relatorio);

    return 0;
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
