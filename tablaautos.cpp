#include "tablaautos.h"
#include "ui_tablaautos.h"
#include <QSqlRelation>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableWidgetItem>
#include <QDebug>
#include <QVector>
#include "admindb.h"

TablaAutos::TablaAutos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TablaAutos)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->pbVolverAutos, SIGNAL(pressed()), this, SLOT(slot_volverAutos()));
}

TablaAutos::~TablaAutos()
{
    delete ui;
}

void TablaAutos::setId_estacionamiento(int value)
{
    id_estacionamiento = value;
}

void TablaAutos::slot_volverAutos()
{
    this->hide();
    emit signal_volverPrincipalAutos();
}

void TablaAutos::showEvent(QShowEvent *)
{    
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    //Crear cabecera de la tabla
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Patente"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Descripcion"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Fecha Ingreso"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Fecha Salida"));

    //se llama desde adentro
    //el JOIN busca las similitudes entre id_descripcion de la tabla autos y el id de la tabla descripciones
    QVector<QVector<QString>> registros = AdminDB::getInstancia()->select("SELECT * FROM autos JOIN descripciones WHERE autos.id_descripcion = descripciones.id AND id_estacionamiento =" + QString::number(id_estacionamiento));

    foreach(QVector<QString> columnas, registros)
    {

        int index = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(index);

        ui->tableWidget->setItem(index,0,new QTableWidgetItem(columnas.at(1)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(columnas.at(7)));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(columnas.at(3)));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(columnas.at(4)));

    }

}
