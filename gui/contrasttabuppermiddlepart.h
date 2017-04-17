#ifndef MIDDLETOPWIDGET_H
#define MIDDLETOPWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "evscolumnslabels.h"
#include "ftestcolumnslabels.h"

class ContrastTabMiddleUpperPart : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTabMiddleUpperPart(QWidget *parent = 0);
    void addOrRemoveEvs(int evsNumber);
signals:

public slots:
private:
    QHBoxLayout * layout;
    QLabel * emptyLabel;
    QLabel * contrastTitle;
    EvsColumnsLabels * evsColumnsLabels;
    FTestColumnsLabels * fTestColumnsLabels;
};

#endif // MIDDLETOPWIDGET_H
