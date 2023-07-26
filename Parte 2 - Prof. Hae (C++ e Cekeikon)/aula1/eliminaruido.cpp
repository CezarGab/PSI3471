#include <cekeikon.h>

int main(){
    Mat_<GRY> imagemMickey;
    le(imagemMickey, "mickey.bmp");

    Mat_<GRY> mickeyFiltrado(imagemMickey.rows, imagemMickey.cols);

    mickeyFiltrado = imagemMickey.clone();

    int pixelBranco = 255;
    int pixelPreto = 0;

    for (int l=0; l<imagemMickey.rows-1; l++){
        for (int c=0; c<imagemMickey.cols-1; c++){ 
            if (imagemMickey(l,c)==pixelBranco){
                if(
                    imagemMickey(l-1, c) == pixelPreto &&
                    imagemMickey(l+1, c) == pixelPreto &&
                    imagemMickey(l, c-1) == pixelPreto &&
                    imagemMickey(l, c+1) == pixelPreto
                ){
                    mickeyFiltrado(l, c) = pixelPreto;
                }
            }
        }
    }
    imp(mickeyFiltrado, "mickeyFiltrado.png");

}