#include "manager.h"
#include <QDebug>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QCompleter>
#include <QMessageBox>

Manager::Manager(QObject *parent) : QObject(parent),
        login( new Login ),
        principal(new Principal ),
        ingreso( new FormularioIngreso ),
        salida( new Formulariosalida ),
        autos( new TablaAutos )
{
    tabla = new QTextBrowser;

    //qDebug() << "Conectado" << AdminDB::getInstancia()->conectar("./tested_osimani");
    AdminDB::getInstancia()->iniciar("../ProyectoCochera/db/tested");

    AdminDB::getInstancia()->mostrarTodo( "usuarios" );

    connect(login, SIGNAL(signal_usuarioValidado(QString,QString)), this, SLOT(slot_ingreso(QString,QString)));
    connect(principal, SIGNAL(signal_cerrarSesion()), login, SLOT(show()));

    connect(principal, SIGNAL(signal_ingresoAutos()), ingreso, SLOT(show()));

    //manager -> ingreso de automovil
    connect(this, SIGNAL(signal_contarEstacionados(int)), ingreso, SLOT(slot_contarEstacionados(int)));

    connect(ingreso, SIGNAL(signal_volverPrincipal()),principal, SLOT(show()));
    connect(ingreso, SIGNAL(signal_cargarAutos(QString,QString,QString)), this, SLOT(slot_ingresoAutos(QString,QString,QString)));

    //ingreso de automovil -> manager
    connect(ingreso,SIGNAL(signal_contarEstacionados()),this,SLOT(slot_contarEstacionados()));

    connect(principal, SIGNAL(signal_salidaDeAutos()), salida, SLOT(show()));

    connect(this, SIGNAL(signal_mostrarTablaEstacionados(QStringList)),salida, SLOT(listar_estacionados(QStringList)));
    connect(salida, SIGNAL(signal_listar_estacionados()),this, SLOT(slot_mostrarTablaEstacionados()));

    connect(salida, SIGNAL(signal_volverSalida()),principal, SLOT(show()));

    connect(salida, SIGNAL(signal_salidaAuto(QString,QString)), this, SLOT(slot_salidaDeAutos(QString,QString)));

    connect(principal, SIGNAL(signal_verTablaAutos()), autos, SLOT(show()));
    connect(autos, SIGNAL(signal_volverPrincipalAutos()), principal, SLOT(show()));


}

Manager::~Manager()
{

}

void Manager::iniciar()
{
    login->show();
}

void Manager::slot_ingreso(QString usuario, QString clave)
{
    QStringList usuarioCompleto;
    usuarioCompleto = AdminDB::getInstancia()->validar(usuario, clave, "usuarios");

    if( !usuarioCompleto.isEmpty())
    {
        id_estacionamiento = usuarioCompleto.at(2).toInt();

        autos->setId_estacionamiento(id_estacionamiento);

        //trae usuario y la id del estacionamiento que se usa para saber la cantidad
        ingreso->setLimite_autos(AdminDB::getInstancia()->capacidadEstacionamiento(id_estacionamiento));

        login->hide();
        principal->show();
    }
}

void Manager::slot_ingresoAutos(QString patente, QString descripcion, QString fechaIn)
{
    // controlar que no ingresen campos o autos vacios a la DB
    if (patente.isEmpty() || descripcion.isEmpty()) {

        mensaje.setText("No se cargaron datos.");
        mensaje.setWindowTitle("ERROR");
        mensaje.show();
    }
    else
    {
        AdminDB::getInstancia()->insertAutos(patente, descripcion, fechaIn, id_estacionamiento);
    }
}

void Manager::slot_salidaDeAutos(QString patente, QString fechaout)
{
    if(AdminDB::getInstancia()->updateAutosSalida(patente, fechaout,id_estacionamiento)){
        emit signal_mostrarTablaEstacionados(AdminDB::getInstancia()->listarAutosEstacionados(id_estacionamiento));
    }
}
//tabla de autos dependiendo el id de estacionamiento(estacionados)
void Manager::slot_mostrarTablaEstacionados()
{
    emit signal_mostrarTablaEstacionados(AdminDB::getInstancia()->listarAutosEstacionados(id_estacionamiento));
}

void Manager::slot_contarEstacionados()
{
    emit signal_contarEstacionados(AdminDB::getInstancia()->cantidadEstacionados(id_estacionamiento));
}

