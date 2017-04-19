#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include "optionstabnumberpermutationpart.h"
#include "optionstabinferencelevelpart.h"
#include "optionstabusetfcepart.h"

struct Options{
    int numPermutation;
    float alpha;
    bool EE;
    bool ISE;
    bool useTfce;
};

class OptionsTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTab(QWidget *parent = 0);
    Options getOptions();
signals:

public slots:
private:
    QVBoxLayout * layout;
    OptionsTabNumberPermutationPart * numberPermutationPart;
    OptionsTabInferenceLevelPart * inferenceLevelPart;
    OptionsTabUseTfcePart * useTfcePart;
};

#endif // OPTIONSTAB_H
