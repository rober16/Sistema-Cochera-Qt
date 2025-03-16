#ifndef FORMULARIOINGRESO_H
#define FORMULARIOINGRESO_H

#include <QWidget>
#include <QCompleter>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include "admindb.h"

namespace Ui {
class FormularioIngreso;
}

class FormularioIngreso : public QWidget
{
    Q_OBJECT

public:
    explicit FormularioIngreso (QWidget *parent = nullptr);
    ~FormularioIngreso();

    void setLimite_autos(int value);

private:
    Ui::FormularioIngreso *ui;
    QMessageBox msn;
    QTimer update2;
    int limite_autos;

protected:
    void showEvent( QShowEvent * );

signals:
    void signal_volverPrincipal();
    void signal_cargarAutos(QString patente, QString descripcion, QString fechaIn);
    void signal_contarEstacionados();

public slots:
    void slot_contarEstacionados(int cantidad);

private slots:
     void slot_alta();
     void slot_pbVolverIngreso();
     void onUpdateTimeout();
     void upperCase(QString patente);

};

#endif // FORMULARIOINGRESO_H
