#include "produit.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>
produit::produit()
{
prix=0; referance=0; nomproduit="";
}

produit::produit(QString nomproduit,int prix,int referance,QDate date)
{this->prix=prix;
this->referance=referance;
this->nomproduit=nomproduit;
this->date=date;}

int produit::getprix(){return prix;}
int produit::getreferance(){return referance;}
QString produit::getnomproduit(){return  nomproduit;}
QDate produit::getdate(){return date;}
void produit::setprix(int prix){this->prix=prix;}
void produit::setreferance(int referance){this->referance=referance;}
void produit::setnomproduit(QString nomproduit){this->nomproduit=nomproduit;}
void produit::setdate(QDate date){this->date=date;}
bool produit::ajouter()
{

    QSqlQuery query;
    QString referance_string= QString::number(referance);
    QString prix_string=QString::number(prix);
         query.prepare("INSERT INTO produit (NOM_PRODUIT, REFERANCE, PRIX, DATE_ACHAT) "
                       "VALUES (:nom_produit,:referance, :prix, :date_achat)");
         query.bindValue(":nom_produit",nomproduit);
         query.bindValue(":referance",referance_string);
         query.bindValue(":prix", prix_string);
         query.bindValue(":date_achat", date);
        return query.exec();

}
QSqlQueryModel* produit::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  /*QSqlQueryModel is a high level of QSqlQuery nestaamlouh l affichage quoi*/


   model->setQuery("SELECT* FROM produit");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("REFERANCE"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
  return  model;
}
bool produit::supprimer(int REFERANCE)
{
    QSqlQuery query;
         query.prepare(" Delete from produit where REFERANCE=:REFERANCE");
         query.bindValue(0, REFERANCE);

        return query.exec();


}
bool produit::modifier(QString nom,int prix,int referance,QDate date)
{
    QSqlQuery query;
    QString sl= QString::number(prix);
    QString res= QString::number(referance);
    query.prepare("update produit set NOM_PRODUIT=:nom_produit,REFERANCE=:referance,PRIX=:prix,DATE_ACHAT=:date where REFERANCE=:referance");
    query.bindValue(":nom_produit",nom);
    query.bindValue(":referance", res);
    query.bindValue(":prix", sl);
    query.bindValue(":date",date);
    return query.exec();
}
QSqlQueryModel * produit::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from produit where ((NOM_PRODUIT || REFERANCE || PRIX || DATE_ACHAT) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("REFERANCE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));

    return model;
}
QSqlQueryModel *  produit::trie(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PRODUIT order by "+critere+" "+mode+"");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("REFERANCE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
    return model;
}
