#include "udirgraph.h"

UDirGraph::UDirGraph()
{
    this->V = 0;
    this->E = 0;
    this->conectLists = {};
}

UDirGraph::UDirGraph(int V, bool **mat)
{
    this->V = V;
    this->E = 0;
    for(std::size_t i = 0; i < this->V; i++){
        for(std::size_t j = 0; j < this->V; j++){
            if(mat[i][j]){
                this->conectLists[i+1].insert(j+1);
                this->E++;
            }
        }
    }
}

UDirGraph::UDirGraph(const edge_list &el)   // edge list
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

UDirGraph::UDirGraph(const adj_list &vl)
{
    this->conectLists = adj_list(vl);
    this->V = conectLists.size();
    this->E = 0;
    for(auto& list : conectLists){
        this->E += list.second.size();
    }
    this->E /= 2;
}

UDirGraph::~UDirGraph()
{

}

void UDirGraph::addV(const std::set<int> &list)
{
    this->V++;
    for(auto& v : list){
        if(v > 0 && v < this->V){
            this->conectLists[this->V].insert(v);
            this->conectLists[v].insert(this->V);
            this->E++;
        }
    }
}

void UDirGraph::addE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end() &&
        !this->isConected(from, to)){
        this->conectLists[from].insert(to);
        this->conectLists[to].insert(from);
        this->E++;
    }
}

void UDirGraph::eraseV(int v)
{
    if(v > 0 && v <= this->V){
        for(auto& c : this->conectLists[v]){
            if(this->isConected(v, c)){
                this->conectLists[v].erase(c);
                this->conectLists[c].erase(v);
                this->E--;
            }
        }
        this->conectLists.erase(v);
        this->V--;
    }
}

void UDirGraph::eraseE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end() &&
        this->isConected(from, to)){
        this->conectLists[from].erase(to);
        this->conectLists[to].erase(from);
        this->E--;
    }
}

int UDirGraph::type() const
{
    return graphTypes::udirgraph;
}

const QString &UDirGraph::show() const
{
    static QString graph;
    graph = "UDirGraph\n";
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

