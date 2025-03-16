#include "admindb.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QVariant>
#include "admindb.h"

AdminDB * AdminDB::instancia = NULL;

AdminDB::AdminDB(QObject * parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

AdminDB::~AdminDB()
{

}

AdminDB *AdminDB::getInstancia()
{
    if(instancia == 0)
    {
        instancia = new AdminDB;
    }

    return instancia;
}

void AdminDB::iniciar(QString archivo)
{
    this->conectar(archivo);
}

bool AdminDB::conectar(QString nombreBase)
{
    db.setDatabaseName(nombreBase);
    db.open();

    return db.isOpen();
}

void AdminDB::mostrarTodo(QString tabla)
{
    if ( db.isOpen() )  {
            QSqlQuery query = db.exec( "SELECT * FROM " + tabla );

            while ( query.next() )  {

                QSqlRecord registro = query.record();

                int cantidadCampos = registro.count();

                QStringList listaDeCampos;

                for ( int i = 0 ; i < cantidadCampos ; i++ )  {
                    listaDeCampos.append( query.value( i ).toString() );
                }

                qDebug() << listaDeCampos;

            }
    }
}

QStringList AdminDB::validar(QString nombre, QString contrasena, QString tabla)
{

    QStringList listaNombreApellido;

       if ( db.isOpen() )  {

           QSqlQuery query = db.exec( "SELECT nombre, clave, id_estacionamiento FROM " + tabla +
                                      " WHERE nombre = '" + nombre + "' AND clave = '" +
                                      contrasena + "'" );

           while ( query.next() )  {
               listaNombreApellido.append( query.value( 0 ).toString() );
               listaNombreApellido.append( query.value( 1 ).toString() );
               //id_estacionamiento
               listaNombreApellido.append( query.value( 2 ).toString() );
           }
       }

       return listaNombreApellido;

}
QSqlDatabase AdminDB::getDB()
{
    return db;
}

QStringList *AdminDB::query(QString table, int column)
{
    QStringList * list = new QStringList();

    QSqlQuery * query = new QSqlQuery(db);
    query->exec("select * FROM " + table);
    while(query->next()){
        QString row = query->value(column).toString(); // 1 = indice de la primera columna de table
        *list << row;
    }
    return list;
}

bool AdminDB::insert(QString table, QString column, QString value)
{
    QSqlQuery * query = new QSqlQuery( db );

    return query->exec("INSERT INTO " + table + " (" + column +") "
                               "VALUES ('"+ value +"')");
}

bool AdminDB::insertAutos(QString patente, QString descripcion, QString fechain, int id_estacionamiento)
{
    QSqlQuery query(db);
    //Primero controlamos que no ingrese otra vez un auto que sigue estacionado
    query.exec("SELECT * FROM autos WHERE patente= '"+ patente +"'");

    while (query.next())
    {
        if (query.value(4).isNull()) //si fecha_salida es null quiere decir que sigue estacionado
        {            
           msn3.setText("Esta patente ya en el sistema!");
           msn3.setWindowTitle("ERROR");
           msn3.show();
           return false;
        }
    }
    query.exec("SELECT id FROM descripciones WHERE descripcion= '"+ descripcion +"'");

    int id_descripcion = 0;

    while (query.next())
    {
        if (query.value(0).isNull()) return false;
        id_descripcion = query.value(0).toInt();
    }
    qDebug() << id_descripcion;

    return query.exec("INSERT INTO autos (patente, id_descripcion, fecha_ingreso,id_estacionamiento) VALUES ('"
                        + patente + "', '" + QString::number(id_descripcion) + "', '" + fechain + "', " + QString::number(id_estacionamiento) + ")");

    qDebug() << "Datos agregados con exito!...";
}

bool AdminDB::updateAutosSalida(QString patente, QString fechaout, int id_estacionamiento)
{
    QSqlQuery query(db);
    // para evitar que el usuario no pueda sacar autos de otro estacionamiento
    bool res = query.exec("UPDATE autos set fecha_salida = '" +fechaout+ "' WHERE patente = '" +patente+ "' AND fecha_salida IS NULL AND id_estacionamiento = " + QString::number(id_estacionamiento));

    qDebug() << res;

    return true;

}

QVector<QVector<QString>> AdminDB::select(QString comando)
{
    QVector<QVector<QString>> registros;
    QSqlQuery query = db.exec(comando);

    while(query.next())
    {
        QVector<QString> columnas;

        for (int i = 0; i < query.record().count(); i++)
        {
            columnas.append(query.value(i).toString());
        }

        registros.append(columnas);
    }

    return registros;
}

QStringList AdminDB::listarAutosEstacionados(int id_estacionamiento)
{
    QStringList autos;

    QSqlQuery query(db);
    query.exec("SELECT * FROM autos WHERE fecha_salida IS NULL AND id_estacionamiento = " + QString::number(id_estacionamiento));

    while(query.next())
        autos.append(query.value(1).toString());

    return autos;
}

int AdminDB::cantidadEstacionados(int id_estacionamiento)
{
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM autos WHERE fecha_salida IS NULL AND id_estacionamiento = " + QString::number(id_estacionamiento));
    query.next();

    return query.value(0).toInt();
}

int AdminDB::capacidadEstacionamiento(int id_estacionamiento)
{
    QSqlQuery query(db);
    query.exec("SELECT cantidad FROM estacionamientos WHERE id = " + QString::number(id_estacionamiento));
    query.next();

    return query.value(0).toInt();
}


