#include "skinpage.h"

#include <QGridLayout>
#include <QMouseEvent>

SkinPage::SkinPage(QWidget *parent)
    : QWidget{parent}
{
    // 成员初始化
    member << new SkinItem("#c0444444", "#c0444444");
    member << new SkinItem("#c0444444", "#c0ffffff");
    member << new SkinItem("#c0444444", "#c080d080");
    member << new SkinItem("#c0444444", "#c0daa520");
    member << new SkinItem("#c0444444", "#c087ceeb");
    member << new SkinItem("#c0444444", "#c0ffd0d0");

    QGridLayout* mainLayout = new QGridLayout(this);

    int i = 0; // 用于划分行列
    for (const auto& item : member) // 槽函数连接及加入布局
    {
        connect(item, &SkinItem::clicked, this, [&](){
            emit selectSkin(item->topColor(), item->bottomColor());
        });

        mainLayout->addWidget(item, i / 3, i % 3);
        ++i;
    }
}

SkinItem::SkinItem(QString topColor, QString bottomColor)
    : m_topColor(topColor)
    , m_bottomColor(bottomColor)
{
    setFixedSize(200, 200);
    setAttribute(Qt::WA_StyledBackground); // 启用 QSS

    QString styleSheet =
        QString(
            "background-color: qlineargradient("
                "spread:pad, "
                "x1:0, y1:0, x2:0, y2:1, "
                "stop:0 %1, "
                "stop:1 %2);"
            "border: 1px solid white;"
            "border-color: rgba(255, 255, 255, 128);"
            "border-radius: 10px;").arg(m_topColor, m_bottomColor);
    setStyleSheet(styleSheet);
}
