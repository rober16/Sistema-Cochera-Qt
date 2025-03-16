#ifndef FORMULARIOSALIDA_H
#define FORMULARIOSALIDA_H

#include <QWidget>
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class Formulariosalida;
}

class Formulariosalida : public QWidget
{
    Q_OBJECT

public:
    explicit Formulariosalida(QWidget *parent = nullptr);
    ~Formulariosalida();
private:
    Ui::Formulariosalida *ui;
    QMessageBox msn2;
    QTimer update;

protected:
    void showEvent( QShowEvent * );

public slots:
    void listar_estacionados(QStringList autos);

private slots:
    void buscarAuto();
    void slot_pbVolverSalida();
    void slot_altaSalidaAuto();
    void onUpdateTimeout();
    void slot_currentTextChanged(QString text);
    void upperCase(QString patente);

signals:
    void signal_listar_estacionados();
    void signal_volverSalida();
    void signal_salidaAuto(QString patente, QString fechaout);

};

#endif // FORMULARIOSALIDA_H
