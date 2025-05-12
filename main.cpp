#include "mainwindow.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}













/*
     * examples:
     * first (12 vertices) OK! (1 -> 12)
        mat[0][2] = 1;
        mat[0][8] = 1;
        mat[1][3] = 1;
        mat[2][5] = 1;
        mat[2][0] = 1;
        mat[3][6] = 1;
        mat[4][7] = 1;
        mat[5][8] = 1;
        mat[5][2] = 1;
        mat[6][9] = 1;
        mat[7][10] = 1;
        mat[8][11] = 1;
     * second OK! (1 -> 5) (1 -> 12)
        // Основной DAG
        mat[0][1] = 1;
        mat[0][6] = 1;
        mat[1][2] = 1;
        mat[2][3] = 1;
        mat[3][4] = 1;

        // Боковая ветка с циклом
        mat[2][5] = 1;
        mat[5][6] = 1;
        mat[6][2] = 1; // цикл: 2 → 5 → 6 → 2
        mat[6][4] = 1;

        // Ветка без цикла
        mat[3][7] = 1;
        mat[7][8] = 1;

        // Еще один локальный цикл
        mat[9][10] = 1;
        mat[10][9] = 1;

        // Последний узел связан односторонне
        mat[8][11] = 1;
    */
