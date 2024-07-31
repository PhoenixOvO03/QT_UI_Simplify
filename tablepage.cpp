#include "tablepage.h"

#include "tabel.h"

#include <QLabel>
#include <QGridLayout>

TablePage::TablePage(QWidget *parent)
    : QWidget{parent}
{
    m_tabel = new Tabel();

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(m_tabel);
}
