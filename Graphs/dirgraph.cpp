#include "dirgraph.h"

DirGraph::DirGraph() : Graph()
{}

DirGraph::DirGraph(int V, bool **mat)
{

}

DirGraph::DirGraph(const edge_list &el)
{

}

DirGraph::DirGraph(const adj_list &vl)
{

}

DirGraph::~DirGraph()
{

}

void DirGraph::addV(const std::set<int> &list)
{

}

void DirGraph::addE(int from, int to)
{

}

void DirGraph::eraseV(int v)
{

}

void DirGraph::eraseE(int from, int to)
{

}

int DirGraph::type() const
{
    return graphTypes::dirgraph;
}

const QString &DirGraph::show() const
{
    static QString graph;
    graph = "DirGraph\n";
    for(int i = 0; i < this->V; i++){
        QString curV = QString::fromStdString(std::to_string(i+1));
        graph += curV + ": ";
        std::set<int> list = this->conectLists.at(i+1);
        for(int j = 0; j < list.size(); j++){
            graph += QString::fromStdString(std::to_string(j+1));
            if(j != list.size()){
                graph += ", ";
            }
        }
        graph += '\n';
    }
    return graph;
}
