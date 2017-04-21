#ifndef CONTRASTTABMIDDLEPART_H
#define CONTRASTTABMIDDLEPART_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QString>
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
    int getContrast(int contrastNumber, int evNumber);
    QString getContrastName(int contrastNumber);
signals:

public slots:

private:
    QVBoxLayout * layout;
    QVector<ContrastTabMiddlePartContent*> rows;
};

#endif // CONTRASTTABMIDDLEPART_H
