#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "precompiled.h"

#include <QTextEdit>

class GraphManager
{
private:
    GraphManager();
public:

    static QString answer;

    static int cast_op0(QTextEdit* pad);
    static int cast_op1(Graph* G, std::set<int>& adj);
    static int cast_op2(Graph* G, int from, int to);
    static int cast_op3(Graph* G, int id);
    static int cast_op4(Graph* G, int from, int to);

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
