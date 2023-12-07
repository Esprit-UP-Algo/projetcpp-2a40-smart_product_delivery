#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vehicle.h"
#include <QApplication>
#include <QMessageBox>
#include <QTableView>
#include <qmessagebox.h>
#include <QIntValidator>
#include <QSqlQuery>
#include <QScrollBar>
#include <qfiledialog.h>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QComboBox>
#include <QMediaPlayer>
#include <QtSql>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->vehiclesTableView->setModel(tmpproduits.afficher());
   

}




MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_addVehicle_Button_clicked()
{
    int id =ui->id->text().toInt();
    QString make =ui->make->text();
    QString model =ui->model->text();
    QString datedebut =ui->datedebut->text();

    Vehicle V(id,make,model,datedebut);
    bool test=V.ajouter();


    if(test)
    {
        ui->vehiclesTableView->setModel(V1.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("ajout effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("ajout non effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);
}

void MainWindow::on_updateVehicleButton_clicked()
{
    Vehicle v;

    int id =ui->updateid->text().toInt();
    QString make =ui->updatemake->text();
    QString model =ui->updatemodel->text();
    QString datedebut =ui->updatedatedebut->text();



    bool test=v.modifier(id,make,model,datedebut);

    if(test)

    {

       QMessageBox::information(this, "Modification réussie", "Votre données a été modifié avec succès.");



        // Mettez à jour le modèle de votre QTableView

        ui->vehiclesTableView->setModel(v.afficher());

    }

    else

    {

        QMessageBox::warning(this, "Erreur de modification", "Erreur lors de la modification du produit.");

    }
}

void MainWindow::on_deleteVehicleButton_clicked()
{
    Vehicle V2; V2.setid(ui->supid->text().toInt());
    bool test=V2.supprimer(V2.getid());
    QMessageBox msgBox;

    if(test)
    {
        ui->vehiclesTableView->setModel(V1.afficher());
        msgBox.setText("suppression avec succes");
    }
    else
    msgBox.setText("echec de suppression");
    msgBox.exec();  
}

void MainWindow::on_tripardatedebut_clicked()
{
    ui->vehiclesTableView->setModel(tmpproduits.tridatedebut());
}
void MainWindow::on_triparid_clicked()
{
    ui->vehiclesTableView->setModel(tmpproduits.triid());
}
void MainWindow::on_excel_clicked()
{
    Vehicle V;
              QSqlQueryModel * model=new QSqlQueryModel();
              model=V.Find_Vehicle();
              QString textData= "id                make                    model                  date de debut \n";
              int rows=model->rowCount();
              int columns=model->columnCount();
              for (int i = 0; i < rows; i++)
              {
                  for (int j = 0; j < columns; j++)
                  {
                      textData += model->data(model->index(i,j)).toString();
                      textData +=" ; ";
                  }
                  textData += "\n";
              }
              QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
              if (!fileName.isEmpty())
                  if (QFileInfo(fileName).suffix().isEmpty())
                      fileName.append(".csv");
              QFile csvfile(fileName);
              if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
              {
                  QTextStream out(&csvfile);
                  out<<textData;
              }
              csvfile.close();
}


void MainWindow::on_imprimer_clicked()
{
        QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = ui->vehiclesTableView->model()->rowCount();
                    const int columnCount = ui->vehiclesTableView->model()->columnCount();
                    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                    out <<"<html>\n"
                          "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        << "<title> LISTE DES STADES<title>\n "
                        << "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                        "<h1 style=\"text-align: center;\"><strong> ***LISTE DES PRODUITS*** "+TT+"</strong></h1>"
                        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                          "</br> </br>";
                    // headers
                    out << "<thead><tr bgcolor=#d6e5ff>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->vehiclesTableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->vehiclesTableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->vehiclesTableView->isColumnHidden(column)) {
                                QString data =ui->vehiclesTableView->model()->data(ui->vehiclesTableView->model()->index(row, column)).toString().simplified();
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

                    QPrintDialog *test = new QPrintDialog(&printer, NULL);
                    if (test->exec() == QDialog::Accepted) {
                        document->print(&printer);
                    }

                    delete document;
    }





void MainWindow::on_recherche_2_clicked()
{
    QMediaPlayer * bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl::fromLocalFile("C:Users\MSI\Downloads/untitled_307.mp3"));

       if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
        QString rech =ui->recherche->text();
       ui->vehiclesTableView->setModel(tmpproduits.recherche(rech));
}
