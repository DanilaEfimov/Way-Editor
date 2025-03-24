#include "general.h"
#include "parser.h"
#include "Overrided/dialog.h"
#include "graphmanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFile>
#include <QDir>
#include <QFileDialog>

Ui::MainWindow* MainWindow::ui = new Ui::MainWindow;
std::map<int, Graph*> MainWindow::graphs = {};
std::map<int, QTextEdit*> MainWindow::output = {};

template<typename T>
static void clear(std::map<int, T*>& container) {
    for (auto& p : container) {
        delete p.second;
        p.second = nullptr;
    }
    container.clear();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
    clear<Graph>(graphs);
    clear<QTextEdit>(output);
}

void MainWindow::addTab(QTextEdit *itemEdit, Graph *item, const QString& path)
{
    QString info = item->show();
    itemEdit->setText(info);
    itemEdit->setReadOnly(true);
    int number = graphs.size() + 1;
    graphs.emplace(std::make_pair(number, item));
    output.emplace(std::make_pair(number, itemEdit));
    ui->files_tab->addTab(itemEdit, path);
}

void MainWindow::init()
{
    this->initWindow();
    this->initWidgets();
    this->setWhiteTheme();
    this->initMenuBar();
}

void MainWindow::initWindow()
{
    this->setWindowTitle(NAME);
    this->setWindowIcon(QIcon(ICON_F));
}

void MainWindow::setWhiteTheme()
{
    QFile style;
    style.setFileName(WHITE_F);
    style.open(QFile::ReadOnly);
    QString qssStr = style.readAll();
    this->setStyleSheet(qssStr);
    ui->black_theme->setChecked(false);
    ui->white_theme->setChecked(true);
}

void MainWindow::setBlackTheme()
{
    QFile style;
    style.setFileName(BLACK_F);
    style.open(QFile::ReadOnly);
    QString qssStr = style.readAll();
    this->setStyleSheet(qssStr);
    ui->white_theme->setChecked(false);
    ui->black_theme->setChecked(true);
}

void MainWindow::setRightMode()
{
    ui->central->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    ui->left_mode->setChecked(false);
    ui->right_mode->setChecked(true);
}

void MainWindow::setLeftMode()
{
    ui->central->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    ui->left_mode->setChecked(true);
    ui->right_mode->setChecked(false);
}

void MainWindow::newFileEvent()
{
    Dialog inputForm;
    inputForm.newFileForm();
    fileFormat descriptor = inputForm.getData();

    int verdict = FileManager::createNewFile(descriptor.path);
    if(verdict == ERROR_CODE){
        Dialog::Warning(_PROBLEM_OF_OPEN_FILE_);
        return;
    }

    int graphType = descriptor.graphType;
    Graph* item = GraphParser::createGraph(graphType);
    if(item == nullptr){return;}
    QTextEdit* itemEdit = new QTextEdit(this);
    itemEdit->setText(descriptor.path);
    this->addTab(itemEdit, item, descriptor.path);

    int index = ui->files_tab->count() - 1;
    ui->files_tab->setCurrentIndex(index);
    ui->input_area->setReadOnly(false);
}

void MainWindow::openFileEvent()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Choose Your Graph file", "", "All Files (*)");
    int type = Parser::getFileType(filePath);
    if(type == -1){
        Dialog::Error(_UNDFINED_FILE_TYPE);
        return;
    }
    if(!FileManager::isExistingFile(filePath)){
        Dialog::Error(_INVALID_DIR_ERROR_);
        return;
    }
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QString graphStr = file.readAll();

    Graph* item = GraphParser::initGraph(static_cast<fileTypes>(type), filePath);
    if(item == nullptr){return;}
    QTextEdit* itemEdit = new QTextEdit(this);
    itemEdit->setText(filePath);
    this->addTab(itemEdit, item, filePath);

    ui->input_area->setReadOnly(false);
}

void MainWindow::saveFileEvent()
{
    static QString data;

    int index = this->curTabIndex();
    if(!index){return;}
    QString filename = ui->files_tab->tabText(index);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        Dialog::Warning(_OPEN_FILE_ERROR_);
        return;
    }

    QTextStream in(&file);
    Graph* G = graphs[index];
    fileTypes filetype = static_cast<fileTypes>(Parser::getFileType(filename));
    data = GraphParser::toStr(G, filetype);
    in << data << '\n';
    file.close();

    data = "";
}

void MainWindow::showHistory()
{

}

void MainWindow::showHelpMsg()
{
    QFile helptxt;
    helptxt.setFileName(HELP_F);
    helptxt.open(QFile::ReadOnly);
    QString help = helptxt.readAll();
    ui->start_massage->setText(help);
    helptxt.close();
}

Graph *MainWindow::currentGraph()
{
    int index = ui->files_tab->currentIndex();
    if(index == 0) {
        return nullptr;
    }
    Graph* current = graphs.at(index);
    return current;
}

void MainWindow::initMenuBar()
{
    this->initFileMenu();
    this->initViewMenu();
    this->initConsoleMenu();
}


void MainWindow::initFileMenu()
{
    ui->new_file->setIcon(QIcon(NEW_FILE_F));
    ui->open->setIcon((QIcon(OPEN_F)));
    ui->save->setIcon(QIcon(SAVE_F));
    ui->remove->setIcon(QIcon(REMOVE_F));
    connect(ui->new_file, &QAction::triggered, this, &MainWindow::newFileEvent);
    connect(ui->open, &QAction::triggered, this, &MainWindow::openFileEvent);
    connect(ui->save, &QAction::triggered, this, &MainWindow::saveFileEvent);
}

void MainWindow::initViewMenu()
{
    ui->white_theme->setCheckable(true);
    ui->white_theme->setChecked(true);
    connect(ui->white_theme, &QAction::triggered, this, &MainWindow::setWhiteTheme);
    ui->black_theme->setCheckable(true);
    ui->black_theme->setChecked(false);
    connect(ui->black_theme, &QAction::triggered, this, &MainWindow::setBlackTheme);
    ui->right_mode->setCheckable(true);
    ui->right_mode->setChecked(true);
    connect(ui->right_mode, &QAction::triggered, this, &MainWindow::setRightMode);
    ui->left_mode->setCheckable(true);
    ui->left_mode->setChecked(false);
    connect(ui->left_mode, &QAction::triggered, this, &MainWindow::setLeftMode);
}

void MainWindow::initConsoleMenu()
{
    connect(ui->help, &QAction::triggered, this, &MainWindow::showHelpMsg);
}

void MainWindow::initWidgets()
{
    ui->files_tab->removeTab(1);
    ui->files_tab->setTabText(0, _HELLO_);
    ui->start_massage->setReadOnly(true);
    ui->input_area->setReadOnly(true);

    QFile text;
    text.setFileName(MSG_F);
    text.open(QFile::ReadOnly);
    QString txtStr = text.readAll();
    ui->start_massage->setText(txtStr);
}

int MainWindow::curTabIndex()
{
    return ui->files_tab->currentIndex();
}

