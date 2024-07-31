#include "progresspage.h"

#include "circleprogress.h"

#include <QHBoxLayout>

ProgressPage::ProgressPage(QWidget *parent)
    : QWidget{parent}
{
    CircleProgress* circle1 = new CircleProgress("湿度：", "度");
    circle1->setFixedSize(200, 200);
    circle1->setValue(50);

    CircleProgress* circle2 = new CircleProgress("内存：", "%");
    circle2->setFixedSize(200, 200);
    circle2->setValue(90);

    QHBoxLayout* allLayout = new QHBoxLayout(this);
    allLayout->addWidget(circle1);
    allLayout->addWidget(circle2);
}
