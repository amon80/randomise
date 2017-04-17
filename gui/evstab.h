#ifndef EVSTAB_H
#define EVSTAB_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QLabel>
#include "evstabtoppart.h"
#include "evstabuppermiddlepart.h"
#include "evstabmiddlepart.h"
#include "evstabbottompart.h"
#include "evstabbottomcontent.h"
#include "myvmp.h"

class EvsTab : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTab(QWidget *parent = 0);
    void addOrRemoveEvs(int evNumber);
signals:
    void valueChanged(int value);
public slots:
    void openVmp();
    void clearAll();
private slots:
private:
    EvsTabTopPart * top;
    EvsTabUpperMiddlePart * upperMiddle;
    EvsTabMiddlePart * middle;
    EvsTabBottomPart * bottom;
};

#endif // EVSTAB_H
