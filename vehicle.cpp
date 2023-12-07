#include "vehicle.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlError>
#include<QSqlQueryModel>

Vehicle::Vehicle()
{
    id = 0;
    make = "";
    model = "";
    datedebut = "";
}

Vehicle::Vehicle(int id, QString make, QString model, QString datedebut)
{
    this->id = id;
    this->make = make;
    this->model = model;
    this->datedebut = datedebut;
}

int Vehicle::getid()
{
    return id;
}

QString Vehicle::getmake()
{
    return make;
}

QString Vehicle::getmodel()
{
    return model;
}

QString Vehicle::getdatedebut()
{
    return datedebut;
}

void Vehicle::setid(int id)
{
    this->id = id;
}

void Vehicle::setmake(QString make)
{
    this->make = make;
}

void Vehicle::setmodel(QString model)
{
    this->model = model;
}

void Vehicle::setdatedebut(QString datedebut)
{
    this->datedebut = datedebut;
}

bool Vehicle::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("INSERT INTO VEHICLE (ID, MAKE, MODEL, DATEDEBUT) "
                  "VALUES (:id, :make, :model, :datedebut)");
    query.bindValue(":id", id);
    query.bindValue(":make", make);
    query.bindValue(":model", model);
    query.bindValue(":datedebut", datedebut);
    return query.exec();
}

bool Vehicle::supprimer(int id)
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("DELETE FROM VEHICLE WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Vehicle::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICLE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("make"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("model"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedebut"));
    return model;
}

bool Vehicle::modifier(int id, QString make, QString model, QString datedebut)
{
    QSqlQuery query;
    query.prepare("UPDATE VEHICLE SET MAKE = :make, MODEL = :model, DATEDEBUT = :datedebut WHERE ID = :id");
    query.bindValue(":id", id);
    query.bindValue(":make", make);
    query.bindValue(":model", model);
    query.bindValue(":datedebut", datedebut);

    if (query.exec())
    {
        return true; // Modification successful
    }
    else
    {
        qDebug() << "Error during modification: " << query.lastError().text();
    }

    return false;
}

QSqlQueryModel* Vehicle::recherche(QString rech)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICLE WHERE ID LIKE '" + rech + "%' OR MAKE LIKE '" + rech + "%'");
    return model;
}

QSqlQueryModel* Vehicle::Find_Vehicle()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID, MAKE, MODEL, DATEDEBUT FROM VEHICLE");

    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Vehicle::triid()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * from VEHICLE ORDER BY ID ");
    return model;
}

QSqlQueryModel* Vehicle::tridatedebut()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * from VEHICLE ORDER BY DATEDEBUT ");
    return model;
}



