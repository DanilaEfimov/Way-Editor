#include "graphmanager.h"

#include <QRegularExpression>

QString GraphManager::answer = "";

GraphManager::GraphManager() {}

int GraphManager::cast_op0(QTextEdit *pad)
{
    pad->setText(QString(""));
    return operations::clear_text;
}

int GraphManager::cast_op1(Graph *G, std::set<int> &adj)
{
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

int GraphManager::cast_op2(Graph *G, int from, int to)
{
    int type = G->type();
    switch(type){
        case graphTypes::udirgraph:         G->addE(from, to); break;
        case graphTypes::dirgraph:          G->addE(from, to); break;
        case graphTypes::upseudograph:      G->addE(from, to); break;
        case graphTypes::dpseudograph:      G->addE(from, to); break;
        case graphTypes::uweightedgraph:    G->addE(from, to); break;
        case graphTypes::dweightedgraph:    G->addE(from, to); break;
        case graphTypes::tree:              return -1; break;
        case graphTypes::bitree:            return -1; break;
        case graphTypes::weightedtree:      return -1; break;
    default:
        return -1;
    }
    return operations::add_edge;
}

int GraphManager::cast_op3(Graph *G, int id)
{
    int type = G->type();
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
    return operations::erase_vertex;
}

int GraphManager::cast_op4(Graph *G, int from, int to)
{
    int type = G->type();
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
    return operations::erase_edge;
}

int GraphManager::calculate(QString &argv, Graph *G)
{

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
    if (dir.exists()){
        return true;
    }
    return false;
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
