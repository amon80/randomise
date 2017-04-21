#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QString>
#include "filetab.h"
#include "contrasttab.h"
#include "evstab.h"
#include "optionstab.h"
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
    void collectDataAndFire();
    void closeWindow();
private:
    QString filepath;
    QVBoxLayout * mainLayout;
    QTabWidget * tabs;
    QDialogButtonBox * buttonBox;
    FileTab * fileTab;
    EvsTab * evsTab;
    ContrastTab * contrastTab;
    OptionsTab * optionsTab;
    MyVmp vmp;
};

#endif // MAINWINDOW_H
