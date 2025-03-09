#include "parser.h"
#include "precompiled.h"
#include "dialog.h"
#include "general.h"

Parser::Parser() {}

int Parser::getExtention(const QString &path)
{
    std::size_t l, r;
    std::string stdPath = path.QString::toStdString();
    l = stdPath.find_last_of('.');
    r = stdPath.size() - 1;
    if(l == std::string::npos || r < l){
        Dialog::Warning(_PATH_PARS_WARNING_);
        return -1;
    }
    std::string extention = stdPath.substr(l, r);
    if(extentions.find(extention) != extentions.end()){
        return extentions.at(extention);
    }
    return -1;
}

const QString &Parser::getExctention(int code)
{
    static QString answer = "";
    if(r_extentions.find(code) != r_extentions.end()){
        answer = QString::fromStdString(r_extentions.at(code));
    }
    else{
        Dialog::Error(_UNDEFINED_ERROR_);
        answer = _UNDEFINED_ERROR_;
    }
    return answer;
}

int Parser::getGraphType(const QString &line)
{
    std::string stdLine = line.toStdString();
    if(graphs.find(stdLine) == graphs.end()){
        Dialog::Warning(_GRAPH_TYPE_PARS_WARNING_);
        return -1;
    }
    else{
        int code = graphs.at(line.toStdString());
        return code;
    }
    return -1;
}

const QString &Parser::getGraphType(int code)
{
    static QString answer = "";
    if(r_graphs.find(code) != r_graphs.end()){
        answer = QString::fromStdString(r_graphs.at(code));
    }
    else{
        Dialog::Error(_UNDEFINED_ERROR_);
        answer = _UNDEFINED_ERROR_;
    }
    return answer;
}

// ^^^ PARSER / GRAPH_PARSER vvv

Graph *GraphParser::createGraph(int type)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(); break;
        case graphTypes::dirgraph:          return new DirGraph(); break;
        case graphTypes::upseudograph:      return new DirGraph(); break;
        case graphTypes::dpseudograph:      return new DirGraph(); break;
        case graphTypes::uweightedgraph:    return new DirGraph(); break;
        case graphTypes::dweightedgraph:    return new DirGraph(); break;
        case graphTypes::tree:              return new DirGraph(); break;
        case graphTypes::bitree:            return new DirGraph(); break;
        case graphTypes::weightedtree:      return new DirGraph(); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

Graph *GraphParser::createGraph(int type, int V, bool **mat)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(V, mat); break;
        case graphTypes::dirgraph:          return new DirGraph(); break;
        case graphTypes::upseudograph:      return new DirGraph(); break;
        case graphTypes::dpseudograph:      return new DirGraph(); break;
        case graphTypes::uweightedgraph:    return new DirGraph(); break;
        case graphTypes::dweightedgraph:    return new DirGraph(); break;
        case graphTypes::tree:              return new DirGraph(); break;
        case graphTypes::bitree:            return new DirGraph(); break;
        case graphTypes::weightedtree:      return new DirGraph(); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

Graph *GraphParser::createGraph(int type, const edge_list &el)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(); break;
        case graphTypes::dirgraph:          return new DirGraph(); break;
        case graphTypes::upseudograph:      return new DirGraph(); break;
        case graphTypes::dpseudograph:      return new DirGraph(); break;
        case graphTypes::uweightedgraph:    return new DirGraph(); break;
        case graphTypes::dweightedgraph:    return new DirGraph(); break;
        case graphTypes::tree:              return new DirGraph(); break;
        case graphTypes::bitree:            return new DirGraph(); break;
        case graphTypes::weightedtree:      return new DirGraph(); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

Graph *GraphParser::createGraph(int type, const adj_list &vl)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(); break;
        case graphTypes::dirgraph:          return new DirGraph(); break;
        case graphTypes::upseudograph:      return new DirGraph(); break;
        case graphTypes::dpseudograph:      return new DirGraph(); break;
        case graphTypes::uweightedgraph:    return new DirGraph(); break;
        case graphTypes::dweightedgraph:    return new DirGraph(); break;
        case graphTypes::tree:              return new DirGraph(); break;
        case graphTypes::bitree:            return new DirGraph(); break;
        case graphTypes::weightedtree:      return new DirGraph(); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

bool **GraphParser::readMat(const QString &file)
{
    return nullptr;
}

const edge_list &GraphParser::readEdgeList(const QString &file)
{

}

const adj_list &GraphParser::readAdjectList(const QString &file)
{

}


