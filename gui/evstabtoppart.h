#ifndef EVSTABTOPPART_H
#define EVSTABTOPPART_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

class EvsTabTopPart : public QWidget
{
    Q_OBJECT
public:
    explicit EvsTabTopPart(QWidget *parent = 0);
    void setFileName(const QString &fileName);
signals:

public slots:

private:
    QHBoxLayout * layout;
    QLabel * fileLabel;
    QPushButton * loadFileButton;
    QPushButton * clearButton;
};

#endif // EVSTABTOPPART_H
