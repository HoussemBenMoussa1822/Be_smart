#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QComboBox>
#include <QTabWidget>
#include <QObject>
#include <QSqlTableModel>
#include <QPrinter>
#include <QPrintDialog>
#include<QPropertyAnimation>
#include<QEasingCurve>
#include<QParallelAnimationGroup>
#include<QGraphicsOpacityEffect>
#include<QSound>
#include <QtMultimedia>
#include<QWidget>
#include<QMediaPlayer>
#include<QDate>
#include <QTextDocument>
#include <QTextStream>
#include<QMenu>
#include<QDialogButtonBox>
#include "produit.h"
#include "fournisseurs.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_3_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*CRUD AJOUTER*/
    int prix=ui->le_prix->text().toInt();
    int referance=ui->le_referrance->text().toInt();
    QString nomproduit=ui->le_nom->text();
     QDate date=ui->dateEdit->date();
     produit P(nomproduit,prix,referance,date);

 bool test=P.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView->setModel(P.afficher());
 }
 else
 {
         const int DeltaPos = 10;

         QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
         animation->setDuration(500);

         if (ui->stackedWidget->currentIndex() == 0) {
            /* Animation mainwindow*/
             int oldX = pos().x();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.1, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.2, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.3, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.4, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.5, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.6, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.7, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.8, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.9, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(1.0, QPoint(oldX, pos().y()));
         } else {
             int oldY = pos().y();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.1, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.2, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.3, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.4, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.5, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.6, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.7, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.8, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.9, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(1.0, QPoint(pos().x(), oldY));
         }
         animation->start(QAbstractAnimation::DeleteWhenStopped);
         /*message d'erreur*/
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}
}

void MainWindow::on_supprimer_pb_clicked()
{
    /*sound */

QMediaPlayer *player = new QMediaPlayer;

player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
player->setVolume(50);
player->play();
    /*CRUD SUPPRIMER*/
produit P;
P.setreferance(ui->le_referrance->text().toInt());
bool test=P.supprimer(P.getreferance());
QMessageBox msgBox;

if(test)
   { msgBox.setText("Suppression avec succes.");
ui->tableView->setModel(P.afficher());

}
else{
    /*message d'erreur*/

    msgBox.setText("Echec de suppression");
    msgBox.exec();
}
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    if(ui->lineEdit->text() == "")
        {
            ui->tableView->setModel(P.afficher());
        }
        else
        {
             ui->tableView->setModel(P.rechercher(ui->lineEdit->text()));
        }

}


void MainWindow::on_pushButton_clicked()
{
    /*metier tri*/

    QString critere=ui->comboBox->currentText();
        QString mode;
        if (ui->checkBox->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->checkBox_2->checkState()==false)
         {
             mode="ASC";
         }
    ui->tableView->setModel(P.trie(critere,mode));
}


void MainWindow::on_pushButton_2_clicked()
{
    int referance = ui->le_referrance->text().toInt();
    int prix= ui->le_prix->text().toInt();
    QDate date= ui->dateEdit->date();
    QString nom=ui->le_nom->text();
    produit P(nom,prix,referance,date) ;
    bool test =P.modifier(nom,prix,referance,date);
    if(test)
    {ui->tableView->setModel(P.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier une produit"),
                                 QObject::tr("produit  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une produit"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_4_clicked()
{
    /*IMPRESSION PDF*/
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView->model()->rowCount();
                const int columnCount =ui->tableView->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("produit")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/wallys_smart/icons/wallys.jpg' width='100' height='100'>\n"
                            "<h1>Liste des produits</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_6_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_10_clicked()
{
    /*IMPRESSION PDF*/
    {
        QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView_2->model()->rowCount();
                const int columnCount =ui->tableView_2->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("fournisseurs")
                        <<  "</head>\n"
                        "<body bgcolor=#D3D3D3 link=#5000A0>\n"
                            "<img src='C:/Users/user/Documents/wallys_smart/icons/wallys.jpg' width='100' height='100'>\n"
                            "<h1>Liste des fournisseurs</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView_2->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_2->isColumnHidden(column)) {
                                   QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);
                    }
    }
}




void MainWindow::on_pushButton_8_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
    player->setVolume(50);
    player->play();

    /*CRUD AJOUTER*/
    QString nom=ui->lineEdit_3->text();
    QString adresse=ui->lineEdit_4->text();
    int num=ui->lineEdit_5->text().toInt();

     fournisseurs F(nom,adresse,num);

 bool test=F.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tableView_2->setModel(F.afficher());
 }
 else
 {
         const int DeltaPos = 10;

         QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
         animation->setDuration(500);

         if (ui->stackedWidget->currentIndex() == 0) {
            /* Animation mainwindow*/
             int oldX = pos().x();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.1, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.2, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.3, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.4, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.5, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.6, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.7, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(0.8, QPoint(oldX - DeltaPos, pos().y()));
             animation->setKeyValueAt(0.9, QPoint(oldX + DeltaPos, pos().y()));
             animation->setKeyValueAt(1.0, QPoint(oldX, pos().y()));
         } else {
             int oldY = pos().y();
             animation->setEasingCurve(QEasingCurve(static_cast<QEasingCurve::Type>(10)));
             animation->setKeyValueAt(0.0, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.1, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.2, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.3, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.4, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.5, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.6, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.7, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(0.8, QPoint(pos().x(), oldY + DeltaPos));
             animation->setKeyValueAt(0.9, QPoint(pos().x(), oldY - DeltaPos));
             animation->setKeyValueAt(1.0, QPoint(pos().x(), oldY));
         }
         animation->start(QAbstractAnimation::DeleteWhenStopped);
         /*message d'erreur*/
     msgBox.setText("Echec d'ajout");
     msgBox.exec();
}
}

void MainWindow::on_pushButton_9_clicked()
{
    QString nom=ui->lineEdit_3->text();
    QString adresse=ui->lineEdit_4->text();
    int num=ui->lineEdit_5->text().toInt();

     fournisseurs F(nom,adresse,num);

    bool test =F.modifier(nom,adresse,num);
    if(test)
    {ui->tableView_2->setModel(F.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un fournisseur"),
                                 QObject::tr("produit  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un fournisseur"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
fournisseurs F;
    if(ui->lineEdit_7->text() == "")
        {
            ui->tableView_2->setModel(F.afficher());
        }
        else
        {
             ui->tableView_2->setModel(F.rechercher(ui->lineEdit_7->text()));
        }

}

void MainWindow::on_pushButton_11_clicked()
{
    /*metier tri*/
fournisseurs F;
    QString critere=ui->comboBox_2->currentText();
        QString mode;
        if (ui->checkBox_2->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->checkBox_2->checkState()==false)
         {
             mode="ASC";
         }
    ui->tableView_2->setModel(F.trie(critere,mode));
}

void MainWindow::on_pushButton_7_clicked()
{
    /*sound */

QMediaPlayer *player = new QMediaPlayer;

player->setMedia(QUrl::fromLocalFile("C:/Users/user/Documents/Ressources_Humaines/button-6.mp3"));
player->setVolume(50);
player->play();
    /*CRUD SUPPRIMER*/
fournisseurs F;
F.setnomsociete(ui->lineEdit_6->text());
bool test=F.supprimer(F.getnomsociete());
QMessageBox msgBox;

if(test)
   { msgBox.setText("Suppression avec succes.");
ui->tableView_2->setModel(F.afficher());

}
else{
    /*message d'erreur*/

    msgBox.setText("Echec de suppression");
    msgBox.exec();
}
}
