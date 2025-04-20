#ifndef DIRGRAPH_H
#define DIRGRAPH_H

#include "graph.h"

<<<<<<< HEAD
#include <stack>

typedef std::pair<int,int> edge;
typedef std::set<edge> edge_list;
typedef std::set<std::set<int>> scc; // strongly connectyvyticompoment
=======
typedef std::pair<int,int> edge;
typedef std::set<edge> edge_list;
>>>>>>> c4a626a2e3725ab737452b36229c1b6482689c22

class DirGraph : public Graph
{
private:
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

    virtual scc& Kosaraju();
    virtual scc& Tarjan();

    virtual int type() const override;

    virtual const QString& show() const override;
};

#endif // DIRGRAPH_H

/*
#include <stack>
#include <set>
#include <map>

typedef std::set<int> SCC;  // Сильно связная компонента
typedef std::set<SCC> scc;  // Множество сильных компонент

class DirGraph : public Graph {
private:
    // Помощь для алгоритма Тарьяна
    void tarjanDFS(int v, std::map<int, int>& indices,
                   std::map<int, int>& lowlink,
                   std::stack<int>& stack,
                   std::set<int>& onStack,
                   scc& sccs,
                   int& index);
public:
    // Метод для нахождения SCC
    scc& Tarjan();
};

scc& DirGraph::Tarjan() {
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

void DirGraph::tarjanDFS(int v, std::map<int, int>& indices,
                          std::map<int, int>& lowlink,
                          std::stack<int>& stack,
                          std::set<int>& onStack,
                          scc& sccs,
                          int& index) {
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


*/
