/*#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Haider/OneDrive/Documenti/2A40/Projet C++/interface");
    ui->label_pic->setPixmap(pix.scaled(1300,1300,Qt::KeepAspectRatio));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setclient(Client c)
{
    ui->lineEdit_id->setText(c.get_id());
    ui->lineEdit_nom->setText(c.get_nom());
    ui->lineEdit_prenom->setText(c.get_prenom());
    ui->lineEdit_email->setText(c.get_email());
    ui->lineEdit_numerotel->setText(c.get_numerotel());
    ui->lineEdit_adresse->setText(c.get_adresse());
    ui->lineEdit_datenaissance->setText(c.get_datenaissance());
}
*/

