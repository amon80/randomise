#ifndef EVSCOLUMNS_H
#define EVSCOLUMNS_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QHBoxLayout>

class EvsColumnsLabels : public QWidget
{
    Q_OBJECT
public:
    explicit EvsColumnsLabels(QWidget *parent = 0);
    void addOrRemoveEvs(int evNumber);
    int getNumberOfEvs();
signals:

public slots:

private:
    QVector<QLabel*> evsLabels;
    QHBoxLayout * layout;
};

#endif // EVSCOLUMNS_H
