#include "dirgraph.h"

#include <stack>
#include <queue>

int DirGraph::unvisitedIn(std::set<int>& visited)
{
    for(size_t i = 1; i <= this->V; i++){
        if(visited.find(i) == visited.end()){
            return i;
        }
    }
    return 0;
}

void DirGraph::markedDFS(std::stack<int> &marks, std::set<int> &visited, int start)
{
    visited.insert(start);
    for(auto v : this->conectLists[start]){
        if(visited.find(v) == visited.end()){
            this->markedDFS(marks, visited, v);
        }
    }
    marks.push(start);
}

void DirGraph::reverseEdges()
{
    // Для начала создадим новый граф для перевёрнутых рёбер
    std::map<int, std::set<int>> newConectLists;

    // Проходим по всем вершинам и рёбрам исходного графа
    for (const auto& entry : this->conectLists) {
        int u = entry.first;  // вершина исходного графа
        const std::set<int>& neighbors = entry.second;  // соседи вершины u

        // Для каждого соседа добавляем рёберную связь в новый граф
        for (int v : neighbors) {
            newConectLists[v].insert(u);  // инвертируем рёбра
        }
    }

    for(size_t v = 1; v < this->V; v++){
        if(newConectLists.find(v) == newConectLists.end()){
            newConectLists[v] = {};
        }
    }

    // Теперь заменим старые рёбра на инвертированные
    this->conectLists = std::move(newConectLists);
}

void DirGraph::initSCC(std::set<int>& scc, std::set<int> &visited, int start)
{
    scc.insert(start);
    visited.insert(start);
    for(auto v : this->conectLists[start]){
        if(visited.find(v) == visited.end()){
            this->initSCC(scc, visited, v);
        }
    }
}

void DirGraph::tarjanDFS(int v, std::map<int, int> &indices,
                        std::map<int, int> &lowlink,
                        std::stack<int> &stack,
                        std::set<int> &onStack,
                        scc &sccs, int &index)
{
    // Присваиваем текущий индекс и низший индекс
    indices[v] = lowlink[v] = index++;
    stack.push(v);
    onStack.insert(v);

    // Проходим по всем соседям вершины v
    for (int w : conectLists[v]) {
        if (indices.find(w) == indices.end()) {
            // Если вершина ещё не посещена
            tarjanDFS(w, indices, lowlink, stack, onStack, sccs, index);
            lowlink[v] = std::min(lowlink[v], lowlink[w]);
        } else if (onStack.count(w)) {
            // Если вершина w в стеке, обновляем lowlink[v]
            lowlink[v] = std::min(lowlink[v], indices[w]);
        }
    }

    // Если v — это корень компоненты SCC
    if (lowlink[v] == indices[v]) {
        std::set<int> component; // Новая компонента
        int w;
        do {
            w = stack.top();
            stack.pop();
            onStack.erase(w);
            component.insert(w);
        } while (w != v);

        // Добавляем компоненту в множество
        sccs.insert(component);
    }
}

std::vector<int> DirGraph::topologicalSortKahn(const scc &sccs, const std::map<int, int> &nodeToComponent, DirGraph &G_)
{
    int numComponents = sccs.size();

    // counting degree of in-edges for every node
    std::vector<int> inDegree(numComponents, 0);

    for (int u = 0; u < numComponents; ++u) {
        for (int v : G_.conectLists[u]) {  // G_.adj[u] — соседи компоненты u
            inDegree[v]++;
        }
    }

    // zero in-degree component's queue
    std::queue<int> q;
    for (int i = 0; i < numComponents; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> result;

    // Khan's algorithm
    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.push_back(u);

        for (int v : G_.conectLists[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (result.size() != numComponents) {
        throw std::runtime_error("invalid argument (cond. graph 'G_')");
    }

    return result;
}

DirGraph::DirGraph() : Graph()
{
    this->V = 0;
    this->E = 0;
    this->conectLists = {};
}

DirGraph::DirGraph(int V, bool **mat = nullptr)
{
    this->V = V;
    this->E = 0;
    for(size_t i = 0; i < V; i++)
        this->conectLists[i+1] = {};
    if(!mat){
        return;
    }
    for(std::size_t i = 0; i < this->V; i++){
        for(std::size_t j = 0; j < this->V; j++){
            if(i == j){continue;}
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
    this->conectLists = adj_list(vl);
    this->V = conectLists.size();
    this->E = 0;
    for(auto& list : conectLists){
        this->E += list.second.size();
    }
}

DirGraph::~DirGraph() {}

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
    if(from == to){return;}
    if(this->conectLists.find(from) != this->conectLists.end() &&
        this->conectLists.find(to) != this->conectLists.end() &&
        !this->isConected(from, to)){
        this->conectLists[from].insert(to);
        this->E++;
    }
}

void DirGraph::eraseV(int v)
{
    for(auto& l : this->conectLists){
        for(auto& t : l.second){
            if(t == v){
                l.second.erase(v);
                this->E--;
                break;
            }
        }
    }
    this->conectLists.erase(v);
    this->V--;
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

scc &DirGraph::Kosaraju()
{
    static scc res = {};
    res = {};
    if(!this->V){return res;}
    // first step
    std::stack<int> marks;
    std::set<int> visited;
    while(visited.size() != this->V){
        int start = this->unvisitedIn(visited);
        this->markedDFS(marks, visited, start);
    }

    // second step
    this->reverseEdges();

    // third step
    std::set<int> item = {};
    visited = {};
    while(visited.size() != this->V){
        int start = marks.top();
        marks.pop();
        if(visited.find(start) != visited.end()){
            continue;
        }
        item = {};
        this->initSCC(item, visited, start);
        if(!item.empty()){
            res.insert(item);
        }
    }

    this->reverseEdges();
    return res;
}

scc &DirGraph::Tarjan()
{
    static scc sccs;  // Статическое множество компонент сильной связности
    sccs.clear();  // Очищаем перед запуском алгоритма

    std::map<int, int> indices;    // Временные метки для каждой вершины
    std::map<int, int> lowlink;    // Минимальные метки, достижимые из вершины
    std::stack<int> stack;         // Стек для DFS
    std::set<int> onStack;         // Смотрим, находимся ли в стеке

    int index = 0;  // Индекс для каждой вершины

    // Проходим по всем вершинам графа
    for (const auto& [v, _] : conectLists) {
        if (indices.find(v) == indices.end()) {
            tarjanDFS(v, indices, lowlink, stack, onStack, sccs, index);
        }
    }

    return sccs;  // Возвращаем ссылку на множество компонент
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
        std::set<int> list = this->conectLists.find(i+1)!=this->conectLists.end() ?
                                 this->conectLists.at(i+1) : std::set<int>{};
        for(auto j = list.begin(); j != list.end();){
            QString neighbour = QString::fromStdString((std::to_string(*j)));
            graph += neighbour;
            if(j++ != list.end()){
                graph += ", ";
            }
        }
        graph += '\n';
    }
    return graph;
}
