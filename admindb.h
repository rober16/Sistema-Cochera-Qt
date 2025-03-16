#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>

class AdminDB : public QObject
{
    Q_OBJECT
private:
    AdminDB( QObject * parent = nullptr );
    static AdminDB * instancia;
    QSqlDatabase db;
    //QSqlRelationalTableModel * tableModelAutos;
    QMessageBox msn3, msn4;

public:
    static AdminDB * getInstancia();
    ~AdminDB();

    void iniciar(QString archivo);
    bool conectar( QString nombreBase );
    void mostrarTodo( QString tabla );
    QStringList validar(QString nombre, QString contrasena, QString tabla );
    QSqlDatabase getDB();

    // metodos....
    QStringList *query( QString table, int column );
    bool insert( QString table, QString column, QString value );

    bool insertAutos(QString patente, QString descripcion, QString fechain,int id_estacionamiento);
    bool updateAutosSalida(QString patente, QString fechaout,int id_estacionamiento);
    QVector<QVector<QString>> select(QString comando);

    QStringList listarAutosEstacionados(int id_estacionamiento);
    int cantidadEstacionados(int id_estacionamiento);
    int capacidadEstacionamiento(int id_estacionamiento);
};

#endif // ADMINDB_H
