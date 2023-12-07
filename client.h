#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>
#include <QDate>
class Client
{
public:
    Client();
     Client (int,int,QString,QString,QString,QString,QDate,int);
     int getcin();
     int getNum();
     QString getnom();
     QString getprenom();
     QString getMail();
     QString getAdresse();
     QDate getdate_naissance();
     int getnombre_dachats();




    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setMail(QString);
    void setNum(int);
    void setAdresse(QString);
    void setdate_naissance(QDate);
    void setnombre_dachats(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int cin);
    bool rechercherParAdresse(QString Adresse);
    bool modifier(int cin, QString nouveauNom, QString nouveauPrenom, QString nouveauMail, int nouveauNum, QString nouveauAdresse);
    Client(int cin,QString nom,QString prenom,QString Mail, int Num, QString Adresse, QDate date_naissance, int nombre_dachats);
     QSqlQueryModel* trinAchats();

private:
    int cin,Num,nombre_dachats;
    QString nom,prenom,Mail,Adresse;
    QDate date_naissance;
};

#endif // CLIENT_H
