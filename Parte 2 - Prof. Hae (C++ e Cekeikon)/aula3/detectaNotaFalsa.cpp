// nn_cv2.cpp
#include <cekeikon.h>
int main()
{
    Mat_<float> ax;
    le(ax, "ax.txt");
    Mat_<float> ay;
    le(ay, "ay.txt");
    Mat_<float> qx;
    le(qx, "qx.txt");
    Mat_<float> qy;
    le(qy, "qy.txt");
    Mat_<float> qp;
    CvKNearest ind(ax, ay, Mat(), false, 1);
    ind.find_nearest(qx, 1, &qp);
    int erros = 0;
    for (int i = 0; i < qp.rows; i++)
        if (qp(i) != qy(i))
            erros++;
    printf("Erros=%d/%d. Pct=%1.3f%%\n", erros, qp.rows, 100.0 * erros / qp.rows);
}