#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "contrasttab.h"
#include "evstab.h"
#include "myvmp.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void addOrRemoveEvs(int evsNumber);
    void openVmp();
    void clearAll();
private:
    QVBoxLayout * mainLayout;
    QTabWidget * tabs;
    QDialogButtonBox * buttonBox;
    EvsTab * evsTab;
    ContrastTab * contrastTab;
    MyVmp vmp;
};

#endif // MAINWINDOW_H
