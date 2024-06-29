#ifndef SKINPAGE_H
#define SKINPAGE_H

#include <QWidget>
#include <QPushButton>

// 主题元素
class SkinItem : public QPushButton
{
    Q_OBJECT
public:
    explicit SkinItem(QString topColor, QString bottomColor);
    inline QString topColor(){return m_topColor;}
    inline QString bottomColor(){return m_bottomColor;}

private:
    QString m_topColor;
    QString m_bottomColor;
};

// 主题页面
class SkinPage : public QWidget
{
    Q_OBJECT
public:
    explicit SkinPage(QWidget *parent = nullptr);

signals:
    void selectSkin(QString topColor, QString bottomColor);

private:
    QList<SkinItem*> member;
};

#endif // SKINPAGE_H
