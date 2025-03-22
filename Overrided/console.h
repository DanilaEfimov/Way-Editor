#pragma once
#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "mainwindow.h"

#include <QTextEdit>
#include <QKeyEvent>

class Console : public QTextEdit
{
    Q_OBJECT
    friend class MainWindow;
public:
    Console(QWidget* parent = nullptr);
    static void updateOutput(Graph* G);
protected:
    int terminator = 0;
    virtual void performance();
    virtual void keyPressEvent(QKeyEvent* event) override;
};

#endif // TEXTEDIT_H
