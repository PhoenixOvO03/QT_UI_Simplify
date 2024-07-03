#include "progresspage.h"

#include "circleprogress.h"

#include <QHBoxLayout>

ProgressPage::ProgressPage(QWidget *parent)
    : QWidget{parent}
{
    CircleProgress* circle1 = new CircleProgress();
    circle1->setFixedSize(200, 200);
    circle1->setPreText("湿度：");
    circle1->setPostText("度");
    circle1->setValue(50);

    CircleProgress* circle2 = new CircleProgress();
    circle2->setFixedSize(200, 200);
    circle2->setPreText("内存：");
    circle2->setPostText("%");
    circle2->setValue(80);

    QHBoxLayout* allLayout = new QHBoxLayout(this);
    allLayout->addWidget(circle1);
    allLayout->addWidget(circle2);
}
