#include <cekeikon.h>

int main(){
    Mat_<FLT> a; le(a,"a.png");
    Mat_<FLT> q; le(q,"q.png"); // template do urso

    Mat_<FLT> q2=somaAbsDois(dcReject(q));
    Mat_<FLT> p2;

    p2=matchTemplateSame(a, q, CV_TM_CCOEFF_NORMED);
    imp(p2,"templateMatchingUrso.jpg");


    // Gravando retangulos na imagem original
    Mat_<COR> d; converte(a,d);
    for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
    if (p2(l,c)>=0.90 || p2(l,c)<= -0.9) 
    // Os ursos com as mesmas cores estarão no treshold alto. Por outro lado, os ursos
    // com cores invertidas, estarão no treshold mais baixo.
    rectangle(d,Point(c-1,l-1),Point(c+1,l+1),Scalar(0,0,255),6);
    imp(d,"ocorrencias-p.png");

}