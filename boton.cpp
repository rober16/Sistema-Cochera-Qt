#include "boton.h"
#include "ui_boton.h"

Boton::Boton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Boton)
{
    ui->setupUi(this);
    image.load("../ProyectoCochera/imagenes/boton");
}

Boton::~Boton()
{
    delete ui;
}
void Boton::mousePressEvent(QMouseEvent *)
{
    emit signal_click();
}
void Boton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image.scaled(this->width(),this->height()));
    //painter.drawText(this->width()/4,this->height()/4,"INGRESAR");
    update();
}
