#ifndef OPTIONSTABINFERENCELEVELPART_H
#define OPTIONSTABINFERENCELEVELPART_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

class OptionsTabInferenceLevelPart : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTabInferenceLevelPart(QWidget *parent = 0);
    float getInferenceLevel();
signals:

public slots:
private:
    QLabel * inferenceLevelLabel;
    QDoubleSpinBox * inferenceLevelSpinBox;
    QHBoxLayout * layout;
};

#endif // OPTIONSTABINFERENCELEVELPART_H
