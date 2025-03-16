#include "lineadetexto.h"
#include <QDebug>

LineaDeTexto::LineaDeTexto(QWidget *parent) : QLineEdit(parent)
{
    this->crearpopup();
}
LineaDeTexto::LineaDeTexto(QString texto, QWidget *parent) : QLineEdit(texto, parent)
{

}
LineaDeTexto::LineaDeTexto(const LineaDeTexto &linea, QWidget *parent) : QLineEdit(parent)
{
    this->setText(linea.text());
}
LineaDeTexto& LineaDeTexto::operator=(const LineaDeTexto &linea)
{
    this->setText(linea.text());
    return *this;
}
LineaDeTexto LineaDeTexto::operator+(const LineaDeTexto &linea)
{
    return LineaDeTexto(this->text() + linea.text());
}
LineaDeTexto LineaDeTexto::operator+(QString string)
{
    return LineaDeTexto(this->text() + string);
}
void LineaDeTexto::setList(QStringList l)
{
    list = l;
}

//Crear un popup para sugerencias (estilo QCompleter pero mejor)
void LineaDeTexto::crearpopup()
{
    popup=new QTreeWidget();
    popup->setColumnCount(1);
    popup->header()->hide();
    popup->setRootIsDecorated(false);
    popup->installEventFilter(this);
    popup->setWindowFlags(Qt::Popup);

    connect(popup,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(completarLineEdit()));

    timer=new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(200);
    connect(timer,SIGNAL(timeout()),SLOT(sugerencia()));
    connect(this,SIGNAL(textEdited(QString)),timer,SLOT(start()));
}

void LineaDeTexto::sugerencia()
{
    QVector<QStringList> coincidencias;
    QString line = this->text();
    int contador = 0;

    for (int i = 0; i < list.size() && contador < 4; i++)
    {
        QString sugerencia = list.at(i);
        if(sugerencia.startsWith(line, Qt::CaseInsensitive))
        {
            QStringList parecidos;
            parecidos << sugerencia;
            coincidencias.push_back(parecidos);
            contador++;
        }
    }
    for (int i = 0; i < list.size() && contador < 4; i++)
    {
        QString sugerencia = list.at(i);
        if(sugerencia.contains(line, Qt::CaseInsensitive))
        {
            QStringList parecidos;
            parecidos << sugerencia;
            if (!coincidencias.contains(parecidos))
            {
                coincidencias.push_back(parecidos);
            }
            contador++;
        }
    }
    // Si no existe lo que se busca se limpia el QLineEdit.
    if (coincidencias.size() == 0)
    {
        this->clear();
        return;
    }
    this->completarpopup(coincidencias);
}
void LineaDeTexto::completarpopup(QVector<QStringList> list)
{
    popup->clear();
    for (int i = 0; i < list.size(); ++i)
    {
        QTreeWidgetItem *items;
        items=new QTreeWidgetItem(popup);
        items->setText(0,list.at(i).at(0));
        items->setTextAlignment(1,Qt::AlignRight);
    }
    popup->setCurrentItem(popup->topLevelItem(0));
    int h = popup->sizeHintForRow(0) * qMin(4, list.size()) + 2;
    popup->resize(this->width(), h);
    popup->move(this->mapToGlobal(QPoint(0, this->height())));
    popup->setFocus();
    popup->show();
}
void LineaDeTexto::completarLineEdit()
{
    if(!list.contains(this->text()))
    {
        list.append(this->text());
    }
    timer->stop();
    popup->hide();
    this->setFocus();

    QTreeWidgetItem *items= popup->currentItem();
    if(items)
    {
        this->setText(items->text(0));
    }
}
/*
  Método virtual de QObject para capturar eventos de teclado y de mouse. Se lo instala
  llamando al método installEventFilter(). Si este método devuelve true entonces ninguna
  otra implementación de este método en clases derivadas capturará este evento.
*/
bool LineaDeTexto::eventFilter(QObject *obj, QEvent *e)
{
        if(obj == popup)
        {

            if(e->type()==QEvent::MouseButtonPress)
            {
                popup->hide();
                this->setFocus();
                return true;
            }
            if (e->type() == QEvent::KeyPress)  // si el evento es el que corresponde a una tecla presionada
            {
                bool reconocido = false;
                int key = static_cast<QKeyEvent*>(e)->key();
                switch (key) {
                case Qt::Key_Return:
                    this->completarLineEdit();
                    reconocido = true;
                    break;
                case Qt::Key_Up:
                case Qt::Key_Down:
                case Qt::Key_Home:
                case Qt::Key_End:
                case Qt::Key_PageUp:
                case Qt::Key_PageDown:
                    break;

                default:
                    // Hace que permanezca el cursor en el QLineEdit y poder seguir escribiendo
                    this->event(e);
                    popup->hide();
                    break;
                }
                return reconocido;
            }
        }
//     Esto es para que la clase base decida si necesita controlar los eventos
//     que no estamos capturando nosotros.
    return QWidget::eventFilter(obj, e);
}
