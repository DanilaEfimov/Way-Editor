#ifndef DIALOG_H
#define DIALOG_H

#include "general.h"

#include <QMessageBox>
#include <QDialog>
#include <QString>
#include <QLineEdit>

typedef struct {
    QString path;
    graphTypes graphType;
    fileTypes fileType;
} fileFormat;

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    fileFormat data;

    virtual void initForm();
    virtual void closeEvent(QCloseEvent* event) override;

private:
    static QMessageBox* mBox;
    static QDialog* dBox;

    QLineEdit* pathLb;
    QLineEdit* typeLb;

public:
    Dialog();
    virtual ~Dialog() = default;

    static void Error(const QString& message);
    static void Warning(const QString& message);
    virtual void newFileForm();

    const fileFormat& getData() const;

public slots:
    virtual void initProtocol(QLineEdit* path, QLineEdit* type);

};

#endif // DIALOG_H
