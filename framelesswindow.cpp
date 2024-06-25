#include "framelesswindow.h"
#include "./ui_framelesswindow.h"

#include <QMouseEvent>
#include <windows.h>

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FramelessWindow)
{
    ui->setupUi(this);
    m_resizePadding = 5;
    m_beginMove = false;

    setWindowFlags(Qt::FramelessWindowHint); // 无边框窗口
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon(":/res/Qt.png")); // 标题图标
    ui->TitleImage->setPixmap(QPixmap(":/res/title.png").scaled(200, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 设置属性产生win窗体效果 移动到边缘半屏或者最大化
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
}

FramelessWindow::~FramelessWindow()
{
    delete ui;
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->TitleImage->rect().contains(mapFromGlobal(QCursor().pos())))
    {
        if(event->buttons() & Qt::LeftButton)
        {
            m_pressPos = event->pos();
            m_beginMove = true;
        }
    }
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_beginMove && event->buttons() & Qt::LeftButton)
        move(event->pos() + pos() - m_pressPos);
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_beginMove = false;
}

void FramelessWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (ui->TitleImage->rect().contains(mapFromGlobal(QCursor().pos())))
    {
        if(event->buttons() & Qt::LeftButton)
        {
            if (isMaximized()) showNormal();
            else showMaximized();
        }
    }
}

bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType != "windows_generic_MSG") return QWidget::nativeEvent(eventType, message, result);

    MSG *msg = static_cast<MSG *>(message);

    switch (msg->message)
    {
    case WM_NCCALCSIZE: // 去掉win窗体效果的标题栏
    {
        *result = 0;
        return true;
    }

    case WM_NCHITTEST: // 缩放和移动
    {
        QPoint pos = mapFromGlobal(QCursor().pos()); // 计算鼠标在窗口中的坐标

        //判断当前鼠标位置在哪个区域
        bool left = pos.x() < m_resizePadding;
        bool right = pos.x() > width() - m_resizePadding;
        bool top = pos.y() < m_resizePadding;
        bool bottom = pos.y() > height() - m_resizePadding;

        //鼠标移动到四个角,这个消息是当鼠标移动或者有鼠标键按下时候发出的
        *result = 0;

        // if (left && top) *result = HTTOPLEFT;
        // else if (left && bottom) *result = HTBOTTOMLEFT;
        // else if (right && top) *result = HTTOPRIGHT;
        // else if (right && bottom) *result = HTBOTTOMRIGHT;
        /*else*/ if (left) *result = HTLEFT;
        else if (right) *result = HTRIGHT;
        else if (top) *result = HTTOP;
        else if (bottom) *result = HTBOTTOM;

        // 处理拉伸
        if (0 != *result) {
            return true;
        }

        // 鼠标在标题栏处时拖动产生半屏全屏效果
        if (ui->TitleImage->rect().contains(pos)) {
            *result = HTCAPTION;
            return true;
        }
    }

    default:
        break;
    }

    return false;
}

void FramelessWindow::on_closeBtn_clicked()
{
    this->close();
}

