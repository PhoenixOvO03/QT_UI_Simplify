#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class QSystemTrayIcon;

QT_BEGIN_NAMESPACE
namespace Ui {
class FramelessWindow;
}
QT_END_NAMESPACE

// 无边框窗口
class FramelessWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum PagesIndex{
        SkinPage,
        ButtonsPage,
        ProgressPage,
        TablePage,
    };

public:
    FramelessWindow(QWidget *parent = nullptr);
    ~FramelessWindow();

    void setBackgroundColor(QString topColor, QString bottomColor); // 设置背景颜色
    void setPageIndex(int index); // 设置当前显示页面
    void setOnTop(); // 设置窗口置顶

private:
    void uiStyleInit(); // ui控件样式初始化
    void uiConnectInit(); // ui控件槽函数连接
    void trayIconInit(); // 系统托盘图标初始化

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result); // 重写Windows消息

private:
    Ui::FramelessWindow *ui;

    QPoint m_pressPos; // 点击位置
    int m_resizePadding; // 拉伸边缘宽度
    int m_pageIndex; // 存储除了皮肤页面的当前页号
    bool m_isOnTop; // 当前是否置顶

    QSystemTrayIcon* m_trayIcon; // 托盘图标
};
#endif // FRAMELESSWINDOW_H
