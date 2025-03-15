#ifndef PARSER_H
#define PARSER_H

#include "precompiled.h"

#include <QKeyEvent>

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

    // COMMAND PARSER
    static QString& lastLine(const QTextEdit* textEdit);
    static int op(QString& argv);
    static int argc(int command);
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
    static const edge_list& readEdgeList(const  QString& file);
    static const adj_list& readAdjectList(const QString& file);

    static Graph* initGraph(fileTypes fileType, QString& file);
};

#endif // PARSER_H
