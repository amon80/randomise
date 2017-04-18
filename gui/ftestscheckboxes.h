#ifndef FTESTSCHECKBOXES_H
#define FTESTSCHECKBOXES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVector>
#include <QCheckBox>

class FTestsCheckBoxes : public QWidget
{
    Q_OBJECT
public:
    explicit FTestsCheckBoxes(QWidget *parent = 0, int fTestsNumber = 0);
    void addFTest();
    void removeFTest();
signals:

public slots:
private:
    QHBoxLayout * layout;
    QVector<QCheckBox*> checkBoxes;
};

#endif // FTESTSCHECKBOXES_H
