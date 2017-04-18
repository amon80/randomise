#ifndef CONTRASTTABMIDDLEPARTCONTENT_H
#define CONTRASTTABMIDDLEPARTCONTENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "evsspinboxes.h"
#include "ftestscheckboxes.h"

class ContrastTabMiddlePartContent : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastTabMiddlePartContent(QWidget *parent = 0, int contrastNumber = 1, int evsNumber = 0, int fTestsNumber = 0);
    void addOrRemoveEvs(int evsNumber);
    void addFTest();
    void removeFTest();
signals:

public slots:
private:
    QHBoxLayout * layout;
    QLabel * contrastLabel;
    QLineEdit * contrastTitleLineEdit;
    EvsSpinBoxes * evsSpinBoxes;
    FTestsCheckBoxes * fTestsCheckBoxes;
};

#endif // CONTRASTTABMIDDLEPARTCONTENT_H
