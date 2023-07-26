// Segmentacao de area de Mapa com KDTree e Vizinho Mais Próximo
// Usa OpenCV2
// Cezar Gabriel e Lucas Lima Emerêncio
#include <cekeikon.h>

int main() {
     Mat_<GRY> ax; le(ax,"janei.pgm");
     Mat_<GRY> ay; le(ay,"janei-1.pgm");
     Mat_<GRY> qx; le(qx,"julho.pgm");

     if (ax.size()!=ay.size()) erro("Erro dimensao");

     Mat_<GRY> qp(qx.rows,qx.cols);
     //Cria as estruturas de dados para alimentar OpenCV
     Mat_<FLT> features(ax.rows*ax.cols,9);
     Mat_<FLT> saidas(ax.rows*ax.cols,1);

     int i=0;
     for (int l=0; l<ax.rows; l++)
         for (int c=0; c<ax.cols; c++) {
             features(i, 0)=ax(l,c); // >> salva o pixel das entradas
             features(i, 1)=ax(l+1,c); // >> salva o pixel das entradas
             features(i, 2)=ax(l-1,c); // >> salva o pixel das entradas
             features(i, 3)=ax(l,c+1); // >> salva o pixel das entradas
             features(i, 4)=ax(l,c-1); // >> salva o pixel das entradas
             features(i, 5)=ax(l-1,c-1); // >> salva o pixel das entradas
             features(i, 6)=ax(l-1,c+1); // >> salva o pixel das entradas
             features(i, 7)=ax(l+1,c+1); // >> salva o pixel das entradas
             features(i, 8)=ax(l+1,c-1); // >> salva o pixel das entradas
             
			 
             saidas(i)=ay(l,c); // >> salva o respectivo pixel da saida
             i=i+1;
     }

     flann::Index ind(features,flann::KDTreeIndexParams(4));
     // Aqui, as 4 arvores estao criadas

     Mat_<FLT> query(1,9);
     vector<int> indices(1);
     vector<FLT> dists(1);

     medianBlur(qx, qx, 1);
     for (int l=0; l<qp.rows; l++)
         for (int c=0; c<qp.cols; c++) {
             
			 query(0)=qx(l,c);
             query(1)=qx(l+1,c); 
             query(2)=qx(l-1,c); 
             query(3)=qx(l,c+1); 
             query(4)=qx(l,c-1); 
             query(5)=qx(l-1,c-1); 
             query(6)=qx(l-1,c+1); 
             query(7)=qx(l+1,c+1); 
             query(8)=qx(l+1,c-1);      
             
             // Zero indica sem backtracking

             ind.knnSearch(query,indices,dists,1,flann::SearchParams(0)); 
             // >> encontra a saida mais proxima baseada na entrada

             // Saida e' um numero entre 0 e 255
             qp(l,c)=saidas(indices[0]);
         }

     medianBlur(qp, qp, 7);

     imp(qp,"julho-p1.png");

     //mostra(ay);
     //mostra(qp);


     // Pintando o mapa:

     Mat_<COR> mapa;
     le(mapa, "julho.pgm");

     for(int i=0; i< mapa.rows; i++)
        for(int j=0; j< mapa.cols;j++){
            if(qp[i][j] == 0.0){
                mapa[i][j][2] = 255.0;
            }
     }
    
    imp(mapa, "mapaDestacado.png");
    mostra(qp);
}
