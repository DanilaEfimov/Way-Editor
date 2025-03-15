#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphs/graph.h"

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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static std::map<int, Graph*> graphs;
    static std::map<int, QTextEdit*> output;
    int keys = 0;

    void addTab(QTextEdit* itemEdit, Graph* item, const QString& path);

    void init();
    void initWindow();

    void initMenuBar();
    void initFileMenu();
    void initViewMenu();
    void initConsoleMenu();

    void initWidgets();

private slots:
    void setWhiteTheme();
    void setBlackTheme();

    void setRightMode();
    void setLeftMode();

    void newFileEvent();
    void openFileEvent();

    void showHustory();
    void showHelpMsg();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void cast_keyEvent(QString& line, QKeyEvent* key); // for every case own function
    void cast_enter(QString& argv);
    void cast_backspace();
    Graph* currentGraph() const;
};


#endif // MAINWINDOW_H
