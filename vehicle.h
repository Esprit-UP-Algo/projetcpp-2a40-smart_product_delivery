#ifndef VEHICLE_H
#define VEHICLE_H
#include <QString>
#include <QSqlQueryModel>


class Vehicle
{
public:
    Vehicle();
    Vehicle(int,QString,QString,QString);
    int getid();
    QString getmake();
    QString getmodel();
    QString getdatedebut();
    void setid(int id);
    void setmake(QString make);
    void setmodel(QString model);
    void setdatedebut(QString datedebut);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int id , QString make, QString model,QString datedebut);
     QSqlQueryModel * triid();
     QSqlQueryModel * recherche(QString rech);
     QSqlQueryModel* Find_Vehicle();
     QSqlQueryModel * tridatedebut();



private:
    int id;

    QString make,datedebut,model;

};

#endif //VEHICLE_H
