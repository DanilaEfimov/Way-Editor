#ifndef UDIRGRAPH_H
#define UDIRGRAPH_H

#include "graph.h"

typedef std::pair<int,int> edge;
typedef std::set<edge> edge_list;

class UDirGraph : public Graph
{
public:
    UDirGraph();
    UDirGraph(int V, bool** mat);
    UDirGraph(const edge_list& el);
    UDirGraph(const adj_list& vl);
    virtual ~UDirGraph();

    virtual void addV(const std::set<int>& list) override;
    virtual void addE(int from, int to) override;
    virtual void eraseV(int v) override;
    virtual void eraseE(int from, int to) override;

    virtual const QString& show() const override;
};

#endif // UDIRGRAPH_H
