#ifndef DIRGRAPH_H
#define DIRGRAPH_H

#include "graph.h"

#include <stack>
#include <vector>

typedef std::pair<int,int> edge;
typedef std::set<edge> edge_list;
typedef std::set<std::set<int>> scc; // strongly connectyvity compoment

class DirGraph : public Graph
{
protected:
    int  unvisitedIn(std::set<int>& visited);
    void markedDFS(std::stack<int>& marks, std::set<int>& visited, int start);
    void reverseEdges();
    void initSCC(std::set<int>&scc, std::set<int>& visited, int start);

    void tarjanDFS(int v, std::map<int, int>& indices,
                std::map<int, int>& lowlink,
                std::stack<int>& stack,
                std::set<int>& onStack,
                scc& sccs,
                int& index);

    std::vector<int> topologicalSortKahn(const scc& sccs,
                                         const std::map<int, int>& nodeToComponent,
                                         DirGraph& G_);
public:
    DirGraph();
    DirGraph(int V, bool** mat);
    DirGraph(const edge_list& el);
    DirGraph(const adj_list& vl);
    virtual ~DirGraph() override;

    virtual void addV(const std::set<int>& list) override;
    virtual void addE(int from, int to) override;
    virtual void eraseV(int v) override;
    virtual void eraseE(int from, int to) override;

    scc& Kosaraju();
    scc& Tarjan();

    virtual int type() const override;
    virtual const QString& show() const override;
};

#endif // DIRGRAPH_H
