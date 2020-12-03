#include "connection.h"

Connection::Connection()
{}

bool Connection::ouvrirConnection()
{ db=QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("WALLYS");
db.setUserName("houssem");
db.setPassword("houssi");

if (db.open())
return true;
    return  false;
}

void Connection::fermerConnection()
{db.close();}
