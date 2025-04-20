#include "console.h"
#include "precompiled.h"

Console::Console(QWidget *parent) : QTextEdit(parent)
{}

void Console::updateOutput(Graph *G)
{
    int index = MainWindow::curTabIndex();
    QTextEdit* curEdit = MainWindow::output.at(index);
    curEdit->setText(G->show());
}

void Console::performance()
{
    GraphManager::answer = "";
    static QString argv;
    argv = Parser::lastLine(this);
    Graph* G = MainWindow::currentGraph();
    int res = GraphManager::calculate(argv, G);

    if(GraphManager::answer != "")
        this->append(GraphManager::answer);
    updateOutput(G);
    if(res == ERROR_CODE){
        Dialog::Error(GraphManager::answer);
    }
    this->terminator = 0;
    Parser::updateHistory(GraphManager::answer);
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if(!this->hasFocus() || !MainWindow::curTabIndex()){
        return;
    }

    switch(event->key()){
    case Qt::Key_Backspace:
        if(this->terminator){
            this->terminator--;
            QTextEdit::keyPressEvent(event);
        }
        break;
    case Qt::Key_Return:
        performance();
        QTextEdit::keyPressEvent(event);
        break;
    case Qt::Key_Enter:
        performance();
        QTextEdit::keyPressEvent(event);
        break;
    default:
        if(!Parser::isSpecialChar(event->key())){
            this->terminator++;
            QTextEdit::keyPressEvent(event);
        }
        break;
    }
}
