#ifndef CONTRASTTAB_H
#define CONTRASTTAB_H

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "contrasttabtoppart.h"

#include "contrasttabuppermiddlepart.h"

class ContrastTab : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTab(QWidget *parent = 0);
    void addOrRemoveEvs(int evsNumber);
signals:

public slots:

private:
    ContrastTabTopPart * top;
    ContrastTabMiddleUpperPart * uppermiddle;
};

#endif // CONTRASTTAB_H
