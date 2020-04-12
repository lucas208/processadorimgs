#ifndef FILTROS_H
#define FILTROS_H
//(Pensada para agrupar as funcionalidades relacionadas a aplicação de filtros na imagem)
Image grayscale(Image *imagem);
Image filtrar(int op, Image *imagem);
Image fourier(Image *imagem);
Image relevo(Image *imagem);

#endif

/*
Essa biblioteca contém duas funções:
	Image grayscale(Image *imagem);
	Image filtrar(int op, Image *imagem);

A primeira função é responsável por receber uma variável do tipo Image passada por 
referência e retornar uma variável do tipo Image que contém uma cópia da primeira 
mas com a transformação em escala de cinza, feita ao atribuir a média dos componentes 
do pixel a todos os componentes do pixel correspondente na cópia.
Já a segunda função retorna uma variável do tipo Image, que é a cópia da imagem passada 
por referência como parâmetro de entrada, a cópia é a imagem original após a aplicação do filtro.
*/