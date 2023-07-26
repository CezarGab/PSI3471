// EP1 - 2023
// Cezar Gabriel M. A. Lima - 11806980
#include <cekeikon.h>
#include <cstdio>
#include <cmath>

Point3d findCenterAndOrientation(Mat_<GRY> src) {
 Moments m = moments(src, true);
 double cen_x = (m.m10/m.m00);
 double cen_y = (m.m01/m.m00);
 double theta = 0.5 * atan2( 2*m.mu11, m.mu20-m.mu02);
 return Point3d(cen_x, cen_y, theta);
}

int main(int argc, char** argv){
    // argc = qtd. de argumentos passados; argv = vetor de argumentos
    printf("Parametros: %d\n", argc);

     for (int i=1; i<argc; i++){
        printf("Lendo: %s\n",argv[i]);

        // 1) Leitura de imagem e encontro de orientacao e centro
        Mat_<GRY> a; le(a, argv[i]); // a sera' a versao binaria da imagem (para que certas funcoes funcionem)
        Mat_<COR> q; le(q, argv[i]); // q sera' a versao colorida da imagem

        threshold(a, a, 128, 255, cv::THRESH_BINARY); // Binariza a

        Point3d p=findCenterAndOrientation(a); // encontra a orientacao de a

        // Conversoes para inteiro do centro da imagem:
        int p_x = static_cast<int>(p.x);
        int p_y = static_cast<int>(p.y);

        printf("Centro do objeto: (%f, %f) | Rotacao (rad): %f\n",p.x,p.y,p.z);

        // 2) Plots: linha e circulo que indicam o centro e a rotacao do objeto
        // - Linha: 
        int raio = 2; int espessura = 2; int comprimento_linha = 100;

        int x_inicial = p_x + comprimento_linha*cos(p.z); int y_inicial = p_y + comprimento_linha*sin(p.z);
        int x_final = p_x - comprimento_linha*cos(p.z); int y_final = p_y - comprimento_linha*sin(p.z);

        //line(q, Point(x_inicial, y_inicial), Point(x_final, y_final), Scalar(35, 22, 164), espessura);

        // - Circulo
                                             // cor laranja
        //circle(q, Point(p_x, p_y), raio, Scalar(0, 151, 248), espessura);

        //imp(q, "aComCentroELinha.png");
        //mostra(q);

        // 3) Rotacao e centralizacao de imagens
        Mat_<GRY> aRotETransl; Mat_<COR> qRotETransl;

        // Criando a matriz de rotacao
        double angulo = round(p.z * 180.0 / M_PI);
        Mat_<double> matrizRotacaoETranslacao=getRotationMatrix2D(Point2f(a.cols/2,a.rows/2), angulo, 1);

        // Adicionado translacao 'a matriz:
        matrizRotacaoETranslacao.at<float>(0, 2) = a.cols/2 - p_x; matrizRotacaoETranslacao.at<float>(1, 2) = a.rows / 2 - p_y;

        //warpAffine(a, aRotacionado, matrizRotacaoETranslacao, a.size(), INTER_LINEAR, BORDER_REPLICATE, Scalar(255));
        warpAffine(q, qRotETransl, matrizRotacaoETranslacao, q.size(), INTER_LINEAR, BORDER_REPLICATE, Scalar(255));

        // 4) Salvando o resultado:
        string arquivoPng = semSufixo(argv[i]);
        arquivoPng = addPrefix(arquivoPng, ".png");
        imp(qRotETransl, arquivoPng);
    }
}