#include "login.h"
#include "ui_login.h"
#include "connection.h"
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
void login::on_pb_seconnecter_clicked()
{
     //MainWindow w;
     Connection  c;
     QString nom=ui->nom->text();;
     int loginn=ui->password->text().toInt();

     if(c.Authentification(loginn,nom)==1)
     {
        QMessageBox::information(this,"Connexion","login et mdp correcte");
      qDebug()<< "Mot de passe et login correct";

      this->hide();
      //w.show();
      MainWindow* me = new MainWindow(this);

     me->show();

 }
     if(c.Authentification(loginn,nom)==0)
     {
       QMessageBox::critical(this,"Connexion","login et mdp incorrecte");
       qDebug()<< "Mot de passe et login incorrect";
     }
}
