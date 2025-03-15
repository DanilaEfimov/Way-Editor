#ifndef DIRGRAPH_H
#define DIRGRAPH_H

#include "graph.h"

class DirGraph : public Graph
{
public:
    DirGraph();
    DirGraph(int V, bool** mat);
    DirGraph(const edge_list& el);
    DirGraph(const adj_list& vl);
    virtual ~DirGraph();

    virtual void addV(const std::set<int>& list) override;
    virtual void addE(int from, int to) override;
    virtual void eraseV(int v) override;
    virtual void eraseE(int from, int to) override;

    virtual int type() const override;

    virtual const QString& show() const override;
};

#endif // DIRGRAPH_H
