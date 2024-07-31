#include "framelesswindow.h"
#include "./ui_framelesswindow.h"
#include "util/compositionwindoweffect.h"

#include <windows.h>
#include <QPropertyAnimation>
#include <QDesktopServices>
#include <QFile>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QGraphicsBlurEffect>
#include <QScreen>
#include <QPainter>

FramelessWindow::FramelessWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FramelessWindow)
{
    ui->setupUi(this);
    // 数据初始化
    m_resizePadding = 5;
    m_pageIndex = PagesIndex::ButtonsPage;
    m_isOnTop = false;

    // 窗口设置
    setWindowFlags(Qt::FramelessWindowHint); // 无边框窗口
    setAttribute(Qt::WA_TranslucentBackground); // 透明窗口
    setWindowIcon(QIcon(":/res/Qt.png")); // 标题图标

    uiStyleInit(); // 初始化ui界面样式
    uiConnectInit(); // ui各控件槽函数连接
    trayIconInit(); // 托盘图标初始化

    // 设置属性产生win窗体效果 移动到边缘半屏或者最大化
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

    // 毛玻璃效果
    CompositionWindowEffect::setAreoEffect((HWND)(hwnd));
}

FramelessWindow::~FramelessWindow()
{
    delete ui;
}

void FramelessWindow::setBackgroundColor(QString topColor, QString bottomColor)
{
    QFile qss(":/qss/setTheme.qss");
    qss.open(QFile::ReadOnly);
    QString styleSheet = QString(qss.readAll()).arg(topColor, bottomColor);
    qss.close();
    ui->centralwidget->setStyleSheet(styleSheet);
}

void FramelessWindow::setPageIndex(int index)
{
    if (index == PagesIndex::SkinPage)
    {
        if (ui->body->currentIndex() == PagesIndex::SkinPage) setPageIndex(m_pageIndex); // 恢复页面
        else ui->body->setCurrentIndex(index); // 打开主题页面
    }
    else
    {
        ui->body->setCurrentIndex(index);
        m_pageIndex = index;
    }
}

void FramelessWindow::setOnTop()
{
    if (m_isOnTop) // 设置为不置顶
    {
        ui->onTopBtn->setStyleSheet("QPushButton#onTopBtn{border-image: url(:/res/onTopOff.png);}");
        ::SetWindowPos(HWND(this->winId()),HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }
    else // 设置为置顶
    {
        ui->onTopBtn->setStyleSheet("QPushButton#onTopBtn{border-image: url(:/res/onTopOn.png);}");
        ::SetWindowPos(HWND(this->winId()),HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }

    m_isOnTop = !m_isOnTop;
}

void FramelessWindow::uiStyleInit()
{
    // 窗口初始化
    ui->body->setCurrentIndex(PagesIndex::ButtonsPage);
    ui->titleImage->setPixmap(QPixmap(":/res/title.png").scaled(200, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setBackgroundColor("#c0444444", "#c0444444");

    // 控件资源初始化
    QFile qss(":/qss/windowControl.qss");
    qss.open(QFile::ReadOnly);
    QString styleSheet = qss.readAll();
    qss.close();
    setStyleSheet(styleSheet);

    // 窗口置顶按钮
    ui->onTopBtn->setStyleSheet("QPushButton#onTopBtn{border-image: url(:/res/onTopOff.png);}");
}

void FramelessWindow::uiConnectInit()
{
    // 主题
    connect(ui->skinPage, &SkinPage::selectSkin, this, &FramelessWindow::setBackgroundColor);
    // 标题栏
    connect(ui->minBtn, &QPushButton::clicked, this, &FramelessWindow::showMinimized);
    // connect(ui->closeBtn, &QPushButton::clicked, this, &FramelessWindow::close);
    connect(ui->closeBtn, &QPushButton::clicked, this, [&](){
        QMessageBox quitBox;
        quitBox.setWindowTitle("退出");
        quitBox.setText("最小化到系统托盘或退出程序");
        quitBox.addButton("最小化", QMessageBox::ActionRole);
        quitBox.addButton("关闭", QMessageBox::ActionRole);
        quitBox.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

        quitBox.setStyleSheet("QMessageBox,QPushButton{"
                              "color: white;"
                              "background-color: #c0444444;"
                              "border: 1px solid white;"
                              "border-color: white;"
                              "}"
                              "QLabel{"
                              "color: white;"
                              "}");

        int ret = quitBox.exec();
        if (ret == 0) hide();
        else close();
    });
    // 侧边栏
    connect(ui->bilibiliBtn, &QPushButton::clicked, this, [&](){QDesktopServices::openUrl(QUrl("https://space.bilibili.com/387426555"));});
    connect(ui->buttonsPageBtn, &QPushButton::clicked, this, [&](){this->setPageIndex(PagesIndex::ButtonsPage);});
    connect(ui->progressPageBtn, &QPushButton::clicked, this, [&](){this->setPageIndex(PagesIndex::ProgressPage);});
    connect(ui->tablePageBtn, &QPushButton::clicked, this, [&](){this->setPageIndex(PagesIndex::TablePage);});
    connect(ui->skinBtn, &QPushButton::clicked, this, [&](){this->setPageIndex(PagesIndex::SkinPage);});
    connect(ui->onTopBtn, &QPushButton::clicked, this, &FramelessWindow::setOnTop);
}

void FramelessWindow::trayIconInit()
{
    // 显示
    QAction* showAction = new QAction(QStringLiteral("显示"));
    connect(showAction, &QAction::triggered, this, &FramelessWindow::show);
    // 退出
    QAction* exitAction = new QAction(QStringLiteral("退出"));
    connect(exitAction , &QAction::triggered, this, &QApplication::exit);

    // 初始化菜单并添加项
    QMenu* trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addAction(exitAction );

    //创建一个系统托盘
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/res/Qt.png"));
    m_trayIcon->setContextMenu(trayMenu);
    m_trayIcon->show();
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

        if (left) *result = HTLEFT;
        else if (right) *result = HTRIGHT;
        else if (top) *result = HTTOP;
        else if (bottom) *result = HTBOTTOM;

        if (0 != *result) // 处理拉伸
        {
            return true;
        }

        if (ui->titleImage->geometry().contains(pos)) // 鼠标在标题栏处时拖动产生半屏全屏效果
        // if (ui->TitleImage->rect().contains(pos))
        {
            *result = HTCAPTION;
            return true;
        }
    }

    default:
        break;
    }

    return QWidget::nativeEvent(eventType, message, result);
}
