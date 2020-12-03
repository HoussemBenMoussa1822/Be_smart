#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H


#include <QString>
#include <QSqlQueryModel>
#include<QThread>
#include<QSound>
#include<QDate>
class fournisseurs
{
public:
    fournisseurs();
    fournisseurs(QString,QString,int);
    QString getnomsociete();
    QString getadresse();
    int getnumtel();
    void setnomsociete(QString);
    void setadresse(QString);
    void setnumtel(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(const QString &aux);
    bool supprimer(QString);
    bool modifier(QString,QString,int);
    QSqlQueryModel* trie(const QString &critere, const QString &mode );



private:


    int numtel;
    QString nomsociete,adresse;
};



#endif // FOURNISSEURS_H
