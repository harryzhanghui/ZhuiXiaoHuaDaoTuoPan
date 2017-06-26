#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ZhuiXiaoHuaDaoTuoPan();
}


void Widget::ZhuiXiaoHuaDaoTuoPan()
{
    //隐藏主窗口
    this->hide();

    //新建QSystemTrayIcon对象
    mSysTrayIcon = new QSystemTrayIcon(this);
    //新建托盘要显示的icon
    //QIcon icon = QIcon("../IMClient/Resources/GG.png");
     QIcon icon = QIcon("C:/QTtest/ZhuiXiaoHuaDaoTuoPan/GG.png");
    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip(QObject::trUtf8("测试系统托盘图标"));
    //给QSystemTrayIcon添加槽函数
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    //建立托盘操作的菜单
    createActions();
    createMenu();
    //在系统托盘显示此对象
    mSysTrayIcon->show();
}

void Widget::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        mSysTrayIcon->showMessage(QObject::trUtf8("Message Title"),
                                        QObject::trUtf8("欢迎使用此程序"),
                                        QSystemTrayIcon::Information,
                                        1000);
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        //双击后显示主程序窗口
        this->show();
        break;
    default:
        break;
    }
}

void Widget::createActions()
{
    mShowMainAction = new QAction(QObject::trUtf8("显示主界面"),this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));

    mExitAppAction = new QAction(QObject::trUtf8("退出"),this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));

}
void Widget::createMenu()
{
    mMenu = new QMenu(this);
    //新增菜单项---显示主界面
    mMenu->addAction(mShowMainAction);
    //增加分隔符
    mMenu->addSeparator();
    //新增菜单项---退出程序
    mMenu->addAction(mExitAppAction);
    //把QMenu赋给QSystemTrayIcon对象
    mSysTrayIcon->setContextMenu(mMenu);
}
/*
* 当在系统托盘点击菜单内的显示主界面操作
*/
void Widget::on_showMainAction()
{
    this->show();
}

/*
* 当在系统托盘点击菜单内的退出程序操作
*/
void Widget::on_exitAppAction()
{
    exit(0);
}

//最小化到托盘----第一种写法
//void Widget::changeEvent(QEvent *event)
//{
//    if(event->type()!=QEvent::WindowStateChange) return;
//    if(this->windowState()==Qt::WindowMaximized)
//    {
//       //................//需要处理的功能
//    }
//    if(this->windowState()==Qt::WindowMinimized)
//    {
//       ZhuiXiaoHuaDaoTuoPan();
//    }
//}


//最小化到托盘----第二种写法
void Widget::changeEvent(QEvent *e)
{
    if((e->type()==QEvent::WindowStateChange)&&this->isMinimized())
    {
        ZhuiXiaoHuaDaoTuoPan();
       // QTimer::singleShot(100, this, SLOT(close()));
    }
}


//关闭到托盘---------
void Widget::closeEvent(QCloseEvent *e)
{
    e->ignore();
    this->hide();
}











