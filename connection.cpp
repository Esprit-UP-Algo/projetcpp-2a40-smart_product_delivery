#include "connection.h"
#include<QSqlDatabase>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("project2A");
db.setUserName("haider");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
int Connection::Authentification(int loginn,QString nom)

{

    QSqlDatabase bd = QSqlDatabase::database();



        QSqlQuery query;

        QString log=QString::number(loginn);

        query.prepare("SELECT * FROM MOT_PASS where login=\'"+log+"\' AND mot=\'"+nom+"\'");



        query.exec();

        if (query.next())

        {

             return 1;

        }



        else {

            return 0;

        }
}

