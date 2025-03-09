#include "graph.h"

void Graph::addV(const std::set<int> &list)
{
    this->V++;
    for(auto& v : list){
        if(v > 0 && v < this->V){
            this->conectLists[this->V].insert(v);
            this->E++;
        }
    }
}

void Graph::addE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end()){
        this->conectLists[from].erase(to);
        this->E--;
    }
}

void Graph::eraseV(int v)
{
    if(v > 0 && v <= this->V &&
        this->conectLists.find(v) != this->conectLists.end()){
        for(auto c : this->conectLists[v]){
            if(this->isConected(c, v)){
                this->eraseE(c, v);
            }
            if(this->isConected(v,c)){
                this->eraseE(v,c);
            }
        }
        this->conectLists.erase(v);
    }
}

void Graph::eraseE(int from, int to)
{
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end()){
        if(this->conectLists[from].find(to) != this->conectLists[from].end()){
            this->conectLists[from].erase(to);
            this->E--;
        }
    }
}

int Graph::getDegree(int v) const
{
    if(this->conectLists.find(v) != this->conectLists.end()){
        return this->conectLists.at(v).size();
    }
    return -1;
}

int Graph::getV() const
{
    return this->V;
}

int Graph::getE() const
{
    return this->E;
}

bool Graph::isConected(int from, int to) const
{
    if(this->conectLists.find(from) != this->conectLists.end()){
        std::set<int> list = this->conectLists.at(from);
        return list.find(to) != list.end();
    }
    return false;
}
