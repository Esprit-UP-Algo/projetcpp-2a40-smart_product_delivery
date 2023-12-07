#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDateEdit"
#include"client.h"
#include"dialog.h"
#include<QMessageBox>
#include <QIntValidator>
#include"connection.h"
#include <QScrollBar>
#include <qfiledialog.h>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QComboBox>
#include <QTableView>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QSqlError>
#include <QDebug>

Client c;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditCin->setValidator(new QIntValidator(0, 9999999, this));
    ui->lineEditNum->setValidator(new QIntValidator(0, 99999999, this));
    ui->tableClients->setModel(c.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
 Client c;
 c.setcin(ui->lineEditCin->text().toInt());
  c.setnom(ui->lineEditNom->text());
   c.setprenom(ui->lineEditPrenom->text());

    c.setMail(ui->lineEditMail->text());
    c.setNum(ui->lineEditNum->text().toInt());
    c.setAdresse(ui->lineEditAdresse->text());
    c.setdate_naissance(ui->dateEdit->date());
    c.setnombre_dachats(ui->lineEditNombre_dachats->text().toInt());

/*Dialog d;
d.setclient(c);
d.exec();
*/
}
/*void MainWindow::on_pushButtonValider_clicked()
{
    int cinValue = ui->lineEditCin->text().toInt();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString Mail = ui->lineEditMail->text();
    int Num = ui->lineEditNum->text().toInt();
    QString Adresse = ui->lineEditAdresse->text();
    Client c(cinValue, nom, prenom, Mail, Num, Adresse);
    bool test = c.ajouter();

    //int test1 = 1;
    QMessageBox msgBox;  // Déclaration de la variable ici

      if (Mail.isEmpty() || !Mail.endsWith("@gmail.com") || !Mail.endsWith("@hotmail.fr")) {
           test1 = 0;
           msgBox.setText("Échec : Veuillez saisir une adresse e-mail valide");
       }

       if (test) {
           msgBox.setText("Ajout avec succès");
           ui->tableClients->setModel(c.afficher());
       } else {
           msgBox.setText("Veuillez ressaisir votre e-mail");
       }

       // Executer msgBox ici, en dehors des blocs if-else
       msgBox.exec();
}*/

void MainWindow::on_pushButtonValider_clicked()
{
    int cinValue = ui->lineEditCin->text().toInt();
    QString nom=ui->lineEditNom->text();
    QString prenom=ui->lineEditPrenom->text();
    QString Mail=ui->lineEditMail->text();
    int Num=ui->lineEditNum->text().toInt();
    //QString Num=ui->lineEditNum->text().toInt();
    QString Adresse=ui->lineEditAdresse->text();
    QDate date_naissance=ui->dateEdit->date();
    int nombre_dachats=ui->lineEditNombre_dachats->text().toInt();
    Client c (cinValue,nom,prenom,Mail,Num,Adresse,date_naissance,nombre_dachats);
    bool test=c.ajouter();

   int test1=1;
   QMessageBox msgBox;
       QString ref =ui->lineEditMail->text();
       int countMail = 0;
       for (int i=0;i<Mail.size();i++)
       {
           QChar m=Mail[i];
           if (m == "@"||m=="gmail.com"||m=="hotmail.fr")
           {
               countMail++;
           }
       }

        if(Mail==""||countMail>0)
       {
           test1=0;

           msgBox.warning(nullptr,QObject::tr("echec"),QObject::tr("Veuillez resaisir email"),QMessageBox::Ok);
       }
     if(test)
       {
 msgBox.warning(nullptr,QObject::tr(""),QObject::tr("ajout avec success"),QMessageBox::Ok);
        // msgBox.setText("ajout avec success");
     }
    else
      {
 msgBox.warning(nullptr,QObject::tr("echec"),QObject::tr("Veuillez resaisir"),QMessageBox::Ok);
       //  msgBox.setText("veuillez resaisir votre mail");
     }
     ui->tableClients->setModel(c.afficher());



}




void MainWindow::on_pushButtonS_clicked()
{
       Client c;
       c.setcin(ui->lineEditCin_3->text().toInt());
       bool test=c.supprimer(c.getcin());

       QMessageBox msgBox;
          if(test)
          {
           msgBox.setText("suppression avec success");
          }
        else
            msgBox.setText("echec");
           msgBox.exec();
       ui->tableClients->setModel(c.afficher());
}

void MainWindow::on_pushButton_modifier_clicked()

{
    int cinValue = ui->lineEditCin_4->text().toInt();
    QString nom = ui->lineEditNom_2->text();
    QString prenom = ui->lineEditPrenom_2->text();
    QString Mail = ui->lineEditMail_2->text();
    int Num = ui->lineEditNum_2->text().toInt();
    QString Adresse = ui->lineEditAdresse_2->text();





    bool test=c.modifier(cinValue, nom, prenom, Mail, Num,Adresse);

    if(test)

    {

        QMessageBox::information(this, "Modification réussie", "Client a été modifié avec succès.");


        // Mettez à jour le modèle de votre QTableView

        ui->tableClients->setModel(c.afficher());
    }

    else

    {
        QMessageBox::warning(this, "Erreur de modification", "Erreur lors de la modification du client.");
    }

}


void MainWindow::on_pushButton_Modifier_clicked()
{
    Client c;
        int cinValue=ui->lineEditCin_4->text().toInt(); // Remplace 1 par l'ID de l'étudiant que tu veux modifier
        QString nom = ui->lineEditNom_2->text(); // Utilise le champ ou l'élément d'interface approprié
        QString prenom = ui->lineEditPrenom_2->text(); // Utilise le champ ou l'élément d'interface approprié
        QString Mail = ui->lineEditMail_2->text();
        int Num = ui->lineEditNum_2->text().toInt();
        QString Adresse = ui->lineEditAdresse_2->text();

        if(c.modifier(cinValue, nom, prenom, Mail, Num, Adresse))
        {
            QMessageBox::information(this, "Modification réussie", "Client a été modifié avec succès.");
            ui->tableClients->setModel(c.afficher());
        }
        else
        {
            QMessageBox::warning(this, "Erreur de modification", "Erreur lors de la modification du client.");
        }
}


/*void MainWindow::on_pushButton_3_clicked()
{
    ui->tableClients->setModel(tmpAchats.trinAchats());

}
*/
/*
void MainWindow::on_pushButton_4_clicked()
{
    QString strStream;

                             QTextStream out(&strStream);



                             const int rowCount = ui->tableClients->model()->rowCount();

                             const int columnCount = ui->tableClients->model()->columnCount();



                             out <<  "<html>\n"

                                 "<head>\n"

                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                                 <<  QString("<title>%1</title>\n").arg("strTitle")

                                 <<  "</head>\n"

                                 "<body bgcolor=#ffffff link=#5000A0>\n"



                                //     "<align='right'> " << datefich << "</align>"

                                 "<center> <H1>Liste des Clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";



                             // headers

                             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";

                             for (int column = 0; column < columnCount; column++)

                                 if (!ui->tableClients->isColumnHidden(column))

                                     out << QString("<th>%1</th>").arg(ui->tableClients->model()->headerData(column, Qt::Horizontal).toString());

                             out << "</tr></thead>\n";



                             // data table

                             for (int row = 0; row < rowCount; row++) {

                                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";

                                 for (int column = 0; column < columnCount; column++) {

                                     if (!ui->tableClients->isColumnHidden(column)) {

                                         QString data = ui->tableClients->model()->data(ui->tableClients->model()->index(row, column)).toString().simplified();

                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                                     }

                                 }

                                 out << "</tr>\n";

                             }

                             out <<  "</table> </center>\n"

                                 "</body>\n"

                                 "</html>\n";



                       QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");

                         if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }



                        QPrinter printer (QPrinter::PrinterResolution);

                         printer.setOutputFormat(QPrinter::PdfFormat);

                        printer.setPaperSize(QPrinter::A4);

                       printer.setOutputFileName(fileName);



                        QTextDocument doc;

                         doc.setHtml(strStream);

                         doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number

                         doc.print(&printer);

}
*/


/*void MainWindow::on_pushButton_Trier_clicked()
{
     ui->tableClients->setModel(tmpAchats.trinAchats());
}

*/
void MainWindow::on_pushButton_PDF_clicked()
{
    QString strStream;

                             QTextStream out(&strStream);



                             const int rowCount = ui->tableClients->model()->rowCount();

                             const int columnCount = ui->tableClients->model()->columnCount();



                             out <<  "<html>\n"

                                 "<head>\n"

                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                                 <<  QString("<title>%1</title>\n").arg("strTitle")

                                 <<  "</head>\n"

                                 "<body bgcolor=#ffffff link=#5000A0>\n"



                                //     "<align='right'> " << datefich << "</align>"

                                 "<center> <H1>Liste des Clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";



                             // headers

                             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";

                             for (int column = 0; column < columnCount; column++)

                                 if (!ui->tableClients->isColumnHidden(column))

                                     out << QString("<th>%1</th>").arg(ui->tableClients->model()->headerData(column, Qt::Horizontal).toString());

                             out << "</tr></thead>\n";



                             // data table

                             for (int row = 0; row < rowCount; row++) {

                                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";

                                 for (int column = 0; column < columnCount; column++) {

                                     if (!ui->tableClients->isColumnHidden(column)) {

                                         QString data = ui->tableClients->model()->data(ui->tableClients->model()->index(row, column)).toString().simplified();

                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                                     }

                                 }

                                 out << "</tr>\n";

                             }

                             out <<  "</table> </center>\n"

                                 "</body>\n"

                                 "</html>\n";



                       QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");

                         if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }



                        QPrinter printer (QPrinter::PrinterResolution);

                         printer.setOutputFormat(QPrinter::PdfFormat);

                        printer.setPaperSize(QPrinter::A4);

                       printer.setOutputFileName(fileName);



                        QTextDocument doc;

                         doc.setHtml(strStream);

                         doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number

                         doc.print(&printer);


}

void MainWindow::on_pushButton_Login_clicked()
{
    Client c;
    QString Mail=ui->lineEdit_mail->text();
        int cin = ui->lineEditCin_5->text().toInt();

        if (Mail == c.getMail() && cin == c.getcin())
        {
            QMessageBox::information(this, "Login Successful", "Welcome, " + Mail + "!");
        }
        else
        {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password. Please try again.");
        }
}



void MainWindow::on_pushButton_Trier_clicked()
{
     ui->tableClients->setModel(tmpAchats.trinAchats());
}





void MainWindow::update_label()
{
    data=A.read_from_arduino();
    qDebug() << "data="<<data;
    if(data=="1"){QMessageBox::warning(this, "ok", "succes");

        ui->lineEdit_status->setText("ON");}
         // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else {QMessageBox::warning(this, "error", "non autorisé");

            ui->lineEdit_status->setText("OFF");}
               // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void MainWindow::on_pushButton_clickedon()   // implémentation du slot bouton on
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}

void MainWindow::on_pushButton_2_clicked()  // implémentation du slot bouton off
{

     A.write_to_arduino("0");  //envoyer 0 à arduino
}

void MainWindow::on_pushButton_3_clicked()  // implémentation du slot bouton +
{
    A.write_to_arduino("2");   //envoyer 2 à arduino
}

void MainWindow::on_pushButton_4_clicked() // implémentation du slot bouton -
{
    A.write_to_arduino("3");  //envoyer 3 à arduino
}
void MainWindow::processSerialData()
{
    // Read data from the serial port
    QByteArray data = serial->readAll();

    // Convert the data to a QString
    QString receivedData = QString::fromUtf8(data).trimmed();  // Trim whitespace

    // Debug: Print received data
    qDebug() << "Received data: " << receivedData;

    // Process the received data
    if (receivedData == "A") {
        ui->lineEdit_status->setText("Access Authorized");

        // Assuming you have a valid client ID (e.g., 123456) for the update
        int clientIdToUpdate = 2;

        // Update database for the given ID
        QSqlQuery query;
        query.prepare("UPDATE GS_CLIENT SET access_status = 'ACCES AUTORISE' WHERE CIN= :CIN");
        query.bindValue(":CIN", clientIdToUpdate);

        if (query.exec()) {
            qDebug() << "Database updated successfully for ID: " << clientIdToUpdate;
        } else {
            qDebug() << "Failed to update database for ID: " << clientIdToUpdate;
        }
    } else if (receivedData == "D") {
        ui->lineEdit_status->setText("Access Denied");
    } else {
        // Add additional handling for unexpected data
        ui->lineEdit_status->setText("Message: " + receivedData);
    }

    // You might need additional logic depending on your communication protocol
}



void MainWindow::on_recherche_clicked()
{
    QString adr=ui->radresse->text();
    bool test=c.rechercherParAdresse(adr);
    if(test)
    {
        QMessageBox::warning(this, "success", "adresse found");

    }
    else{
        QMessageBox::warning(this, "error", "adresse not found");

    }
}
