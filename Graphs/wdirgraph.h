#ifndef WDIRGRAPH_H
#define WDIRGRAPH_H

#include "dirgraph.h"

#include <map>

typedef std::map<int, double> distances;
typedef std::map<edge, double> allDistances;
typedef std::vector<int> path;

enum w_modes {
    normalize = 1, randomize,
};

class WDirGraph : public DirGraph
{
protected:
    std::map<int, double> vWeights;
    std::map<edge, double> eWeights;

    void normalizeWeights(double val = 1.0f);
    void randomizeWeights();

public:
    WDirGraph();
    WDirGraph(int V, bool** mat);
    WDirGraph(const edge_list& el);
    WDirGraph(const adj_list& vl);
    virtual ~WDirGraph() override;

    WDirGraph& condensation(std::vector<int>& sccs);
    double modifiedDejcstra(int s, int t, std::vector<int>& nodeToSCC);
    distances& Dijkstra(int start);
    std::set<int> DijkstraPathVertices(int s, int t);
    double localDejcstra(int s, int t, std::vector<int>& nodeToSCC, int scc);
    double localDejcstra(int s, int t, std::set<int>& sccs, std::vector<int>& nodeToSCC);
    allDistances& FloydWarshall();

    virtual void addV(const std::set<int>& list) override;
    virtual void addE(int from, int to) override;
    virtual void eraseV(int v) override;
    virtual void eraseE(int from, int to) override;

    virtual void weight(int mode);
    virtual void setVWeight(int v, double val);
    virtual void setEWeight(int from, int to, double val);
    double getEW(int from, int to) const;
    double getVW(int v) const;

    virtual int type() const override;
    virtual const QString& show() const override;
};

#endif // WDIRGRAPH_H

/**/
