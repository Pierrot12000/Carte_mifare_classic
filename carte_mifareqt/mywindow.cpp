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
#include <QPixmap>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Pierre/Documents/Esirem/carte mifare/Carte_mifare_classic/mifare.jpg");
    int w=ui->label_card->width();
    int h=ui->label_card->height();
    ui->label_card->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
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
    status=Version(&lecteur);
    if(status!=MI_OK)
    {
        ui->Display->setText("Reader not found");
    }
    else
    {
        ui->Display->setText(lecteur.version);
        status = LEDBuzzer(&lecteur, LED_RED_ON);
    }
    RF_Power_Control(&lecteur, TRUE, 0);
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

void MyWindow::on_Disconnect_clicked()
{
    int16_t status = MI_OK;
    status=LEDBuzzer(&lecteur, LED_OFF);
    status=CloseCOM(&lecteur);
    ui->Display->setText("Succesfully disconnected");
}

void MyWindow::on_Read_clicked()
{
    uint8_t data[240] = {0};
    uint32_t data2=0;

    int16_t status = 0;
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;

    memset(data, 0x00, 240);
    status = ISO14443_3_A_PollCard(&lecteur, atq, sak, uid, &uid_len);
    status = Mf_Classic_Read_Block(&lecteur, TRUE, 10, data, AuthKeyA, 2);
    ui->Nom->setText((char*)data);
    status = Mf_Classic_Read_Block(&lecteur, TRUE, 9, data, AuthKeyA, 2);
    ui->Prenom->setText((char*)data);
    status=Mf_Classic_Read_Value(&lecteur, TRUE, 14, &data2, AuthKeyA, 3);
    ui->Money->display(QString::number(data2));

    status=LEDBuzzer(&lecteur, BUZZER_ON);
    status=LEDBuzzer(&lecteur, LED_RED_ON);
    DELAYS_MS(50);
    status=LEDBuzzer(&lecteur, BUZZER_OFF);
}

void MyWindow::on_Set_name_clicked()
{
    char nom[16];
    char prenom[16];
    int16_t status = 0;

    strncpy(nom, ui->Nom->toPlainText().toUtf8().data(), 16);
    status = Mf_Classic_Write_Block(&lecteur, TRUE, 10, (uint8_t*) nom, AuthKeyB, 2);
    strncpy(prenom, ui->Prenom->toPlainText().toUtf8().data(), 16);
    status = Mf_Classic_Write_Block(&lecteur, TRUE, 9, (uint8_t*) prenom, AuthKeyB, 2);

    status=LEDBuzzer(&lecteur, BUZZER_ON);
    status=LEDBuzzer(&lecteur, LED_RED_ON);
    DELAYS_MS(50);
    status=LEDBuzzer(&lecteur, BUZZER_OFF);
}

void MyWindow::on_add_clicked()
{
    int16_t status = 0;
    uint32_t data2=0;
    status=Mf_Classic_Increment_Value(&lecteur, TRUE, 14, ui->spin_Money->value(), 13, AuthKeyB, 3); //on prend la valeur du block 14, on incrémente et on écrit dans le bloc 13
    status=Mf_Classic_Restore_Value(&lecteur, TRUE, 13, 14, AuthKeyA, 3); //on prend la valeur dans le backup pour la mettre dans le compteur
    status=Mf_Classic_Read_Value(&lecteur, TRUE, 14, &data2, AuthKeyA, 3);
    ui->Money->display(QString::number(data2));

    status=LEDBuzzer(&lecteur, BUZZER_ON);
    status=LEDBuzzer(&lecteur, LED_RED_ON);
    DELAYS_MS(50);
    status=LEDBuzzer(&lecteur, BUZZER_OFF);
}

void MyWindow::on_withdraw_clicked()
{
    int16_t status = 0;
    uint32_t data2=0;
    status=Mf_Classic_Decrement_Value(&lecteur, TRUE, 14, ui->spin_Money->value(), 13, AuthKeyA, 3);
    status=Mf_Classic_Restore_Value(&lecteur, TRUE, 13, 14, AuthKeyA, 3);
    status=Mf_Classic_Read_Value(&lecteur, TRUE, 14, &data2, AuthKeyA, 3);
    ui->Money->display(QString::number(data2));

    status=LEDBuzzer(&lecteur, BUZZER_ON);
    status=LEDBuzzer(&lecteur, LED_RED_ON);
    DELAYS_MS(50);
    status=LEDBuzzer(&lecteur, BUZZER_OFF);
}
