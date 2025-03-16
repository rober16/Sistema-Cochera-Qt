#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QGridLayout>

Login::Login( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Login )
{
    ui->setupUi(this);

    connect(ui->widgetIngresar, SIGNAL( signal_click() ), this, SLOT(slot_validarUsuario()));
    connect(ui->lePass, SIGNAL( returnPressed() ), this, SLOT(slot_validarUsuario()));

    this->setMinimumHeight(ui->lePass->y() + ui->lePass->height() + 40); // se setea una sola vez
}

Login::~Login()
{
    delete ui;
}

void Login::dimensionarWidget()
{
    int h = this->height();
    int w = this->width();

    ui->lIcono->move(w/2-ui->lIcono->width()/2,20);

    ui->lUsuario->resize(w-40,ui->lUsuario->height());
    ui->leUser->resize(w-20,ui->leUser->height());

    ui->lUsuario->move(w/2-ui->lUsuario->width()/2, 135);
    ui->leUser->move(w/2-ui->leUser->width()/2, 150);

    ui->lePass->resize(w-20,ui->lePass->height());

    ui->lClave->move(w/2-ui->lClave->width()/2, 175);
    ui->lePass->move(w/2-ui->lePass->width()/2, 190);

    ui->widgetIngresar->move(w/2-ui->widgetIngresar->width()/2,h-40);

}

void Login::resizeEvent(QResizeEvent *e)
{
   this->dimensionarWidget();
}

void Login::slot_validarUsuario()
{
    emit signal_usuarioValidado(ui->leUser->text(), ui->lePass->text());
    ui->lePass->clear();
}



