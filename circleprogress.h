#ifndef CIRCLEPROGRESS_H
#define CIRCLEPROGRESS_H

#include <QWidget>

class QPropertyAnimation;

class CircleProgress : public QWidget
{
    Q_OBJECT
public:
    explicit CircleProgress(QWidget *parent);
    explicit CircleProgress(QString preText = "", QString postText = "", QWidget* parent = nullptr);

    void setValue(int value);
    inline void setPreText(QString preText){m_preText = preText;}
    inline void setPostText(QString postText){m_postText = postText;}

protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    void paintGray(QPainter& painter); // 绘制灰色底槽
    void paintProgress(QPainter& painter); // 绘制进度条
    void paintText(QPainter& painter); // 绘制中心文字

private:
    int m_value; // 目标值
    int m_currProgress; // 当前动画值
    QString m_preText; // 前缀文字
    QString m_postText; // 后缀文字

    QPropertyAnimation* m_animation;    // 动画
};

#endif // CIRCLEPROGRESS_H
