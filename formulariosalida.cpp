#include "formulariosalida.h"
#include "ui_formulariosalida.h"
#include <QCompleter>
#include <QDebug>

Formulariosalida::Formulariosalida(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formulariosalida)
{
    ui->setupUi(this);
    ui->lePatente2->setMaxLength(6);


    connect(ui->pbVolver2, SIGNAL(pressed()), this, SLOT(slot_pbVolverSalida()));
    connect(ui->pbConfirmarSalida, SIGNAL(pressed()), this, SLOT(slot_altaSalidaAuto()));
    connect(ui->lePatente2, SIGNAL(textChanged(QString)),this,SLOT(buscarAuto()));
    connect(ui->lePatente2, SIGNAL(textChanged(QString)), this, SLOT(upperCase(QString)));

    connect(&update,SIGNAL(timeout()),this,SLOT(onUpdateTimeout()));
    update.start(1000);

    connect(ui->listWidget,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_currentTextChanged(QString)));
}

Formulariosalida::~Formulariosalida()
{
    delete ui;
}

void Formulariosalida::showEvent(QShowEvent *)
{
    ui->dateTimeEditSalida->setDateTime( QDateTime::currentDateTime() );
    emit signal_listar_estacionados();
}

void Formulariosalida::slot_pbVolverSalida()
{
    this->hide();
    emit signal_volverSalida();
}

void Formulariosalida::slot_altaSalidaAuto()
{
    emit signal_salidaAuto(ui->lePatente2->text(),ui->dateTimeEditSalida->text());
}

void Formulariosalida::onUpdateTimeout()
{
    ui->dateTimeEditSalida->setDateTime( QDateTime::currentDateTime() );
}

void Formulariosalida::slot_currentTextChanged(QString text)
{
    ui->lePatente2->setText(text);
}

void Formulariosalida::buscarAuto()
{    
    //Pasa todos los elementos del listwidget a un QStringList
    QStringList campos;
    for(int i = 0; i < ui->listWidget->count(); i++)
        campos.append(ui->listWidget->item(i)->text());

}

void Formulariosalida::listar_estacionados(QStringList autos)
{
    ui->listWidget->clear();
    ui->lePatente2->clear();
    ui->listWidget->addItems(autos);
}
void Formulariosalida::upperCase(QString patente)
{
    ui->lePatente2->setText(patente.toUpper());
}

