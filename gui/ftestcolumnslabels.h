#ifndef FTESTCOLUMNS_H
#define FTESTCOLUMNS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVector>
#include <QString>
#include <QLabel>

class FTestColumnsLabels : public QWidget
{
    Q_OBJECT
public:
    explicit FTestColumnsLabels(QWidget *parent = 0);
    int getNumberOfFTests();
    void addFTest();
    void removeFTest();
signals:

public slots:
private:
    QVector<QLabel*> fTestsLabels;
    QHBoxLayout * layout;
};

#endif // FTESTCOLUMNS_H
