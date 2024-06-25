#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FramelessWindow;
}
QT_END_NAMESPACE

class FramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    FramelessWindow(QWidget *parent = nullptr);
    ~FramelessWindow();

protected:
    // 拖拽
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event); // 双击最大化或正常化
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result); // 拖拽大小、停靠屏幕边缘半屏或全屏

private slots:
    void on_closeBtn_clicked();

private:
    Ui::FramelessWindow *ui;

    QPoint m_pressPos; // 点击位置
    int m_resizePadding; // 拉伸边缘宽度
    bool m_beginMove; // 开始移动
};
#endif // FRAMELESSWINDOW_H
