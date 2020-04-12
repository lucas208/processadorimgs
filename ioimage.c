#include <stdlib.h>
#include <stdio.h>
#include "ioimage.h"

//para a implementação das funções de leitura e escrita adaptei um algoritmo generalista de leitura de ppm ao 
//tipo específico que criei para armazenar a imagem na memória

Image readImage(char* nome)
{
    Image imagem;
    FILE *arquivo;

    if ((arquivo = fopen(nome, "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nome);
        exit(1);
    }

    fscanf(arquivo, "%s", imagem.identificador);
    fscanf(arquivo, "%d", &imagem.coluna);
    fscanf(arquivo, "%d", &imagem.linha);
    fscanf(arquivo, "%d", &imagem.maximo);

    imagem.pixels = calloc(imagem.linha, sizeof(Pixel *));
    for (int i = 0; i < imagem.linha; i++)
    {
        imagem.pixels[i] = calloc(imagem.coluna, sizeof(Pixel));
        for (int j = 0; j < imagem.coluna; j++)
        {
            fscanf(arquivo, "%hhu\n", &imagem.pixels[i][j].red);
            fscanf(arquivo, "%hhu\n", &imagem.pixels[i][j].green);
            fscanf(arquivo, "%hhu\n", &imagem.pixels[i][j].blue);
        }
    }

    fclose(arquivo);
    return imagem;
}

void desalocaImage(Image *imagem)
{
    for (int i = 0; i < imagem->linha; i++)
    {
        free(imagem->pixels[i]);
    }
    free(imagem->pixels);
}

void writeImage(char* nome, Image *imagem)
{
    FILE *arquivo;

    arquivo = fopen(nome, "w");

    fprintf(arquivo, "%s\n", imagem->identificador);
    fprintf(arquivo, "%d ", imagem->coluna);
    fprintf(arquivo, "%d\n", imagem->linha);
    fprintf(arquivo, "%d\n", imagem->maximo);

    for (int i = 0; i < imagem->linha; i++)
    {
        for (int j = 0; j < imagem->coluna; j++)
        {
            fprintf(arquivo, "%hhu ", imagem->pixels[i][j].red);
            fprintf(arquivo, "%hhu ", imagem->pixels[i][j].green);
            fprintf(arquivo, "%hhu\n", imagem->pixels[i][j].blue);
        }
    }

    fclose(arquivo);
    desalocaImage(imagem);
}
