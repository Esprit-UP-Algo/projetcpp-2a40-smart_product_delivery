#include "connection.h"
#include <QtSql>
connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("delivery");
db.setUserName("oussema");
db.setPassword("esprit18");
if (db.open())
{test=true;
}
return test;
}
