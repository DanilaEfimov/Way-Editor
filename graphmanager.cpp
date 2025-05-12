#include "graphmanager.h"

#include <QRegularExpression>

QString GraphManager::answer = "";

GraphManager::GraphManager() {}

int GraphManager::zeroArgOp(int code, Graph *G)
{
    if(!GraphManager::isDirected(G)){
        return operations::kosaraju;
    }
    switch(code){
        case operations::kosaraju: return cast_op6(G);break;
    default:
        return -1;
    }
    return -1;
}

int GraphManager::oneArgOp(int code, Graph *G, QString &argument)
{
    switch(code){
    default:
        return -1;
    }
    return -1;
}

int GraphManager::twoArgOp(int code, Graph *G, QString &argument)
{
    switch(code){
        case operations::add_edge: return cast_op2(G, argument); break;
        case operations::erase_edge: return cast_op4(G, argument); break;
    default:
        return -1;
    }
    return -1;
}

int GraphManager::threeArgOp(int code, Graph *G, QString &argument)
{
    switch(code){
    default:
        return -1;
    }
    return -1;
}

int GraphManager::limitlessArgOp(int code, Graph *G, QString &argument)
{
    switch(code){
        case operations::add_vertex: return cast_op1(G, argument); break;
        case operations::add_edge: return cast_op2(G, argument); break;
        case operations::erase_vertex: return cast_op3(G, argument); break;
        case operations::erase_edge: return cast_op4(G, argument); break;
    default:
        return -1;
    }
    return -1;
}

bool GraphManager::isDirected(Graph *G)
{
    int code = G->type();
    switch(code){
        case graphTypes::dirgraph:          return true; break;
        case graphTypes::udirgraph:         return false; break;
        case graphTypes::dpseudograph:      return true; break;
        case graphTypes::dweightedgraph:    return true; break;
        case graphTypes::upseudograph:      return false; break;
        case graphTypes::weightedtree:      return false; break;
        case graphTypes::tree:              return false; break;
        case graphTypes::bitree:            return false; break;
    default:
        return false;
    }
    return false;
}

bool GraphManager::isTree(Graph *G)
{
    int code = G->type();
    switch(code){
        case graphTypes::dirgraph:          return false; break;
        case graphTypes::udirgraph:         return false; break;
        case graphTypes::dpseudograph:      return false; break;
        case graphTypes::dweightedgraph:    return false; break;
        case graphTypes::upseudograph:      return false; break;
        case graphTypes::weightedtree:      return true; break;
        case graphTypes::tree:              return true; break;
        case graphTypes::bitree:            return true; break;
    default:
        return false;
    }
    return false;
}

int GraphManager::cast_op(int code, Graph *G, QString &arguments)
{
    int argc = Parser::argc(code);
    switch(argc){
        case ZERO: return zeroArgOp(code, G); break;
        case ONE: return oneArgOp(code,G,arguments); break;
        case TWO: return twoArgOp(code, G, arguments); break;
        case THREE: break;
        case FOUR: break;
        case LIMITLESS: return limitlessArgOp(code, G, arguments); break;
    default:
        return -1;
        break;
    }
    return -1;
}

int GraphManager::cast_op0(QTextEdit *pad)
{
    pad->setText(QString(""));
    return operations::clear_text;
}

int GraphManager::cast_op1(Graph *G, QString& argv)
{
    argument arg = Parser::VLfromArgv(argv);
    std::set<int> adj = arg.list;
    int type = G->type();
    switch(type){
        case graphTypes::udirgraph:         G->addV(adj); break;
        case graphTypes::dirgraph:          G->addV(adj); break;
        case graphTypes::upseudograph:      G->addV(adj); break;
        case graphTypes::dpseudograph:      G->addV(adj); break;
        case graphTypes::uweightedgraph:    G->addV(adj); break;
        case graphTypes::dweightedgraph:    G->addV(adj); break;
        case graphTypes::tree:              G->addV(adj); break;
        case graphTypes::bitree:            G->addV(adj); break;
        case graphTypes::weightedtree:      G->addV(adj); break;
    default:
        return -1;
    }
    return operations::add_vertex;
}

int GraphManager::cast_op2(Graph *G, QString& argv)
{
    argument arg = Parser::EdgeFromArgv(argv);
    int from = arg.e.first;
    int to = arg.e.second;
    int type = G->type();
    switch(type){
        case graphTypes::udirgraph:         G->addE(from, to); break;
        case graphTypes::dirgraph:          G->addE(from, to); break;
        case graphTypes::upseudograph:      G->addE(from, to); break;
        case graphTypes::dpseudograph:      G->addE(from, to); break;
        case graphTypes::uweightedgraph:    G->addE(from, to); break;
        case graphTypes::dweightedgraph:    G->addE(from, to); break;
        case graphTypes::tree:
            GraphManager::answer = _GRAPH_TYPE_CMD_ERROR_; return -1; break;
        case graphTypes::bitree:
            GraphManager::answer = _GRAPH_TYPE_CMD_ERROR_; return -1; break;
        case graphTypes::weightedtree:
            GraphManager::answer = _GRAPH_TYPE_CMD_ERROR_; return -1; break;
    default:
        return -1;
    }
    return operations::add_edge;
}

int GraphManager::cast_op3(Graph *G, QString& argv)
{
    argument arg = Parser::VLfromArgv(argv);
    int type = G->type();
    while(!arg.list.empty()){
        int id = *arg.list.begin();
        switch(type){
            case graphTypes::udirgraph:         G->eraseV(id); break;
            case graphTypes::dirgraph:          G->eraseV(id); break;
            case graphTypes::upseudograph:      G->eraseV(id); break;
            case graphTypes::dpseudograph:      G->eraseV(id); break;
            case graphTypes::uweightedgraph:    G->eraseV(id); break;
            case graphTypes::dweightedgraph:    G->eraseV(id); break;
            case graphTypes::tree:              G->eraseV(id); break;
            case graphTypes::bitree:            G->eraseV(id); break;
            case graphTypes::weightedtree:      G->eraseV(id); break;
        default:
            return -1;
        }
        arg.list.erase(arg.list.begin());
    }
    return operations::erase_vertex;
}

int GraphManager::cast_op4(Graph *G, QString& argv)
{
    argument arg = Parser::ELfromArgv(argv);
    int type = G->type();
    while(!arg.el.empty()){
        int from = arg.el.begin()->first;
        int to = arg.el.begin()->second;
        if(from <= 0 || from > G->getV() || to <= 0 || to > G->getV()){
            GraphManager::answer = _UNDEFINED_ARG_ERROR;
            return -1;
        }
        arg.el.erase(arg.el.begin());
        switch(type){
            case graphTypes::udirgraph:         G->eraseE(from, to); break;
            case graphTypes::dirgraph:          G->eraseE(from, to); break;
            case graphTypes::upseudograph:      G->eraseE(from, to); break;
            case graphTypes::dpseudograph:      G->eraseE(from, to); break;
            case graphTypes::uweightedgraph:    G->eraseE(from, to); break;
            case graphTypes::dweightedgraph:    G->eraseE(from, to); break;
            case graphTypes::tree:              G->eraseE(from, to); break;
            case graphTypes::bitree:            G->eraseE(from, to); break;
            case graphTypes::weightedtree:      G->eraseE(from, to); break;
        default:
            return -1;
        }
    }
    return operations::erase_edge;
}

int GraphManager::cast_op6(Graph *G)
{
    if(!GraphManager::isDirected(G)){
        return operations::kosaraju;
    }
    static scc components = {};
    components = reinterpret_cast<DirGraph*>(G)->Kosaraju();
    GraphManager::answer = "";
    for(auto& c : components){
        GraphManager::answer += "component: ";
        for(auto v : c){
            answer += QString::fromStdString(std::to_string(v)) + " ";
        }
        GraphManager::answer += "\n";
    }
    answer.chop(1); // remove last "\n"
    return operations::kosaraju;
}

int GraphManager::calculate(QString &argv, Graph *G)
{
    int opCode = Parser::op(argv);
    QString arguments = Parser::argv(argv);
    int res = cast_op(opCode, G, arguments);
    return res;
}

// ^^^ GraphManager / FileManager vvv

FileManager::FileManager() {}

bool FileManager::isValidPath(const QString &path)
{
    if (path.isEmpty()) {
        Dialog::Warning(_EMPTY_INPUT_);
        return false;
    }

    QRegularExpression pathPattern("^[A-Za-z0-9_\\-\\/\\.\\s:]+$");
    QRegularExpressionMatch match = pathPattern.match(path);
    if (!match.hasMatch()) {
        Dialog::Error(_PROHIBITED_CHARACTERS_);
        return false;
    }

    QFile file(path);
    if (file.exists()) {
        return true;
    }

    QDir dir(path);
    if (dir.exists()) {
        return true;
    }
    return true;
}

bool FileManager::isExistingDir(const QString &path)
{
    QDir dir(path);
    return dir.exists();
}

bool FileManager::isExistingFile(const QString &path)
{
    return QFile::exists(path);
}

int FileManager::createNewFile(const QString &path)
{
    if(!FileManager::isValidPath(path)){
        return ERROR_CODE;
    }

    QFile file(path);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            file.close();
        }
        else{
            return ERROR_CODE;
        }
    }
    return 0;
}
