#ifndef BOTON_H
#define BOTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>

namespace Ui {
class Boton;
}

class Boton : public QWidget
{
    Q_OBJECT

public:
    explicit Boton(QWidget *parent = nullptr);
    ~Boton();

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent * );

private:
    Ui::Boton *ui;
    QImage image;

signals:
    void signal_click();

};
#endif // BOTON_H
