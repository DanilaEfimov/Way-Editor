#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphs/graph.h"
#include "Overrided/console.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QKeyEvent>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class Console;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    static Ui::MainWindow *ui;
    static std::map<int, Graph*> graphs;
    static std::map<int, QTextEdit*> output;

    void addTab(QTextEdit* itemEdit, Graph* item, const QString& path);

    void init();
    void initWindow();

    void initMenuBar();
    void initFileMenu();
    void initViewMenu();
    void initConsoleMenu();

    void initWidgets();

    static int curTabIndex();

private slots:
    void setWhiteTheme();
    void setBlackTheme();

    void setRightMode();
    void setLeftMode();

    void newFileEvent();
    void openFileEvent();
    void saveFileEvent();

    void showHistory();
    void showHelpMsg();

protected:
    static Graph* currentGraph();
};


#endif // MAINWINDOW_H
