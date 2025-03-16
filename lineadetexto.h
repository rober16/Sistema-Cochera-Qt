#include <QLineEdit>
#include <QString>
#include <QTreeWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <QHeaderView>

class LineaDeTexto : public QLineEdit  {
     Q_OBJECT

public:
    LineaDeTexto(QWidget *parent=0);
    LineaDeTexto(QString texto, QWidget *parent=0);
    LineaDeTexto(const LineaDeTexto &linea, QWidget *parent=0);

    LineaDeTexto& operator=(const LineaDeTexto &linea);
    LineaDeTexto operator+(const LineaDeTexto &linea);
    LineaDeTexto operator+(QString string);
    void setList(QStringList );

    int maxSugerencias;
private:
    bool eventFilter(QObject *,QEvent*);
    QStringList list;
    QTimer *timer;
    QTreeWidget *popup;
    void crearpopup();
    void completarpopup(QVector<QStringList> list);
private slots:
    void sugerencia();
    void completarLineEdit();
};
