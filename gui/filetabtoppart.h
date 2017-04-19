#ifndef FILETABTOPPART_H
#define FILETABTOPPART_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

class FileTabTopPart : public QWidget
{
    Q_OBJECT
public:
    explicit FileTabTopPart(QWidget *parent = 0);
    void setFileName(const QString &fileName);
signals:

public slots:

private:
    QHBoxLayout * layout;
    QLabel * fileLabel;
    QPushButton * loadFileButton;
    QPushButton * clearButton;
};

#endif // FILETABTOPPART_H
