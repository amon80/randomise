#ifndef EVSSPINBOXES_H
#define EVSSPINBOXES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QVector>

class EvsSpinBoxes : public QWidget
{
    Q_OBJECT
public:
    explicit EvsSpinBoxes(QWidget *parent = 0, int evsNumber = 0);
    int getEvsNumber();
    void addEv();
    void removeEv();
    int getContrast(int evNumber);
signals:

public slots:
private:
    QHBoxLayout * layout;
    QVector<QSpinBox*> spinBoxes;
};

#endif // EVSSPINBOXES_H
