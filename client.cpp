#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
Client::Client()
{
 cin=0;
 nom=" ";
 prenom=" ";
 Mail=" ";
 Num=0;
 Adresse=" ";
 date_naissance = QDate::currentDate();
 nombre_dachats=0;

}

Client::Client(int cin,QString nom,QString prenom,QString Mail, int Num, QString Adresse,QDate date_naissance, int nombre_dachats)
{this->cin=cin; this->nom=nom; this->prenom=prenom;this->Mail=Mail;this->Num=Num;this->Adresse=Adresse;this->date_naissance=date_naissance;this->nombre_dachats=nombre_dachats;}
int Client::getcin(){return cin;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getMail(){return Mail;}
int Client::getNum(){return Num;}
QString Client::getAdresse(){return Adresse;}
QDate Client::getdate_naissance(){return date_naissance;}
int Client::getnombre_dachats(){return nombre_dachats;}

void Client::setcin(int cin){this->cin=cin;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setMail(QString Mail){this->Mail=Mail;}
void Client::setNum(int Num){this->Num=Num;}
void Client::setAdresse(QString Adresse){this->Adresse=Adresse;}
void Client::setdate_naissance(QDate date_naissance){this->date_naissance=date_naissance;}
void Client::setnombre_dachats(int nombre_dachats){this->nombre_dachats=nombre_dachats;}
bool Client::ajouter()
{
   QSqlQuery query;
  // QString cin_string=QString::number(cin);
        query.prepare("INSERT INTO GS_CLIENT (cin, nom, prenom,Mail,Num,Adresse, DATE_NAISSANCE , NOMBRE_DACHATS) VALUES (:cin, :forename, :surname, :Mail, :Num, :Adresse, :date_naissance, :nombre_dachats)");
        query.bindValue(":cin", cin);
        query.bindValue(":forename", nom);
        query.bindValue(":surname", prenom);
         query.bindValue(":Mail", Mail);
          query.bindValue(":Num", Num);
          query.bindValue(":Adresse", Adresse);
          query.bindValue(":date_naissance", date_naissance);
          query.bindValue(":nombre_dachats", nombre_dachats);

        //query.exec();
   return query.exec();
}

bool Client::supprimer(int cin)
{
   QSqlQuery query;

        query.prepare("DELETE FROM GS_CLIENT WHERE CIN=:cin");
        query.bindValue(":cin", cin);

   return query.exec();
}

QSqlQueryModel* Client::afficher()
{


   QSqlQueryModel* model= new QSqlQueryModel();

         model->setQuery("SELECT * FROM GS_CLIENT");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("ACCESS_STATUS"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
         model->setHeaderData(8, Qt::Horizontal, QObject::tr("NOMBRE_DACHATS"));
         return model;
}
/*bool Client::modifier()
{
   QSqlQuery query;
  // QString cin_string=QString::number(cin);
        query.prepare("UPDATE CLIENTS SET ( nom=:forename, prenom=:surname,nAchats=:nAchats, Mail=:Mail,  cin=:cin,Num=:Num)");
        query.bindValue(":cin", cin);
         query.bindValue(":nAchats", nAchats);
          query.bindValue(":Num", Num);
        query.bindValue(":forename", nom);
        query.bindValue(":surname", prenom);
         query.bindValue(":Mail", Mail);
        //query.exec();
   return query.exec();
}*/

bool Client::modifier(int cin, QString nouveauNom, QString nouveauPrenom, QString nouveauMail, int nouveauNum, QString nouveauAdresse)
{

       QSqlQuery query;

       query.prepare("UPDATE FOURNISSEUR SET NOM = :nouveauNom, PRENOM = :nouveauPrenom, WHERE ID cin =:cin");
       if (!nouveauNom.isEmpty() && !nouveauPrenom.isEmpty()) {
                   query.bindValue(":cin", cin);
                   query.bindValue(":nouveauNom", nouveauNom);
                   query.bindValue(":nouveauPrenom", nouveauPrenom);
                   query.bindValue(":nouveauMail", nouveauMail);
                   query.bindValue(":nouveauNum", nouveauNum);
                   query.bindValue(":nouveauAdresse", nouveauAdresse);

                   if (query.exec())
                   {
                       return true; // La modification a réussi
                   }
                   else
                   {
                       qDebug() << "Erreur lors de la modification : " << query.lastError().text();
                   }
               }

   return false;
}

QSqlQueryModel * Client::trinAchats()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM GS_CLIENT ORDER BY NOM ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));

    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ACCESS_STATUS"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("NOMBRE_DACHATS"));
    return model;
}
/*
int Client::getNombreClientsParMois(float mois)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE EXTRACT(MONTH FROM DateN) = :mois");
    query.bindValue(":mois", mois);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}
*/



bool Client::rechercherParAdresse(QString Adresse)
{
   QSqlQuery query;
   query.prepare("SELECT * FROM GS_CLIENT WHERE Adresse = :Adresse");
   query.bindValue(":Adresse", Adresse);

   if (query.exec() && query.next()) {

       return true;
   } else {

       return false;
   }
}

/*
bool Client::modifier(int cin, QString nouveauNom, QString nouveauPrenom)
{
   QSqlQuery query;
   query.prepare("UPDATE CLIENTS SET nom = :nom, prenom = :prenom WHERE cin = :cin");
   query.bindValue(":cin", cin);
   query.bindValue(":nom", nouveauNom);
   query.bindValue(":prenom", nouveauPrenom);

   return query.exec();
}*/

