#include "formularioingreso.h"
#include "ui_formularioingreso.h"
#include <QSqlQuery>
#include <QDebug>
#include "admindb.h"

FormularioIngreso::FormularioIngreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormularioIngreso)
{
    ui->setupUi(this);

    ui->lTiempoIngreso->hide();
    ui->dateTimeEditIngreso->hide();

    ui->lePatente->setMaxLength(6);


    connect(ui->pbVolverIngreso, SIGNAL(pressed()), this, SLOT(slot_pbVolverIngreso()));
    connect(ui->pbCargar,SIGNAL(pressed()),this,SLOT(slot_alta()));
    connect(&update2,SIGNAL(timeout()),this,SLOT(onUpdateTimeout()));

    connect(ui->lePatente, SIGNAL(textChanged(QString)), this, SLOT(upperCase(QString)));

    update2.start(1000);

    AdminDB::getInstancia()->conectar("../ProyectoCochera/db/tested");
    AdminDB::getInstancia()->mostrarTodo("descripcion");

    QStringList lista;
    QString nombres;
    QSqlQuery *query = new QSqlQuery(AdminDB::getInstancia()->getDB());
    query->exec("SELECT descripcion FROM descripciones");

    while(query->next())
    {
       QSqlRecord record = query->record();
       int i=record.indexOf("descripcion");

        nombres = query->value(i).toString();
        lista<< nombres;
    }
    ui->leDescripcion->setList(lista);

}

FormularioIngreso::~FormularioIngreso()
{
    delete ui;
}

void FormularioIngreso::setLimite_autos(int value)
{
    limite_autos = value;
}

void FormularioIngreso::showEvent(QShowEvent *)
{
    ui->lePatente->clear();
    ui->leDescripcion->clear();

    ui->lePatente->setFocus();

    ui->dateTimeEditIngreso->setDateTime( QDateTime::currentDateTime() );
    emit signal_contarEstacionados();
}

void FormularioIngreso::slot_contarEstacionados(int cantidad)
{

    if(cantidad >= limite_autos)
    {
        ui->lWarning->setText("NO HAY LUGAR DISPONIBLE");
        ui->pbCargar->setVisible(false);

    }else
    {
        ui->pbCargar->setVisible(true);

        if(cantidad >= limite_autos-5){
            ui->lWarning->setText("AVISO: Te quedan " + QString::number(limite_autos - cantidad) + " lugares.");
        }
    }
}

void FormularioIngreso::slot_alta()
{
    emit signal_cargarAutos(ui->lePatente->text(),ui->leDescripcion->text(), ui->dateTimeEditIngreso->text());

    ui->lePatente->clear();
    ui->leDescripcion->clear();
    ui->lePatente->setFocus();
}

void FormularioIngreso::slot_pbVolverIngreso()
{
    this->hide();
    emit signal_volverPrincipal();
}

void FormularioIngreso::onUpdateTimeout()
{
    ui->dateTimeEditIngreso->setDateTime( QDateTime::currentDateTime() );
}

void FormularioIngreso::upperCase(QString patente)
{
    ui->lePatente->setText(patente.toUpper());
}

