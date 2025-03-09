#include "general.h"
#include "parser.h"
#include "dialog.h"
#include "graphmanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFile>
#include <QDir>
#include <QFileDialog>

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
    , ui(new Ui::MainWindow)
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

    int graphType = descriptor.graphType;
    Graph* item = GraphParser::createGraph(graphType);
    if(item == nullptr){return;}
    QTextEdit* itemEdit = new QTextEdit(this);
    itemEdit->setText(descriptor.path);
    this->addTab(itemEdit, item, descriptor.path);
}

void MainWindow::openFileEvent()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Choose Your Graph file", "", "All Files (*)");
    int type = Parser::getExtention(filePath);
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
}

void MainWindow::showHustory()
{

}

void MainWindow::showHelpMsg()
{

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

}

void MainWindow::initWidgets()
{
    ui->files_tab->removeTab(1);
    ui->files_tab->setTabText(0, _HELLO_);
    ui->start_massage->setReadOnly(true);

    QFile text;
    text.setFileName(MSG_F);
    text.open(QFile::ReadOnly);
    QString txtStr = text.readAll();
    ui->start_massage->setText(txtStr);
}
