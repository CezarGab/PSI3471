// pers.cpp grad-2018
#include <cekeikon.h>
int main()
{
    // Coordenadas do tabuleiro, obtidas pelo Paint:
    Mat_<FLT> src = (Mat_<FLT>(4, 2) << 
                    139, 45, 
                    323, 34,
                    108, 294,
                    353, 294
                     );
    
    // Coordenadas do novo posicionamento de perspectiva. 
    // Alinhou-se verticalmente os dois pontos superiores aos dois inf.:
    Mat_<FLT> dst = (Mat_<FLT>(4, 2) << 
                    108, 34,
                    353, 34,
                    108, 294,
                    353, 294);

    Mat_<double> m = getPerspectiveTransform(src, dst);
    cout << m << endl;
    // Verifica se a transformacao esta fazendo o que queremos
    Mat_<double> v = (Mat_<double>(3, 1) << -22, 479, 1);
    Mat_<double> w = m * v;
    cout << w << endl;
    cout << w(0) / w(2) << " " << w(1) / w(2) << endl;
    // Corrige a perspectiva
    Mat_<COR> a;
    le(a, "calib_result.jpg");
    Mat_<COR> b;
    warpPerspective(a, b, m, a.size());
    imp(b, "perspectivaCorrigida.jpg");
}