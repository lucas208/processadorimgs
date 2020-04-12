#include <stdlib.h>
#include <stdio.h>
#include "ioimage.h"
#include "transformacoes.h"

Image ampliar(int amp, Image *imagem)
{
    Image ampliada;

    for (int i = 0; i < 3; i++)
    {
        ampliada.identificador[i] = imagem->identificador[i];
    }

    ampliada.maximo = imagem->maximo;

    ampliada.coluna = amp * imagem->coluna;

    ampliada.linha = amp * imagem->linha;

    ampliada.pixels = calloc(ampliada.linha, sizeof(Pixel *));
    for (int i = 0; i < ampliada.linha; i++)
    {
        ampliada.pixels[i] = calloc(ampliada.coluna, sizeof(Pixel));
    }

    for (int i = 0; i < imagem->linha; i++)
    {
        for (int j = 0; j < imagem->coluna; j++)
        {

            for (int k = 0; k < amp; k++)
            {
                for (int l = 0; l < amp; l++)
                {
                    ampliada.pixels[i * amp + k][j * amp + l] = imagem->pixels[i][j];
                }
            }
        }
    }

    return ampliada;
}
/*
Na função acima recebemos o fator de ampliação e já fazemos as alterações necessárias na variável do tipo Image
que vai receber a cópia da imagem após a alteração, além de alocar o espaço necessário.
Em seguida, vamos percorrendo a imagem menor e a cada pixel dela o jogamos na ampliada de acordo com o fator de
ampliação que foi passado como parâmetro, isso é feito através de 4 'fors' aninhados.
*/

Image reduzir(int red, Image *imagem)
{
    Image reduzida;
    int somared, somagreen, somablue;
    int fator = red * red;

    for (int i = 0; i < 3; i++)
    {
        reduzida.identificador[i] = imagem->identificador[i];
    }

    reduzida.maximo = imagem->maximo;

    reduzida.coluna = imagem->coluna / red;

    reduzida.linha = imagem->linha / red;

    reduzida.pixels = calloc(reduzida.linha, sizeof(Pixel *));
    for (int i = 0; i < reduzida.linha; i++)
    {
        reduzida.pixels[i] = calloc(reduzida.coluna, sizeof(Pixel));
    }

    for (int i = 0; i < reduzida.linha; i++)
    {
        for (int j = 0; j < reduzida.coluna; j++)
        {
            somared = 0;
            somagreen = 0;
            somablue = 0;

            for (int k = 0; k < red; k++)
            {
                for (int l = 0; l < red; l++)
                {
                    Pixel p = imagem->pixels[i * red + k][j * red + l];
                    somared += p.red;
                    somagreen += p.green;
                    somablue += p.blue;
                }
            }

            reduzida.pixels[i][j].red = somared / fator;
            reduzida.pixels[i][j].green = somagreen / fator;
            reduzida.pixels[i][j].blue = somablue / fator;
        }
    }

    return reduzida;
}

/*
Na função acima utilizamos a mesma lógica da função anterior só que "inversamente"
vamos percorrendo cada pixel da imagem reduzida e vamos preenchendo com a média dos pixels
adjacentes que serão suprimidos ao considerar o fator de redução. A variável fator é utilizada
para armazenar red², red*red, pois para tirar a média e atribuir ao pixel da imagem reduzida, percorremos na 
imagem normal o valor equivalente a red², se for 2, percorremos 4, se for 3, 9, e assim por diante, pela própria
forma que opera a transformação.
*/

Image rotacionar(int rot, Image *imagem)
{
    Image rotacionada;

    for (int i = 0; i < 3; i++)
    {
        rotacionada.identificador[i] = imagem->identificador[i];
    }

    rotacionada.maximo = imagem->maximo;

    rotacionada.linha = imagem->coluna;

    rotacionada.coluna = imagem->linha;

    rotacionada.pixels = calloc(rotacionada.linha, sizeof(Pixel *));
    for (int i = 0; i < rotacionada.linha; i++)
    {
        rotacionada.pixels[i] = calloc(rotacionada.coluna, sizeof(Pixel));
    }

    for (int i = 0; i < imagem->coluna; i++)
    {
        for (int j = 0; j < imagem->linha; j++)
        {
            //aqui usei um algoritmo de transformação linear para rotacionar a imagem para a esquerda
            rotacionada.pixels[imagem->coluna - i - 1][j] = imagem->pixels[j][i];
        }
    }

    if (rot == 0)
    {
        return rotacionada;
    }else{
        return rotacionar(rot - 1, &rotacionada);
    }
  
}
/*
A função acima funciona de maneira semelhante as anteriores, com a diferença que trocamos linhas por colunas
entre a imagem original e a rotacionada, para aplicar a rotação usamos dois 'for' para percorrer a imagem original
e aplicar a transformação linear de rotação para a esquerda para cada pixel da matriz rotacionada.
Como queríamos fazer 3 tipos de rotação 90º esquerda, 90º direita e 180º, usamos recursividade para efetuar a 
rotação para a esquerda mais de uma vez e assim obter o resultado desejado, pois rotacionar 180 graus equivale
a girar para a esquerda duas vezes e rotacionar para a direita equivale a rotacionar para a esquerda 3 vezes.
Dessa forma, basta implementar um contador que podemos passar como parâmetro na chamada e definir a lógica recursiva
se não for 0, esse contador é decrementado e chamamos a função novamente para realizar a rotação mais uma vez.
rot 2 equivale a rotação para direita = 3 rotações para a esquerda
 rot 1 equivale a 180 graus = 2 rotações para a esquerda
*/


Image negativar(Image *imagem){

    /* Esta função inverte as cores da imagem. Cada pixel recebe o valor 
    do seu complemento, até o valor máximo que ele pode assumir, 
    ou seja, o valor do pixel assume o valor máximo (255) 
    subtraído do seu valor original. 255 - valor do pixel original*/
   
    Image negative;

    for(int i=0; i<3; i++){
        negative.identificador[i] = imagem->identificador[i];
    }

    negative.linha = imagem->linha;
    negative.coluna = imagem->coluna;
    negative.maximo = imagem->maximo;

    negative.pixels = calloc(negative.linha,sizeof(Pixel *));
    for(int i =0; i<negative.linha; i++){
        negative.pixels[i] = calloc(negative.coluna,sizeof(Pixel));
        for (int j=0; j<negative.coluna; j++){
         
            negative.pixels[i][j].red = 255 - imagem->pixels[i][j].red;
            negative.pixels[i][j].green = 255 - imagem->pixels[i][j].green;
            negative.pixels[i][j].blue = 255 - imagem->pixels[i][j].blue;
        }
    }
    return negative;
}

Image binarizar(Image *imagem){

    /* Essa função converte os valores dos pixels para branco ou preto.
    A verificação do if no segundo for é feita comparando o valor da
    soma dos 3 pixels(R, G e B), com o pixel médio para binarizar seu valor.
    O número 384 é obtido através da expressão (256/2*3). 256/2 é o pixel médio
    e a multiplicação por 3 é devido aos 3 pixels do RGB. */
   
    Image binariza;

    for(int i=0; i<3; i++){
        binariza.identificador[i] = imagem->identificador[i];
    }

    binariza.linha = imagem->linha;
    binariza.coluna = imagem->coluna;
    binariza.maximo = imagem->maximo;

    binariza.pixels = calloc(binariza.linha,sizeof(Pixel *));
    for(int i =0; i<binariza.linha; i++){
        binariza.pixels[i] = calloc(binariza.coluna,sizeof(Pixel));
        for (int j=0; j<binariza.coluna; j++){
           
            if ((imagem->pixels[i][j].red + imagem->pixels[i][j].green + imagem->pixels[i][j].blue > 384)){
                binariza.pixels[i][j].red = 255;
                binariza.pixels[i][j].green = 255;
                binariza.pixels[i][j].blue = 255;
            }
            else {
                binariza.pixels[i][j].red = 0;
                binariza.pixels[i][j].green = 0;
                binariza.pixels[i][j].blue = 0;
            }

        }
    }
    return binariza;
}