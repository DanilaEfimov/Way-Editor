#include "dirgraph.h"

DirGraph::DirGraph() : Graph()
{
    this->V = 0;
    this->E = 0;
    this->conectLists = {};
}

DirGraph::DirGraph(int V, bool **mat)
{
    this->V = V;
    this->E = 0;
    for(std::size_t i = 0; i < this->V; i++){
        for(std::size_t j = i + 1; j < this->V; j++){
            if(mat[i][j]){
                this->conectLists[i+1].insert(j+1);
                this->E++;
            }
        }
    }
}

DirGraph::DirGraph(const edge_list &el)
{
    this->V = 0;
    this->E = 0;
    for(auto& e : el){
        this->conectLists[e.first].insert(e.second);
        this->E++;
        if(e.first > this->V || e.second > this->V){
            this->V = std::max(e.first, e.second);
        }
    }
}

DirGraph::DirGraph(const adj_list &vl)
{

}

DirGraph::~DirGraph()
{

}

void DirGraph::addV(const std::set<int> &list)
{
    this->V++;
    this->conectLists[this->V] = {};
    for(auto& v : list){
        if(v > 0 && v < this->V){
            this->conectLists[this->V].insert(v);
            this->E++;
        }
    }
}

void DirGraph::addE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end() &&
        !this->isConected(from, to)){
        this->conectLists[from].insert(to);
        this->E++;
    }
}

void DirGraph::eraseV(int v)
{
    // have to bypass all connectivity list and decrement
    // all, what greater than deleted vertex - got it
}

void DirGraph::eraseE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end() &&
        this->isConected(from, to)){
        this->conectLists[from].erase(to);
        this->E--;
    }
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
