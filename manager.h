#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>
#include <QLabel>
#include <QTextBrowser>
#include <QMessageBox>
#include "login.h"
#include "principal.h"
#include "formularioingreso.h"
#include "formulariosalida.h"
#include "tablaautos.h"
#include "admindb.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
    ~Manager();

    void iniciar();
    void dimensionarWidget();


private:
    // agregar todos los objetos que se necesiten usar (widgets, variables, etc)
    QTextBrowser *tabla;
    Login * login;
    Principal * principal;
    FormularioIngreso *ingreso;
    Formulariosalida *salida;
    TablaAutos *autos;
    QMessageBox mensaje;

    int id_estacionamiento;

private slots:
        void slot_ingreso(QString usuario, QString clave );
        void slot_ingresoAutos(QString patente, QString descripcion, QString fechaIn);
        void slot_salidaDeAutos(QString patente, QString fechaout);
        void slot_mostrarTablaEstacionados();
        void slot_contarEstacionados();

signals:
    void signal_mostrarTablaEstacionados(QStringList);
    void signal_contarEstacionados(int);


};

#endif // MANAGER_H
