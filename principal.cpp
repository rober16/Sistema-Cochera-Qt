#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    connect(ui->pbCerrarSesion, SIGNAL(pressed()), this, SLOT(slot_pbcerrarSesion()));
    connect(ui->pbIngreso, SIGNAL(pressed()), this, SLOT(slot_IngresarAutos()));
    connect(ui->pbSalida, SIGNAL(pressed()), this, SLOT(slot_salidaAutos()));
    connect(ui->pbAutos, SIGNAL(pressed()), this, SLOT(slot_tablaAutos()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::slot_pbcerrarSesion()
{
    this->hide();
    emit signal_cerrarSesion();
}

void Principal::slot_IngresarAutos()
{
    this->hide();
    emit signal_ingresoAutos();
}

void Principal::slot_salidaAutos()
{
    this->hide();
    emit signal_salidaDeAutos();
}

void Principal::slot_tablaAutos()
{
    this->hide();
    emit signal_verTablaAutos();
}
