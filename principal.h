#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = nullptr);
    ~Principal();

private:
    Ui::Principal *ui;


signals:
    void signal_cerrarSesion();
    void signal_ingresoAutos();
    void signal_salidaDeAutos();
    void signal_verTablaAutos();

private slots:
    void slot_pbcerrarSesion();
    void slot_IngresarAutos();
    void slot_salidaAutos();
    void slot_tablaAutos();

};

#endif // PRINCIPAL_H
