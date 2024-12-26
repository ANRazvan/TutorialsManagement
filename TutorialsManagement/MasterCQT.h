#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MasterCQT.h"

class MasterCQT : public QMainWindow
{
    Q_OBJECT

public:
    MasterCQT(QWidget *parent = nullptr);
    ~MasterCQT();

private:
    Ui::MasterCQTClass ui;
};
