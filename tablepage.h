#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <QWidget>

class Tabel;

class TablePage : public QWidget
{
    Q_OBJECT
public:
    explicit TablePage(QWidget *parent = nullptr);

signals:

private:
    Tabel* m_tabel;
};

#endif // TABLEPAGE_H
