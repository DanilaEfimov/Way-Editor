#include "mainwindow.h"
#include "Graphs/wdirgraph.h"

#include <QApplication>
#include <ctime>
#include <chrono>     // ✅ Добавьте это
#include <iostream>   // Для std::cout

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    /*
    size_t size = 350;
    bool** mat = new bool*[size];
    for (size_t i = 0; i < size; i++) {
        mat[i] = new bool[size];
        for (size_t j = 0; j < size; j++) {
            mat[i][j] = 1;//rand() % 2;
        }
    }

    WDirGraph G(size, mat);
    std::vector<int> nodeToSCC(size, 1);
    for(size_t i = 0; i < size; i++){
        nodeToSCC[i] = 1+rand()%1;
    }

    // ✅ Засекаем время до вызова Kosaraju
    auto start = std::chrono::high_resolution_clock::now();

    double cost = G.modifiedDejcstra(1, 35, nodeToSCC);

    // ✅ Засекаем время после
    auto end = std::chrono::high_resolution_clock::now();

    // ✅ Вычисляем разницу
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << G.DijkstraPathVertices(1, 2).size() << std::endl;

    // ✅ Выводим
    std::cout << "Kosaraju execution time: " << elapsed.count() << " ms" << std::endl;
    */
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
     * third (6 -> 2) (7 вершин) (пример для презентации)
        mat[0][1] = 1;
        mat[0][2] = 1;
        mat[2][0] = 1;
        mat[1][3] = 1;
        mat[2][3] = 1;
        mat[3][4] = 1;
        mat[3][5] = 1;
        mat[4][6] = 1;
        mat[6][4] = 1;
    */
