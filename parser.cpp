#include "parser.h"
#include "precompiled.h"
#include "dialog.h"
#include "general.h"

#include <QTextStream>
#include <QBuffer>

static bool** createMat(int v)
{
    if(v <= 0){
        return nullptr;
    }
    bool** matrix = new bool*[v];
    for(size_t i = 0; i < v; i++){
        matrix[i] = new bool[v];
    }

    return matrix;
}

Parser::Parser() {}

bool Parser::isSpecialChar(int key)
{
    if (key == Qt::Key_Shift || key == Qt::Key_Control || key == Qt::Key_Alt ||
        key == Qt::Key_CapsLock || key == Qt::Key_Escape || key == Qt::Key_Backspace ||
        key == Qt::Key_Tab || key == Qt::Key_Return || key == Qt::Key_Delete ||
        key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Left || key == Qt::Key_Right){
        return true;
    }
    return false;
}

int Parser::getFileType(const QString &path)
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

int Parser::readVertexCount(QString &file)
{
    QTextStream ss(&file);
    QString line = ss.readLine();
    int v;
    ss >> v;
    return v;
}

QString &Parser::lastLine(const QTextEdit *textEdit)
{
    static QString text;
    text = textEdit->toPlainText();

    QStringList lines = text.split('\n');
    if(!lines.empty()){
        text = lines.last();
    }
    else{
        text = "";
        Dialog::Warning(_EMPTY_INPUT_);
    }

    return text;
}

int Parser::op(QString &argv)
{
    size_t left = 0;
    size_t right = argv.lastIndexOf(' ');

    QString op = argv.mid(left, right);
    std::string res = op.toStdString();

    if(!(op_str.find(res) == op_str.end())){
        int key = op_str.at(res);
        return key;
    }
    else{
        return ERROR_CODE;
    }
}

int Parser::argc(int command)
{
    if(op_argc.find(command) != op_argc.end()){
        int argc = op_argc.at(command);
        return argc;
    }
    return ERROR_CODE;
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
        case graphTypes::dirgraph:          return new DirGraph(V, mat); break;
        case graphTypes::upseudograph:      return new DirGraph(V, mat); break;
        case graphTypes::dpseudograph:      return new DirGraph(V, mat); break;
        case graphTypes::uweightedgraph:    return new DirGraph(V, mat); break;
        case graphTypes::dweightedgraph:    return new DirGraph(V, mat); break;
        case graphTypes::tree:              return new DirGraph(V, mat); break;
        case graphTypes::bitree:            return new DirGraph(V, mat); break;
        case graphTypes::weightedtree:      return new DirGraph(V, mat); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

Graph *GraphParser::createGraph(int type, const edge_list &el)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(el); break;
        case graphTypes::dirgraph:          return new DirGraph(el); break;
        case graphTypes::upseudograph:      return new DirGraph(el); break;
        case graphTypes::dpseudograph:      return new DirGraph(el); break;
        case graphTypes::uweightedgraph:    return new DirGraph(el); break;
        case graphTypes::dweightedgraph:    return new DirGraph(el); break;
        case graphTypes::tree:              return new DirGraph(el); break;
        case graphTypes::bitree:            return new DirGraph(el); break;
        case graphTypes::weightedtree:      return new DirGraph(el); break;
    default:
        Dialog::Error(_UNDEFINED_GRAPH_TYPE_);
        return nullptr;
    }
    return nullptr;
}

Graph *GraphParser::createGraph(int type, const adj_list &vl)
{
    switch(type){
        case graphTypes::udirgraph:         return new UDirGraph(vl); break;
        case graphTypes::dirgraph:          return new DirGraph(vl); break;
        case graphTypes::upseudograph:      return new DirGraph(vl); break;
        case graphTypes::dpseudograph:      return new DirGraph(vl); break;
        case graphTypes::uweightedgraph:    return new DirGraph(vl); break;
        case graphTypes::dweightedgraph:    return new DirGraph(vl); break;
        case graphTypes::tree:              return new DirGraph(vl); break;
        case graphTypes::bitree:            return new DirGraph(vl); break;
        case graphTypes::weightedtree:      return new DirGraph(vl); break;
    default:

        return nullptr;
    }
    return nullptr;
}

bool **GraphParser::readMat(QString &file)
{
    QTextStream ss(&file);

    QString gType;
    int v;
    ss >> gType;
    ss >> v;

    bool** mat = createMat(v);
    if(mat == nullptr){
        return nullptr;
    }

    for(int i = 0; i < v; i++){
        QString line = ss.readLine();
        QTextStream lineS(&line);
        for(int j = 0; j < v; j++){
            int val;
            lineS >> val;
            mat[i][j] = val;
        }
    }

    return mat;
}

const edge_list &GraphParser::readEdgeList(const QString &file)
{

}

const adj_list &GraphParser::readAdjectList(const QString &file)
{

}

Graph *GraphParser::initGraph(fileTypes fileType, QString &file)
{
    switch(fileType){
    case fileTypes::MAT:
    {
        int v;
        v = Parser::readVertexCount(file);
        bool** mat = readMat(file);
        return createGraph(fileType, v, mat);
    }
        break;
    case fileTypes::EL: break;
    case fileTypes::VL: break;
    default:
        Dialog::Error(_UNDFINED_FILE_TYPE);
        return nullptr;
    }
    return nullptr;
}
