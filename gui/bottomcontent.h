#ifndef BOTTOMCONTENT_H
#define BOTTOMCONTENT_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QHBoxLayout>

class BottomContent : public QWidget
{
    Q_OBJECT
public:
    explicit BottomContent(QWidget *parent = 0, int inputnumber = 1, int evnumber = 1);
    void addEv();
    void removeEv();

signals:

public slots:

private:
    QSpinBox * groupSpinBox;
    QVector<QSpinBox*> evs;
    QHBoxLayout * layout;
};

#endif // BOTTOMCONTENT_H
