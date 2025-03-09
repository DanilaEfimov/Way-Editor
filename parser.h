#ifndef PARSER_H
#define PARSER_H

#include "precompiled.h"

class GraphParser;

class Parser
{
protected:
    Parser();
public:
    static int getExtention(const QString& path);
    static const QString& getExctention(int code);
    static int getGraphType(const QString& line);
    static const QString& getGraphType(int code);
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

    static bool** readMat(const QString& file);
    static const edge_list& readEdgeList(const  QString& file);
    static const adj_list& readAdjectList(const QString& file);
};

#endif // PARSER_H
