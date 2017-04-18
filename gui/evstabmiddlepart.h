#ifndef EVSTABMIDDLEPART_H
#define EVSTABMIDDLEPART_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVector>

class EvsTabMiddlePart : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTabMiddlePart(QWidget *parent = 0);
    int getNumberOfEvs();
    void addEv();
    void removeEv();
signals:

public slots:
private:
    QLabel * emptyLabel;
    QLabel * groupLabel;
    QVector<QLabel*> evLabels;
    QHBoxLayout * layout;
};

#endif // EVSTABMIDDLEPART_H
