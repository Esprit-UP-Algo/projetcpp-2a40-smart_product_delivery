#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"client.h"
#include "arduino.h"
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
char arduino;
private slots:
    void on_pushButton_clicked();

    void on_pushButtonValider_clicked();

    void on_pushButtonS_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pushButton_Trier_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_Login_clicked();
void processSerialData();


     // slot permettant la mise à jour du label état de la lampe 1,
       // ce slot est lancé à chaque réception d'un message de Arduino

       void on_pushButton_clickedon();   // bouton ON

       void on_pushButton_2_clicked(); // bouton OFF

       void on_pushButton_3_clicked(); // bouton +

       void on_pushButton_4_clicked(); // bouton -

 void update_label();
    //void on_pushButton_Login_clicked();

 void on_recherche_clicked();

private:
    Ui::MainWindow *ui;
    Client c;
    Client tmpAchats;
    Client trinAchats;

    QByteArray data; // variable contenant les données reçues
QSerialPort *serial;
       Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
