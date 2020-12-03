#include "fournisseurs.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>
fournisseurs::fournisseurs()
{
nomsociete=""; adresse=""; numtel=0;
}

fournisseurs::fournisseurs(QString nomsociete,QString adresse,int numtel)
{this->nomsociete=nomsociete;
this->adresse=adresse;
this->numtel=numtel;}

QString fournisseurs::getnomsociete(){return nomsociete;}
QString fournisseurs::getadresse(){return adresse;}
int fournisseurs::getnumtel(){return numtel;}
void fournisseurs::setnomsociete(QString nomsociete){this->nomsociete=nomsociete;}
void fournisseurs::setadresse(QString adresse){this->adresse=adresse;}
void fournisseurs::setnumtel(int numtel){this->numtel=numtel;}
bool fournisseurs::ajouter()
{

    QSqlQuery query;
    QString Numtel_string= QString::number(numtel);
         query.prepare("INSERT INTO FOURNISSEUR (NOM_SOCIETE, ADRESSE, NUMTEL) "
                       "VALUES (:nom_societe,:adresse, :numtel)");
         query.bindValue(":nom_societe",nomsociete);
         query.bindValue(":adresse",adresse);
         query.bindValue(":numtel", Numtel_string);
        return query.exec();

}
QSqlQueryModel* fournisseurs::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  /*QSqlQueryModel is a high level of QSqlQuery nestaamlouh l affichage quoi*/


   model->setQuery("SELECT* FROM fournisseur");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_SOCIETE"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMTEL"));
  return  model;
}
bool fournisseurs::supprimer(QString NOM_SOCIETE)
{
    QSqlQuery query;
         query.prepare(" Delete from fournisseur where NOM_SOCIETE=:NOM_SOCIETE");
         query.bindValue(0, NOM_SOCIETE);

        return query.exec();


}
bool fournisseurs::modifier(QString nomsociete,QString adresse,int numtel)
{
    QSqlQuery query;
    QString sl= QString::number(numtel);
    query.prepare("update FOURNISSEUR set ADRESSE=:adresse,NUMTEL=:numtel where NOM_SOCIETE=:nomsociete");
    query.bindValue(":adresse", adresse);
    query.bindValue(":numtel", sl);
    query.bindValue(":nomsociete",nomsociete);
    return query.exec();
}
QSqlQueryModel* fournisseurs::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from FOURNISSEUR where ((NOM_SOCIETE || ADRESSE || NUMTEL) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_SOCIETE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMTEL"));


    return model;
}

QSqlQueryModel*  fournisseurs::trie(const QString &critere, const QString &mode )
{
    QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("select * from FOURNISSEUR order by "+critere+" "+mode+"");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_SOCIETE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMTEL"));
    return model;
}
