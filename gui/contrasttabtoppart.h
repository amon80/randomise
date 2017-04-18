#ifndef CONTRASTTABTOPPART_H
#define CONTRASTTABTOPPART_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

class ContrastTabTopPart : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTabTopPart(QWidget *parent = 0);
signals:
public slots:
private:
    QHBoxLayout * layout;
    QSpinBox * contrastSpinBox;
    QSpinBox * ftestsSpinBox;
    QLabel * contrastSpinBoxLabel;
    QLabel * ftestsSpinBoxLabel;
};

#endif // CONTRASTTABTOPPART_H
