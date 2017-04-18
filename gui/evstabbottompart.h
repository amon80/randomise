#ifndef EVSTABBOTTOMPART_H
#define EVSTABBOTTOMPART_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include "evstabbottomcontent.h"

class EvsTabBottomPart : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTabBottomPart(QWidget *parent = 0);
    void addEv();
    void removeEv();
    void addRow();
    void removeRow();
    int getNRows();
signals:

public slots:

private:
    QVBoxLayout * layout;
    QVector<EvsTabBottomContent*> rows;
};

#endif // EVSTABBOTTOMPART_H
