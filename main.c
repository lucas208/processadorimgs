#include <stdlib.h>
#include <stdio.h>
#include "ioimage.h"
#include "filtros.h"
#include "transformacoes.h"

/*
Aqui no main importamos todas as bibliotecas necessárias para trabalhar com as imagens e implementamos
uma espécie de menu que permite ao usuário selecionar a opção desejavada e realizar várias operações
com a mesma imagem, ao final do programa, desalocamos a matriz de pixels da imagem lida.
Como podemos encontrar uma característica única que define cada opção, a lógica para a seleção delas
inclui essa especificidade na ordem em que funciona corretamente, alguma espécie de validação foi feita ao ler determinada opção digitada
pelo usuário e assim seguir com o fluxo correto do programa, mostrando mensagens sobre opções inexistentes
ou não cadastradas.
*/

int main()
{
    char opcao[4];
    char nome[30];
    char modificado[30];
    Image imagem;
    int cont;

    printf("Insira o nome do arquivo .ppm a ser trabalhado\n");
    fflush(stdin);
    scanf("%s", nome);
    imagem = readImage(nome);

    while (opcao[0] != 'n'){
        cont = 0;
        printf("\n");
        printf("O que deseja fazer com a imagem?\n");
        printf("amp - para ampliar\n");
        printf("red - para reduzir\n");
        printf("rot - para rotacionar\n");
        printf("gra - para escala de cinza\n");
        printf("blu - para blurring\n");
        printf("sha - para sharpening\n");
        printf("bor - para detecção de bordas\n");
        printf("neg - para negativo\n");//MODIFICAÇÃO
        printf("bin - para binarização\n");//MODIFICAÇÃO
        printf("rel - para auto-relevo\n");//MODIFICAÇÃO
        printf("fou - para fourier\n");//MODIFICAÇÃO
        printf("n - para encerrar o programa\n");
        fflush(stdin);
        scanf("%s", opcao);

        if(opcao[0]=='a' || opcao[0]=='A'){
            int amp;
            printf("Insira o fator de ampliação (2,3,4...)\n");
            fflush(stdin);
            scanf("%d", &amp);
            Image ampliada = ampliar(amp, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &ampliada);
        }else if (opcao[2]=='l' || opcao[2]=='L'){
            Image relevada = relevo(&imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &relevada);     
        }else if (opcao[1]=='i' || opcao[1]=='I'){
            Image binarizada = binarizar(&imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &binarizada);    
        }else if (opcao[2]=='g' || opcao[2]=='G'){
            Image negativada = negativar(&imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &negativada);    
        }else if(opcao[1]=='e' || opcao[1]=='E' ){
            int red;
            printf("Insira o fator de redução (2,3,4...)\n");
            fflush(stdin);
            scanf("%d", &red);
            Image reduzida = reduzir(red, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &reduzida);
        }else if(opcao[2]=='t' || opcao[2]=='T'){
            int rot;
            char dir = '0';
            printf("Selecione o ângulo de rotação (90 ou 180)\n");
            fflush(stdin);
            scanf("%d", &rot);
            while(rot != 90 && rot != 180){
                printf("Opção não cadastrada, tente novamente!\n");
                fflush(stdin);
                scanf("%d", &rot);
            }
            if(rot == 90){
                printf("Direita ou esquerda? (d/e)\n");
                fflush(stdin);
                scanf("\n%c", &dir);
                while(dir != 'd' && dir != 'D' && dir != 'e' && dir != 'E'){
                    printf("Opção não cadastrada, tente novamente!\n");
                    fflush(stdin);
                    scanf("\n%c", &dir);
                }
            }
            if(dir == 'e' || dir == 'E'){
                rot = 0;
            }else if(dir == 'd' || dir == 'D'){
                rot = 2;
            }else{
                rot = 1;
            }
            Image rotacionada = rotacionar(rot, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &rotacionada);
        }else if(opcao[0]=='g' || opcao[0]=='G' ){
            Image filtrada = filtrar(0, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &filtrada);
        }else if(opcao[1]=='l' || opcao[1]=='L' ){
            Image filtrada = filtrar(1, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &filtrada);
        }else if(opcao[0]=='s' || opcao[0]=='S' ){
            Image filtrada = filtrar(2, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &filtrada);
        }else if(opcao[2]=='r' || opcao[2]=='R' ){
            int mod;
            printf("Selecione a o modelo de detecção de borda (1,2 ou 3)\n");
            fflush(stdin);
            scanf("%d", &mod);
            while(mod < 1 || mod > 3){
                printf("Opção não cadastrada, tente novamente!\n");
                fflush(stdin);
                scanf("%d", &mod);
            }
            mod +=2 ;
            Image filtrada = filtrar(mod, &imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &filtrada);
        }else if (opcao[0]=='f' || opcao[0]=='F'){
            Image fourierzada = fourier(&imagem);
            printf("Insira o nome do arquivo .ppm a ser salvo\n");
            fflush(stdin);
            scanf("%s", modificado);
            writeImage(modificado, &fourierzada);           
        }else if(opcao[0]=='n' || opcao[0]=='N' ){
            break;
        }else{
            printf("\n");
            printf("A opção digitada não existe, tente novamente!\n");
            cont = 1;
        }
        if (cont == 0){
        printf("\n");
        printf("Deseja realizar outra operação usando a mesma imagem (s/n)?\n");
        fflush(stdin);
        scanf("%s", opcao);
        }
    }
    desalocaImage(&imagem);
}

/*
Referências:

https://www.vivaolinux.com.br/artigo/Manipulacao-de-imagens-no-formato-PPM?pagina=2
https://pt.stackoverflow.com/questions/136858/girar-imagem-ppm-em-90-graus-em-c
https://github.com/AndersonSantosMedeiros/Aplicador-de-filtros-em-imagens-PPM/blob/master/funcoes.c
https://docplayer.com.br/49128586-Processamento-de-imagem-convolucao-filtragem-no-dominio-da-frequencia-fourier-professora-sheila-caceres.html


*/
