#ifndef CONTRASTTABMIDDLEPART_H
#define CONTRASTTABMIDDLEPART_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include "contrasttabmiddlepartcontent.h"

class ContrastTabMiddlePart : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTabMiddlePart(QWidget *parent = 0);
    int getNumberOfContrasts();
    void addContrast(int evsNumber, int fTestsNumber);
    void addFTest();
    void removeFTest();
    void removeContrast();
    void addOrRemoveEvs(int evsNumber);
signals:

public slots:

private:
    QVBoxLayout * layout;
    QVector<ContrastTabMiddlePartContent*> rows;
};

#endif // CONTRASTTABMIDDLEPART_H