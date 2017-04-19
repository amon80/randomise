#ifndef FILETAB_H
#define FILETAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include "filetabtoppart.h"

class FileTab : public QWidget
{
    Q_OBJECT
public:
    explicit FileTab(QWidget *parent = 0);
    void setFileName(const QString& filename);
signals:
    void openVmp();
    void clearAll();
public slots:
private:
    QVBoxLayout * layout;
    FileTabTopPart * top;
};

#endif // FILETAB_H
