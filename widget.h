#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void ZhuiXiaoHuaDaoTuoPan();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void createActions();
    void createMenu();
    void on_showMainAction();
    void on_exitAppAction();
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *e);
private:
    Ui::Widget *ui;
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
};

#endif // WIDGET_H
