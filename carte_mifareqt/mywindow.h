#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWindow; }
QT_END_NAMESPACE

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

private slots:
    void on_Connect_clicked();
    void on_Exit_clicked();
    void on_Disconnect_clicked();
    void on_Read_clicked();
    void on_Set_name_clicked();
    void on_add_clicked();
    void on_withdraw_clicked();
private:
    Ui::MyWindow *ui;
};
#endif // MYWINDOW_H
