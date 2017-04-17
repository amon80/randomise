#ifndef EVSTABUPPERMIDDLEPART_H
#define EVSTABUPPERMIDDLEPART_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

class EvsTabUpperMiddlePart : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTabUpperMiddlePart(QWidget *parent = 0);

signals:

public slots:

private:
    QHBoxLayout * layout;
    QLabel * evLabel;
    QSpinBox * evNumberSpinBox;
};

#endif // EVSTABUPPERMIDDLEPART_H
