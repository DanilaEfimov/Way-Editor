#include "mainwindow.h"
#include "Graphs/dirgraph.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    size_t size = 5;
    std::srand(time(0));
    bool** mat = new bool*[size];
    for(size_t i = 0; i < size; i++){
        mat[i] = new bool[size];
        for(size_t j = 0; j < size; j++){
            mat[i][j] = rand() % 2;
        }
        qDebug() << '\n';
    };
    /*
     * examples:
     * default non inited fields = 0:
     * fisrt: V = 5
        mat[0][1] = 1; mat[0][4] = 1;
        mat[1][2] = 1;
        mat[2][3] = 1;
        mat[3][1] = 1;
        mat[4][3] = 1;
     * second: V =4
       mat[0][1] = 1; mat[0][2] = 1;
       mat[1][2] = 1;
       mat[2][3] = 1;
       mat[3][1] = 1;
    */
    DirGraph G(size, mat);
    scc b = G.Kosaraju();
    for(auto item : b){
        qDebug() << "component: ";
        for(int v : item){
            qDebug() << v << ' ';
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
