#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <QString>

typedef std::map<int, std::set<int>> adj_list;

class Graph
{
protected:
    int V;
    int E;

    adj_list conectLists;

    Graph() = default;

public:
    virtual ~Graph();

    virtual void addV(const std::set<int>& list);
    virtual void addE(int from, int to);
    virtual void eraseV(int v);
    virtual void eraseE(int from, int to);
    virtual int getDegree(int v) const;

    // ACCESSORS
    bool empty() const;
    int getV() const;
    int getE() const;
    bool isConected(int from, int to) const;

    QString& toVL() const;
    QString& toEL() const;
    QString& toMat() const;

    virtual int type() const = 0;
    virtual const QString& show() const = 0;

};

#endif // GRAPH_H
