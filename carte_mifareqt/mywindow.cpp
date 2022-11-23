#include "mywindow.h"
#include "ui_mywindow.h"
#include "MfErrNo.h""
#include "Core.h"
#include "Sw_Device.h"
#include "Sw_Mf_Classic.h"
#include "Sw_Poll.h"
#include "Sw_ISO14443A-3.h"
#include "TypeDefs.h"
#include "Tools.h"

#include <QtGui>


MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWindow)
{
    ui->setupUi(this);
}

MyWindow::~MyWindow()
{
    delete ui;
}

ReaderName lecteur;

void MyWindow::on_Connect_clicked()
{
    int16_t status=MI_OK;
    lecteur.Type=ReaderCDC;
    lecteur.device=0;

    status=OpenCOM(&lecteur);
    qDebug()<<"Salut bg"<<status;
    status=Version(&lecteur);
    ui->Display->setText(lecteur.version);
    ui->Display->update();
}

void MyWindow::on_Exit_clicked()
{
    int16_t status = MI_OK;
    RF_Power_Control(&lecteur, FALSE, 0);
    status=LEDBuzzer(&lecteur, LED_OFF);
    status=CloseCOM(&lecteur);
    qApp->quit();
}
