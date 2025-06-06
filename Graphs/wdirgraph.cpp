#include "wdirgraph.h"

#include <ctime>
#include <queue>
#include <math.h>

void WDirGraph::normalizeWeights(double val)
{
    if(val < 0){val -= val;}
    if(val == 0){val = 1.0f;}
    for(auto& v : this->conectLists){
        this->vWeights[v.first] = val;
        for(auto& l : v.second){
            edge e = edge(v.first, l);
            this->eWeights[e] = val;
        }
    }
}

void WDirGraph::randomizeWeights()
{
    int from = 1, to = 100;
    std::srand(time(NULL));
    for(auto& v : this->conectLists){
        this->vWeights[v.first] = float(from+ rand()%to);
        for(auto& l : v.second){
            edge e = edge(v.first, l);
            this->eWeights[e] = float(from + rand()%to);
        }
    }
}

WDirGraph::WDirGraph() : DirGraph()
{
    this->vWeights = {};
    this->eWeights = {};
    this->normalizeWeights(1);
}

WDirGraph::WDirGraph(int V, bool **mat = nullptr) : DirGraph(V, mat)
{
    this->vWeights = {};
    this->eWeights = {};
    this->normalizeWeights(1);
}

WDirGraph::WDirGraph(const edge_list &el) : DirGraph(el)
{
    this->vWeights = {};
    this->eWeights = {};
    this->normalizeWeights(1);
}

WDirGraph::WDirGraph(const adj_list &vl) : DirGraph(vl)
{
    this->vWeights = {};
    this->eWeights = {};
    this->normalizeWeights(1);
}

WDirGraph::~WDirGraph()
{
    this->DirGraph::~DirGraph();
}

WDirGraph& WDirGraph::condensation(std::vector<int> &sccs)
{
    // определение количества вершин в графе конденсации
    int size = 0;
    for(int v : sccs){
        if(v > size){
            size = v;
        }
    }
    static  WDirGraph G_(size, nullptr);    // граф с изолированными вершинами
    for(auto& l : this->conectLists){
        for(int v : l.second){
        // если есть связь между компонентами - зафиксировать это
            if(sccs[l.first-1] != sccs[v-1]){
                G_.addE(sccs[l.first-1], sccs[v-1]);
            }
        }
    }
    return G_; // все веса ребер нормализованы
}

#include <iostream>
double WDirGraph::modifiedDejcstra(int s, int t, std::vector<int>& nodeToSCC)
{
    // Алгоритм нахождения кратчайшего пути с учетом компонент сильной связности
    // Общая инициализация
    double cost = -1.0; // По умолчанию предполагаем отсутствие пути
    // Шаг 1: Проверка эквивалентности вершин
    if (nodeToSCC[s - 1] == nodeToSCC[t - 1]) {
        // Вершины эквивалентны, возвращаем результат локального поиска
        return this->localDejcstra(s, t, nodeToSCC, nodeToSCC[s - 1]);
    }
    // Шаг 2: Построение конденсации графа
    static WDirGraph GT = this->condensation(nodeToSCC);
    // Шаг 3: Нахождение пути в сконденсированном графе
    std::set<int> components = GT.DijkstraPathVertices(nodeToSCC[s - 1], nodeToSCC[t - 1]);
    // Шаг 4: Локальный поиск пути
    if (components.empty()) {
        // Пути не существует
        return cost;
    }
    // Рассчитываем путь внутри компоненты
    cost = this->localDejcstra(s, t, components, nodeToSCC);
    return cost;
}

distances &WDirGraph::Dijkstra(int start)
{
    static std::map<int, double> distances;
    std::set<int> visited;

    // initialize
    for (const auto& [node, _] : this->conectLists) {
        distances[node] = INFINITY;
    }
    distances[start] = 0.0;

    std::queue<std::pair<double, int>> pq;
    pq.emplace(0.0, start);

    // main loop
    while (!pq.empty()) {
        auto [currentDist, current] = pq.front();
        pq.pop();

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);

        for (int neighbor : this->conectLists.at(current)) {
            // measuring
            double edgeWeight = this->eWeights.at({current, neighbor});
            double newDist = currentDist + edgeWeight;

            // updating distances
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }

    return distances;
}

std::set<int> WDirGraph::DijkstraPathVertices(int start, int target)
{
    std::map<int, double> distances;
    std::map<int, int> parent;
    std::set<int> visited;

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    for (const auto& [node, _] : this->conectLists) {
        distances[node] = INFINITY;
    }
    distances[start] = 0.0;
    pq.emplace(0.0, start);

    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (current == target) break;

        for (int neighbor : this->conectLists.at(current)) {
            double edgeWeight = this->eWeights.at({current, neighbor});
            double newDist = currentDist + edgeWeight;

            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                parent[neighbor] = current;
                pq.emplace(newDist, neighbor);
            }
        }
    }

    // Восстановление пути
    std::set<int> pathVertices;
    int current = target;
    while (parent.find(current) != parent.end()) {
        pathVertices.insert(current);
        current = parent[current];
    }

    if (current == start) {
        pathVertices.insert(start);
    } else {
        pathVertices.clear(); // Путь не найден
    }

    return pathVertices;
}

double WDirGraph::localDejcstra(int s, int t, std::vector<int> &nodeToSCC, int scc)
{
    static std::map<int, double> distances;
    distances = {};
    std::set<int> visited = {};

    if(nodeToSCC[s-1] != scc || nodeToSCC[t-1] != scc){
        // некорректные входные данные
        // (вершины принадлежат разным компонентам сильной связности
        // или компонента не совпадает с указанной)
        // возвращаем некорекное значение (так как веса ребер только положительны)
        return -1.0;
    }

    // инициализация
    for (const auto& [node, _] : this->conectLists) {
        distances[node] = INFINITY;
    }
    distances[s] = 0.0;

    std::queue<std::pair<double, int>> pq;
    pq.emplace(0.0, s);

    // главный цикл
    while (!pq.empty()) {
        auto [currentDist, current] = pq.front();
        pq.pop();

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);
        if(nodeToSCC[current-1] != scc) continue; // игнорируем вершины из других компонент

        for (int neighbor : this->conectLists.at(current)) {
            if(nodeToSCC[neighbor-1] != scc) continue; // игнорируем вершины из других компонент

            // измерения и сравнения
            double edgeWeight = this->eWeights.at({current, neighbor});
            double newDist = currentDist + edgeWeight;

            // обновение выходных данных
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }

    return distances[t];
}

double WDirGraph::localDejcstra(int s, int t, std::set<int> &sccs, std::vector<int>& nodeToSCC)
{
    std::map<int, double> distances;
    std::set<int> visited;

    auto shouldIgnore = [&sccs, &nodeToSCC](int v) {
        int scc = nodeToSCC[v-1];
        return sccs.find(scc) == sccs.end(); // игнорируем, если v НЕ в sccs
    };

    // Инициализация
    for (const auto& [node, _] : this->conectLists) {
        distances[node] = INFINITY;
    }
    distances[s] = 0.0;

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.emplace(0.0, s);

    // Главный цикл
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        if (shouldIgnore(current)) continue;

        for (int neighbor : this->conectLists.at(current)) {
            if (shouldIgnore(neighbor)) continue;

            double edgeWeight = this->eWeights.at({current, neighbor});
            double newDist = currentDist + edgeWeight;

            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }

    return distances[t];
}

allDistances &WDirGraph::FloydWarshall()
{
    static std::map<std::pair<int,int>, double> dist = {};
    dist = {};

    // initialize dist
    for (const auto& [u, neighbors] : this->conectLists) {
        for (int v : neighbors) {
            dist[{u, v}] = this->eWeights.at({u, v});
        }
        dist[{u, u}] = 0.0;
    }

    // all vertices (like would 'visited' was done)
    std::set<int> nodes;
    for (const auto& [node, _] : this->conectLists) {
        nodes.insert(node);
    }

    // main looped looped loop
    for (int k : nodes) {
        for (int i : nodes) {
            for (int j : nodes) {
                edge ij = edge(i, j);
                edge ik = edge(i, k);
                edge kj = edge(k, j);

                double dik = dist.count(ik) ? dist[ik] : INFINITY;
                double dkj = dist.count(kj) ? dist[kj] : INFINITY;
                double dij = dist.count(ij) ? dist[ij] : INFINITY;

                if (dik + dkj < dij) {
                    dist[ij] = dik + dkj;
                }
            }
        }
    }

    return dist;
}

void WDirGraph::addV(const std::set<int> &list)
{
    this->DirGraph::addV(list);
    this->vWeights[this->V] = 1.0f;
}

void WDirGraph::addE(int from, int to)
{
    this->DirGraph::addE(from, to);
    edge e = edge(from, to);
    this->eWeights[e] = 1.0f;
}

void WDirGraph::eraseV(int v)
{
    if(this->conectLists.find(v) == this->conectLists.end()){
        return;
    }
    this->vWeights.erase(v);
    for(auto& l : this->conectLists[v]){
        edge e = edge(v, l);
        this->eWeights.erase(e);
    }
    this->DirGraph::eraseV(v);
}

void WDirGraph::eraseE(int from, int to)
{
    if(conectLists.find(from) == conectLists.end()){
        return;
    }
    if(this->conectLists[from].find(to) == this->conectLists[from].end()){
        return;
    }
    edge e = edge(from, to);
    this->eWeights.erase(e);
    this->conectLists[from].erase(to);
}

void WDirGraph::weight(int mode)
{
    switch(mode){
        case w_modes::normalize: this->normalizeWeights(1); break;
        case w_modes::randomize: this->randomizeWeights(); break;
    default:
        break;
    }
}

void WDirGraph::setVWeight(int v, double val)
{
    if(this->conectLists.find(v) == this->conectLists.end()){
        return;
    }
    if(val < 0){ val -= val;}
    if(val == 0){val = 1.0f;}
    this->vWeights[v] = val;
}

void WDirGraph::setEWeight(int from, int to, double val)
{
    if(conectLists.find(from) == conectLists.end()){
        return;
    }
    if(this->conectLists[from].find(to) == this->conectLists[from].end()){
        return;
    }
    edge e = edge(from, to);
    this->eWeights[e] = val;
}

double WDirGraph::getEW(int from, int to) const
{
    try{
        edge e(from, to);
        return this->eWeights.at(e);
    }
    catch(...){
        return INFINITY;
    }
}

double WDirGraph::getVW(int v) const
{
    try{
        return this->vWeights.at(v);
    }
    catch(...){
        return INFINITY;
    }
}

int WDirGraph::type() const
{
    return graphTypes::dweightedgraph;
}

const QString &WDirGraph::show() const
{
    static QString graph;
    graph = "WDirGraph\n";
    for(int i = 0; i < this->V; i++){
        QString curV = QString::fromStdString(std::to_string(i+1));
        graph += curV + ": ";
        std::set<int> list = this->conectLists.at(i+1);
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
