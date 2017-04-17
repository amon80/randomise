#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include "contrasttab.h"
#include "evstab.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void addOrRemoveEvs(int evsNumber);

private:
    QTabWidget * tabs;
    QDialogButtonBox * buttonBox;
    EvsTab * evsTab;
    ContrastTab * contrastTab;
};

#endif // MAINWINDOW_H
