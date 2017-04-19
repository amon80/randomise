#ifndef OPTIONSTABUSETFCEPART_H
#define OPTIONSTABUSETFCEPART_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>

class OptionsTabUseTfcePart : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsTabUseTfcePart(QWidget *parent = 0);
    bool getUseTfce();
    bool getEE();
    bool getISE();
signals:

public slots:
private:
    QHBoxLayout * layout;
    QCheckBox * useTfceCheckBox;
    QCheckBox * EECheckBox;
    QCheckBox * ISECheckBox;

};

#endif // OPTIONSTABUSETFCEPART_H
