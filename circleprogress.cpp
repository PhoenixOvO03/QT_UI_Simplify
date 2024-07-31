#include "circleprogress.h"

#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

CircleProgress::CircleProgress(QWidget *parent)
    : QWidget{parent}
{
    // 初始化值
    m_value = 0;
    m_currProgress = 0;
    m_preText = "";
    m_postText = "";

    // 动画的初始化
    m_animation = new QPropertyAnimation(this);
    m_animation->setTargetObject(this);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_animation->setDirection(QVariantAnimation::Forward);
    m_animation->setDuration(1000);

    // 数值改变触发绘制函数
    connect(m_animation, &QPropertyAnimation::valueChanged, this, [&](const QVariant& value){
        m_currProgress = value.toInt();
        // 越界
        if (m_currProgress < 0) m_currProgress = 0;
        if (m_currProgress > 100) m_currProgress = 100;
        update();
    });
}

CircleProgress::CircleProgress(QString preText, QString postText, QWidget *parent)
    : CircleProgress(parent)
{
    m_preText = preText;
    m_postText = postText;
}

void CircleProgress::setValue(int value)
{
    // 越界
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    m_value = value;
    // 中止当前动画
    m_animation->stop();
    // 开始新的动画
    m_animation->setStartValue(m_currProgress);
    m_animation->setEndValue(value);
    m_animation->start();
}

void CircleProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    // 绘制各个部分
    paintGray(painter);
    paintProgress(painter);
    paintText(painter);
}

void CircleProgress::paintGray(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(QBrush(Qt::gray), 20, Qt::SolidLine, Qt::RoundCap));
    QRect rectangle = rect();
    rectangle.adjust(10, 10, -10, -10);
    painter.drawArc(rectangle, -210 * 16, -300 * 16);
    painter.restore();
}

void CircleProgress::paintProgress(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(QBrush(m_currProgress > 80 ? Qt::red : Qt::green), 10, Qt::SolidLine, Qt::RoundCap));
    QRect rectangle = rect();
    rectangle.adjust(10, 10, -10, -10);
    painter.drawArc(rectangle, -210 * 16, m_currProgress * -16 * 3);
    painter.restore();
}

void CircleProgress::paintText(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::green);
    painter.setFont(QFont("华文彩云", 20));
    painter.drawText(rect(), Qt::AlignVCenter, QString("%1%2%3").arg(m_preText).arg(m_currProgress).arg(m_postText));
    painter.restore();
}
