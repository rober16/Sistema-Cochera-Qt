#ifndef TABLAAUTOS_H
#define TABLAAUTOS_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>

namespace Ui {
class TablaAutos;
}

class TablaAutos : public QWidget
{
    Q_OBJECT

public:
    explicit TablaAutos(QWidget *parent = nullptr);
    ~TablaAutos();

    //setter de id_estacionamiento
    void setId_estacionamiento(int value);

private:
    Ui::TablaAutos *ui;

    int id_estacionamiento;

private slots:
        void slot_volverAutos();        

protected:
    void showEvent( QShowEvent * );

signals:
    void signal_volverPrincipalAutos();

};

#endif // TABLAAUTOS_H
