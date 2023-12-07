#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "vehicle.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_addVehicle_Button_clicked();
    
    void on_updateVehicleButton_clicked();
    
    void on_deleteVehicleButton_clicked();

    void on_imprimer_clicked();

    void on_excel_clicked();

    void on_triparid_clicked();

    void on_tripardatedebut_clicked();

    void on_recherche_2_clicked();

private:
     Vehicle tmpproduits;
    Ui::MainWindow *ui;
    Vehicle V1;
};

#endif // MAINWINDOW_H
