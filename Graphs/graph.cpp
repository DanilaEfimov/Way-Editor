#include "graph.h"

static QString data;

QString &Graph::toVL() const
{
    data = "";
    QTextStream ts(&data);
    ts << Parser::graphType(this) << '\n';
    ts << this->V << '\n';
    if(this->empty()){return data;}
    for(auto l : this->conectLists){
        for(auto v : l.second){
            ts << v << ' ';
        }
        ts << '\n';
    }
    return data;
}

QString &Graph::toEL() const
{
    data = "";
    QTextStream ts(&data);
    ts << Parser::graphType(this) << '\n';
    if(this->empty()){return data;}
    for(auto l : this->conectLists){
        for(auto v : l.second){
            ts << l.first << ' ' << v << '\n';
        }
    }
    return data;
}

QString &Graph::toMat() const
{
    data = "";
    QTextStream ts(&data);
    size_t v = (this->conectLists.end()--)->first; // max index vertex
    ts << Parser::graphType(this) << '\n';
    ts << this->V << '\n';

    if(this->empty()){return data;}
    for(size_t i = 1; i <= v; i++){
        for(size_t j = 1; j <= v; j++){
            if(this->isConected(i, j)){
                ts << "1 ";
            }
            else{
                ts << "0 ";
            }
        }
        ts << '\n';
    }
    return data;
    // There is one nuance here:
    // if some index don't exist, it will
    // be writen like an empty vertex, unconnected
    // zeros in matrix
    // recomended to save unsepareted vertities indexes graphs
}

Graph::~Graph()
{

}

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

bool Graph::empty() const
{
    return this->V == 0;
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
