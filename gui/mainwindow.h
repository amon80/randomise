#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget * tabs;
    QDialogButtonBox * buttonBox = new QDialogButtonBox;
};

#endif // MAINWINDOW_H
