#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.ouvrirConnection();

    MainWindow w;
    w.show();

         if(test)
         {

             w.show();
             QMessageBox::information(nullptr, QObject::tr("database is open"),
                         QObject::tr("connection successful.\n""Click Cancel to exit."), QMessageBox::Ok);

             // qDebug()<<"Connection successful";
         }
         else

             QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                         QObject::tr("connection failed.\n""Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}
