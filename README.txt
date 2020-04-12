Todas as funcionalidades básicas foram implementadas,
como funcionalidades extra escolhemos a implementação 
de alguns filtros e transformações. 
    
    Funções básicas:
        Tipos de dados necessários;
        Modularização do programa;
        Leitura e escrita de arquivos ppm;
        Escala de cinza;
        Ampliar, reduzir e rotacionar;
        Blurring e sharpening;
        Detecção de bordas;
        Implementação do menu do programa;

    Funções extras:
        Filtro de fourier;
        Aplicação de auto-relevo;
        Gerar negativo da imagem;
        "Binarizar" a imagem;

Não foi feita a implementação de uma interface gráfica
para o programa em virtude da dificuldade de instalação
e utilização das dependências e bibliotecas externas necessárias.
Para contornar esse fator, escolhemos alguns filtros e transformações
como funcionalidades extras. Outro recurso que poderia ter ser utilizado
é o makefile, para facilitar a compilação dos arquivos necessários, porém,
nos habituamos ao comando de compilação mais extenso e acabamos não implementando.

O que seria feito de maneira diferente é a implementação do 
menu do programa, que apresenta leitura um pouco confusa,
poderíamos ter criado uma outra biblioteca para evitar a repetição
do código e assim modularizar o nosso menu e deixá-lo mais legível.

Para compilar o projeto basta executar o seguinte comando (via terminal) em sua pasta de origem:

gcc main.c ioimage.c transformacoes.c filtros.c -o main

Não utilizamos bibliotecas externas além daquelas que criamos. Utilizamos também as bibliotecas nativas do c:
stdlib.h e stdio.h para trabalhar com leitura e escrita de arquivos, entrada e saída de dados.

Autores:

BRUNO ALYSSON DO AMARAL SOARES CARRILHO - Responsável pelas funcionalidades extras;
LUCAS OTÁVIO VIEIRA - Responsável pelas funcionalidades básicas;

