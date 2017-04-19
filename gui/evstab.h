#ifndef EVSTAB_H
#define EVSTAB_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QLabel>
#include "filetabtoppart.h"
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
    void addSubject();
    void removeSubject();
    void removeAllSubjects();
    int getNumEvs();
    int getEv(int row, int col);
signals:
    void valueChanged(int value);
private slots:
private:
    EvsTabUpperMiddlePart * upperMiddle;
    EvsTabMiddlePart * middle;
    EvsTabBottomPart * bottom;
};

#endif // EVSTAB_H
