#include "dialog.h"
#include "parser.h"

#include <QFile>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

QMessageBox* Dialog::mBox = nullptr;
QDialog* Dialog::dBox = nullptr;

void Dialog::initForm()
{
    this->setWindowTitle(_FORM_TITLE_);
    this->setWindowIcon(QIcon(INPUT_FORM_F));
    this->setMaximumSize(QSize(300,200));

    QVBoxLayout* formLayout = new QVBoxLayout();

    QLabel* pathMsg = new QLabel(_INPUT_PATH_MSG_);
    QLabel* typeMsg = new QLabel(_INPUT_TYPE_MSG_);
    this->pathLb = new QLineEdit();
    this->typeLb = new QLineEdit();
    QPushButton* enter = new QPushButton(_ENTER_);

    formLayout->addWidget(pathMsg);
    formLayout->addWidget(pathLb);
    formLayout->addWidget(typeMsg);
    formLayout->addWidget(typeLb);
    formLayout->addWidget(enter);

    this->setLayout(formLayout);
    QFile qss(INPUT_FORM_QSS_F);
    qss.open(QFile::ReadOnly);
    QString style = qss.readAll();
    this->setStyleSheet(style);

    auto pars = [this](){initProtocol(pathLb, typeLb);};

    connect(enter, &QPushButton::clicked, this, pars);
}

void Dialog::closeEvent(QCloseEvent *event)
{
    QList<QWidget*> childrenList = findChildren<QWidget*>();
    for (QWidget* widget : childrenList) {
        widget->deleteLater();
    }

    QWidget::closeEvent(event);
}

Dialog::Dialog()
{

}

void Dialog::Error(const QString &message)
{
    mBox = new QMessageBox();
    mBox->setWindowTitle(_ERROR_TITLE_);
    mBox->setInformativeText(message);
    mBox->setIcon(QMessageBox::Warning);
    mBox->setWindowIcon(QIcon(ERROR_ICO_F));

    mBox->setObjectName(ERROR_BOX);

    QFile qss(ERROR_QSS_F);
    qss.open(QFile::ReadOnly);
    QString styleSheet = qss.readAll();
    mBox->setStyleSheet(styleSheet);

    mBox->exec();
    delete mBox;
}

void Dialog::Warning(const QString &message)
{
    mBox = new QMessageBox();
    mBox->setWindowTitle(_WARNING_TITLE_);
    mBox->setInformativeText(message);
    mBox->setIcon(QMessageBox::Warning);
    mBox->setWindowIcon(QIcon(WARNING_ICO_F));

    mBox->setObjectName(ERROR_BOX);

    QFile qss(WARNING_QSS_F);
    qss.open(QFile::ReadOnly);
    QString styleSheet = qss.readAll();
    mBox->setStyleSheet(styleSheet);

    mBox->exec();
    delete mBox;
}

void Dialog::newFileForm()
{
    this->initForm();
    this->exec();
}

const fileFormat &Dialog::getData() const
{
    return this->data;
}

void Dialog::initProtocol(QLineEdit* path_, QLineEdit* type_)
{
    this->data.path = path_->text();
    int fileT = Parser::getFileType(path_->text());
    if(fileT == -1){
        Dialog::Warning(_INVALID_INPUT_);
        return;
    }
    else{
        this->data.fileType = static_cast<fileTypes>(fileT);
    }

    int graphT = Parser::getGraphType(type_->text());
    if(graphT == -1){
        Dialog::Warning(_INVALID_INPUT_);
        return;
    }
    else{
        this->data.graphType = static_cast<graphTypes>(graphT);
    }

    this->close();
}

