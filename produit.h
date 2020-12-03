#ifndef PRODUIT_H
#define PRODUIT_H


#include <QString>
#include <QSqlQueryModel>
#include<QThread>
#include<QSound>
#include<QDate>
class produit
{
public:
    produit();
    produit(QString,int,int,QDate);
    int getprix();
    int getreferance();
    QString getnomproduit();
    QDate getdate();
    void setprix(int);
    void setreferance(int);
    void setnomproduit(QString);
    void setdate(QDate);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher (const QString &aux);
    bool supprimer(int);
    bool modifier(QString,int,int,QDate);
    QSqlQueryModel *  trie(const QString &critere, const QString &mode );



private:


    int prix,referance;
    QString nomproduit;
    QDate date;
};



#endif // PRODUIT_H
