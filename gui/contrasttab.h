#ifndef CONTRASTTAB_H
#define CONTRASTTAB_H

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "contrasttabtoppart.h"
#include "contrasttabuppermiddlepart.h"
#include "contrasttabmiddlepart.h"

class ContrastTab : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTab(QWidget *parent = 0);
    void addOrRemoveEvs(int evsNumber);
    int getNumberOfEvs();
    int getNumberOfFTests();
    int getNumberOfContrasts();
    int getContrast(int contrastNumber, int evNumber);
signals:
public slots:
    void ftestsValueChanged(int ftestsNumber);
    void contrastsValueChanged(int);
private:
    ContrastTabTopPart * top;
    ContrastTabMiddleUpperPart * uppermiddle;
    ContrastTabMiddlePart * middle;
};

#endif // CONTRASTTAB_H
