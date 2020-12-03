#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produit.h"
#include "fournisseurs.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_supprimer_pb_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    produit P;
    fournisseurs F;

};
#endif // MAINWINDOW_H
