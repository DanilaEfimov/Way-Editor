#ifndef PARSER_H
#define PARSER_H

#include "precompiled.h"

#include <QKeyEvent>

struct argument {
    edge_list el;
    adj_list vl;
    std::set<int> list;
    edge e;
    int v;
};

class GraphParser;

class Parser
{
protected:
    Parser();
public:
    static bool isSpecialChar(int key);

    static int getFileType(const QString& path);
    static const QString& getExctention(int code);
    static int getGraphType(const QString& line);
    static const QString& getGraphType(int code);

    static int readVertexCount(QString& file);
    static QString graphType(const Graph* G);

    // COMMAND PARSER
    static QString& lastLine(const QTextEdit* textEdit);
    static int op(QString& argv);
    static QString& argv(QString& line);
    static int argc(int command);

    static argument VLfromArgv(QString& argv);
    static argument ELfromArgv(QString& argv);
    static argument EdgeFromArgv(QString& argv);
    static argument VfromArgv(QString& argv);
};

// ^^^ Parser / GraphParser vvv

class GraphParser
{
protected:
    GraphParser();

public:
    // Graph Object Generators for every file type
    static Graph* createGraph(int type);
    static Graph* createGraph(int type, int V, bool** mat);
    static Graph* createGraph(int type, const edge_list& el);
    static Graph* createGraph(int type, const adj_list& vl);

    static bool** readMat(QString& file);
    static const edge_list& readEdgeList(QString& file);
    static const adj_list& readAdjectList(QString& file);

    static QString& toStr(Graph* G, fileTypes filetype);

    static Graph* initGraph(fileTypes fileType, QString& file);
};

#endif // PARSER_H
