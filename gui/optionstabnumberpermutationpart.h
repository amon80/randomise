#ifndef OPTIONSTABNUMBERPERMUTATIONPART_H
#define OPTIONSTABNUMBERPERMUTATIONPART_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

class OptionsTabNumberPermutationPart : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTabNumberPermutationPart(QWidget *parent = 0);
    int getNumPermutation();
signals:

public slots:
private:
    QLabel * numberPermutationLabel;
    QSpinBox * numberPermutationSpinBox;
    QHBoxLayout * layout;
};

#endif // OPTIONSTABNUMBERPERMUTATIONPART_H
