#ifndef CONTINFOWINDOW_H
#define CONTINFOWINDOW_H

#include <QDialog>
#include <QString>
#include <object.h>

namespace Ui {
class Continfowindow;
}

class Continfowindow : public QDialog
{
    Q_OBJECT

public:
    explicit Continfowindow(QWidget *parent = 0);
    ~Continfowindow();

public slots:
    void recieveData2(QList<Object*>* objL);

private slots:
    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Continfowindow *ui;
    QList<Object*>* objects;
    int rowSC; //Индекс выбранной строки в таблице
};

#endif // CONTINFOWINDOW_H
