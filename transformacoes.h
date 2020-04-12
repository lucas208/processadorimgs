#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H
//(Pensada para conter as funcionalidades relacionadas a mudanças "geométricas" na imagem)
Image ampliar(int amp, Image *imagem);
Image reduzir(int red, Image *imagem);
Image rotacionar(int rot, Image *imagem);
Image negativar(Image *imagem);
Image binarizar(Image *imagem);

#endif

/*
Todas as funções dessa biblioteca recebem como parâmetro uma Image passada por referência e um 
inteiro que referencia a mudança desejada, seja o fator de ampliação, redução ou ângulo de rotação
*/