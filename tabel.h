#ifndef TABEL_H
#define TABEL_H

#include <QTableWidget>

class Tabel : public QTableWidget
{
    Q_OBJECT
public:
    explicit Tabel(QWidget *parent = nullptr);

signals:
};

#endif // TABEL_H
