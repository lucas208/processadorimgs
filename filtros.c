#include <stdlib.h>
#include <stdio.h>
#include "ioimage.h"
#include "filtros.h"

Image grayscale(Image *imagem)
{
    Image gray;

    for (int i = 0; i < 3; i++)
    {
        gray.identificador[i] = imagem->identificador[i];
    }

    gray.coluna = imagem->coluna;
    gray.linha = imagem->linha;
    gray.maximo = imagem->maximo;

    gray.pixels = calloc(gray.linha, sizeof(Pixel *));
    for (int i = 0; i < gray.linha; i++)
    {
        gray.pixels[i] = calloc(gray.coluna, sizeof(Pixel));
        for (int j = 0; j < gray.coluna; j++)
        {
            Pixel p = imagem->pixels[i][j];
            unsigned char media = (p.red + p.green + p.blue) / 3;
            gray.pixels[i][j].red = media;
            gray.pixels[i][j].green = media;
            gray.pixels[i][j].blue = media;
        }
    }
    return gray;
}


//  O inteiro op da função abaixo serve para selecionar a matriz de convolução usada como filtro  

Image filtrar(int op, Image *imagem)
{
    int mat[3][3];

    if (op == 0)
    {
        return grayscale(imagem);
    }
    else if (op == 1)
    {
        int mat[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    }
    else if (op == 2)
    {
        int mat[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    }
    else if (op == 3)
    {
        int mat[3][3] = {{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}};
    }
    else if (op == 4)
    {
        int mat[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
    }
    else if (op == 5)
    {
        int mat[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    }

    Image filtrada;
    int somared, somagreen, somablue;
    int cont1, cont2;

    for (int i = 0; i < 3; i++)
    {
        filtrada.identificador[i] = imagem->identificador[i];
    }

    filtrada.coluna = imagem->coluna;
    filtrada.linha = imagem->linha;
    filtrada.maximo = imagem->maximo;

    filtrada.pixels = calloc(filtrada.linha, sizeof(Pixel *));
    for (int i = 0; i < filtrada.linha; i++)
    {
        filtrada.pixels[i] = calloc(filtrada.coluna, sizeof(Pixel));
    }

    for (int i = 1; i < filtrada.linha - 1; i++)
    {
        for (int j = 1; j < filtrada.coluna - 1; j++)
        {
            somared = 0;
            somagreen = 0;
            somablue = 0;
            cont1 = 0;
            cont2 = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                cont2 = 0;
                for (int l = j - 1; l <= j + 1; l++)
                {
                    somared += imagem->pixels[k][l].red * mat[cont1][cont2];
                    somagreen += imagem->pixels[k][l].green * mat[cont1][cont2];
                    somablue += imagem->pixels[k][l].blue * mat[cont1][cont2];
                    cont2++;
                }
                cont1++;
            }
           /* 
            essa parte dos "ifs" eu pesquisei para entender o porquê do resultado estar diferente do que esperava
            (quando eles não estavam incluídos), para algumas matrizes de convolução é necessário limitar o valor
            de cada componente dos pixels ao máximo
            */
            if (op != 1)
            {
                if (somared > 255)
                    somared = imagem->maximo;
                if (somagreen > 255)
                    somagreen = imagem->maximo;
                if (somablue > 255)
                    somablue = imagem->maximo;
                if (somared < 0)
                    somared = 0;
                if (somagreen < 0)
                    somagreen = 0;
                if (somablue < 0)
                    somablue = 0;

                filtrada.pixels[i][j].red = somared;
                filtrada.pixels[i][j].green = somagreen;
                filtrada.pixels[i][j].blue = somablue;
            }
            else
            {
                filtrada.pixels[i][j].red = somared / 9;
                filtrada.pixels[i][j].green = somagreen / 9;
                filtrada.pixels[i][j].blue = somablue / 9;
            }
        }
    }

    return filtrada;
}
/*
O if acima serve para separar o filtro blurring dos demais, pois esse filtro específico precisa
multiplicar a matriz de convolução por 1/9 (dividir por 9). Já em relação a limitar os componentes
do Pixel para um valor entre 255 e 0, isso não se faz necessário no blurring porque pelas características
da própria matriz de convolução isso nunca acontece.
*/

Image fourier(Image *imagem){

    /* Função para aplicar o filtro de Fourier. Essa função remove
    o ruído da imagem. Para uma melhor visualização do seu efeito
    é necessário aplicar a função à uma imagem chiada
    Filtro aplicado : [-1,0,1; -2,1,2; -1,0,1]*/

    Image fourier;

    for(int i=0; i<3; i++){
        fourier.identificador[i] = imagem->identificador[i];
    }

    fourier.linha = imagem->linha;
    fourier.coluna = imagem->coluna;
    fourier.maximo = imagem->maximo;

    fourier.pixels = calloc(fourier.linha,sizeof(Pixel *));
    for(int i =0; i<fourier.linha; i++){
        fourier.pixels[i] = calloc(fourier.coluna,sizeof(Pixel));
    }

    for (int i=1; i<fourier.linha-1; i++){
        for (int j=1; j<fourier.coluna-1; j++){

            int somared=0, somagreen=0, somablue=0;
            somared = (-imagem->pixels[i-1][j-1].red                         + imagem->pixels[i-1][j+1].red
                    - 2*imagem->pixels[i][j-1].red + imagem->pixels[i][j].red + 2*imagem->pixels[i][j+1].red
                    - imagem->pixels[i+1][j-1].red                              + imagem->pixels[i+1][j+1].red);
            if (somared<0){
                fourier.pixels[i][j].red = 0;
            }
            else if (somared>255){
                fourier.pixels[i][j].red = 255;
            }
            else{
                fourier.pixels[i][j].red = somared;
            }//RED



            somagreen = (-imagem->pixels[i-1][j-1].green                         + imagem->pixels[i-1][j+1].green
                    - 2*imagem->pixels[i][j-1].green + imagem->pixels[i][j].green + 2*imagem->pixels[i][j+1].green
                    - imagem->pixels[i+1][j-1].green                              + imagem->pixels[i+1][j+1].green);
            if (somagreen<0){
                fourier.pixels[i][j].green = 0;
            }
            else if (somagreen>255){
                fourier.pixels[i][j].green = 255;
            }
            else{
                fourier.pixels[i][j].green = somagreen;
            }//GREEN



            somablue = (-imagem->pixels[i-1][j-1].blue                         + imagem->pixels[i-1][j+1].blue
                    - 2*imagem->pixels[i][j-1].blue + imagem->pixels[i][j].blue + 2*imagem->pixels[i][j+1].blue
                    - imagem->pixels[i+1][j-1].blue                              + imagem->pixels[i+1][j+1].blue);
            if (somablue<0){
                fourier.pixels[i][j].blue = 0;
            }
            else if (somablue>255){
                fourier.pixels[i][j].blue = 255;
            }
            else{
                fourier.pixels[i][j].blue = somablue;
            }//BLUE

        }
    }
    return fourier;  

}

Image relevo(Image *imagem){

    /* Função para destacar o relevo da imagem 
    Filtro aplicado : [-2,-1,0; -1,1,1; 0,1,2]*/

    Image relevo;

    for(int i=0; i<3; i++){
        relevo.identificador[i] = imagem->identificador[i];
    }

    relevo.linha = imagem->linha;
    relevo.coluna = imagem->coluna;
    relevo.maximo = imagem->maximo;

    relevo.pixels = calloc(relevo.linha,sizeof(Pixel *));
    for(int i =0; i<relevo.linha; i++){
        relevo.pixels[i] = calloc(relevo.coluna,sizeof(Pixel));
    }

    for (int i=1; i<relevo.linha-1; i++){
        for (int j=1; j<relevo.coluna-1; j++){
            int somared=0, somagreen=0, somablue=0;
            somared = (-2*imagem->pixels[i-1][j-1].red - imagem->pixels[i-1][j].red
                    - imagem->pixels[i][j-1].red + imagem->pixels[i][j].red + imagem->pixels[i][j+1].red
                                        + imagem->pixels[i+1][j].red + 2*imagem->pixels[i+1][j+1].red);
            if (somared<0){
                relevo.pixels[i][j].red = 0;
            }
            else if (somared>255){
                relevo.pixels[i][j].red = 255;
            }
            else{
                relevo.pixels[i][j].red = somared;
            }//RED




            somagreen = (-2*imagem->pixels[i-1][j-1].green - imagem->pixels[i-1][j].green
            - imagem->pixels[i][j-1].green + imagem->pixels[i][j].green + imagem->pixels[i][j+1].green
                                        + imagem->pixels[i+1][j].green + 2*imagem->pixels[i+1][j+1].green);
            if (somagreen<0){
                relevo.pixels[i][j].green = 0;
            }
            else if (somagreen>255){
                relevo.pixels[i][j].green = 255;
            }
            else{
                relevo.pixels[i][j].green = somagreen;
            }//GREEN




            somablue = (-2*imagem->pixels[i-1][j-1].blue - imagem->pixels[i-1][j].blue
            - imagem->pixels[i][j-1].blue + imagem->pixels[i][j].blue + imagem->pixels[i][j+1].blue
                                        + imagem->pixels[i+1][j].blue + 2*imagem->pixels[i+1][j+1].blue);
            if (somablue<0){
                relevo.pixels[i][j].blue = 0;
            }
            else if (somablue>255){
                relevo.pixels[i][j].blue = 255;
            }
            else{
                relevo.pixels[i][j].blue = somablue;
            }//BLUE

       
        }
    }
    return relevo;  

}