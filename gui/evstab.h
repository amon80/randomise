#ifndef EVSTAB_H
#define EVSTAB_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QLabel>
#include "bottomcontent.h"

class EvsTab : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTab(QWidget *parent = 0, int num_of_subjects = 1);

signals:

public slots:

private slots:
    void addOrRemoveEV(int evSpinBoxValue);
    void openvmp();
private:
    QHBoxLayout * middleLayout;
    QSpinBox * evnumberSpinbox;
    QLineEdit * fileEdit;
    int evnumber;
    QWidget * labelRow;
    QVector<BottomContent*> rows;
    QVector<QLabel*> evLabels;
    int num_of_subjects;
};

#endif // EVSTAB_H
