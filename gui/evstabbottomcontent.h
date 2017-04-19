#ifndef BOTTOMCONTENT_H
#define BOTTOMCONTENT_H

#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QHBoxLayout>
#include <QLabel>

class EvsTabBottomContent : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTabBottomContent(QWidget *parent = 0, QString labelText = "", int nEvs = 0);
    void addEv();
    void removeEv();

signals:

public slots:

private:
    QLabel * inputLabel;
    QSpinBox * groupSpinBox;
    QVector<QSpinBox*> evs;
    QHBoxLayout * layout;
};

#endif // BOTTOMCONTENT_H
