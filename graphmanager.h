#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "precompiled.h"

#include <QTextEdit>

class GraphManager
{
private:
    GraphManager();

    static int zeroArgOp(int code, Graph* G);
    static int oneArgOp(int code, Graph* G, QString& argument);
    static int twoArgOp(int code, Graph* G, QString& argument);
    static int threeArgOp(int code, Graph* G, QString& argument);
    static int limitlessArgOp(int code, Graph* G, QString& argument);

    static bool isDirected(Graph* G);
    static bool isTree(Graph* G);
    static bool ifWeighted(Graph* G);

public:

    static QString answer;

    static int cast_op(int code, Graph* G, QString& arguments);

    static int cast_op0(QTextEdit* pad);
    static int cast_op1(Graph* G, QString& argv);
    static int cast_op2(Graph* G, QString& argv);
    static int cast_op3(Graph* G, QString& argv);
    static int cast_op4(Graph* G, QString& argv);
    static int cast_op6(Graph* G);
    static int cast_op7(Graph* G);
    static int cast_op8(Graph* G, QString& argv);
    static int cast_op9(Graph* G, QString& argv);
    static int cast_op10(Graph* G, QString& argv);
    static int cast_op11(Graph* G, QString& argv);
    static int cast_op12(Graph* G, QString& argv);

    static int calculate(QString& argv, Graph* G);
};

// ^^^ GraphManager / FileManager vvv

class FileManager
{
private:
    FileManager();
public:

    static bool isValidPath(const QString& path);
    static bool isExistingDir(const QString& path);
    static bool isExistingFile(const QString& path);

    static int createNewFile(const QString& path);
};

#endif // GRAPHMANAGER_H
