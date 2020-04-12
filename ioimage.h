#ifndef IOIMAGE_H
#define IOIMAGE_H
//(Pensada para conter funcionalidades relacionadas a entrada/saída na manipulação de imagens)
typedef struct
{
    unsigned char red, green, blue;
} Pixel;

typedef struct
{
    char identificador[3];
    int coluna;
    int linha;
    int maximo;
    Pixel **pixels;
} Image;

Image readImage(char* nome);
void desalocaImage(Image *imagem);
void writeImage(char* nome, Image *imagem);


#endif

/*
Essa biblioteca contém os dois tipos estruturados utilizados, o tipo Pixel
e o tipo Image. O tipo Pixel é formado por 3 variáveis do tipo unsigned char
que armazenam informação sobre cada componente do pixel (vermelho,verde,amarelo).
Já o tipo Image foi criado para armazenar as informações da leitura de um arquivo
de imagem do tipo PPM e possui 4 atributos, são eles:
	uma string para armazenar o identificador do arquivo ("P3")
	um inteiro para armazenar o número de colunas da imagem
	um inteiro para armazenar o número de linhas da imagem
	outro inteiro para armazenar o valor máximo de cada componente do pixel
	uma matriz de to tipo Pixel para armazenar informação sobre todos os pixels da imagem

Criar o tipo imagem e o tipo pixel facilita o fluxo do programa porque podemos
gerar uma variável do tipo Image que pode ser passada sem problemas para as funções
específicas que trabalham com esse tipo e assim as modificações são feitas. No final
podemos gravar essa variável num outro arquivo ppm ou modificar a imagem lida. 
Optamos por sempre criar um arquivo extra para se quisermos fazer mais de uma operação com a imagem de entrada.

Além dos tipos, a biblioteca possui três funções:
	Image readImage(char* nome);
	void desalocaImage(Image *imagem);
	void writeImage(char* nome, Image *imagem);

A primeira é utilizada para ler determinado arquivo ppm, recebendo seu nome e retornando uma variável do tipo Image
A segunda é utilizada para desalocar a matriz de pixel de uma imagem lida recebendo uma variável do tipo Image(passada por referência),
no caso de não precisarmos mais dela. Já a terceira cria um arquivo que "materializa" a variável do tipo Image num arquivo ppm, e logo
em seguida chama a segunda para desalocar a matriz da imagem passada por referência. A passagem por referência foi utilizada para economizar
recursos de processamento e memória.

*/