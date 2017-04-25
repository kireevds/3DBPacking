#ifndef CONTINFO_H
#define CONTINFO_H

#include <QWidget>
#include <QString>
#include <object.h>
#include <container.h>

namespace Ui {
class ContInfo;
}

class ContInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ContInfo(QWidget *parent = 0);
    ~ContInfo();

public slots:
//    void recieveData2(QList<Object*>* objL);
    void recieveData2(Container* cont);


private slots:
    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::ContInfo *ui;
    QList<Object*>* objects;
    int rowSC; //Индекс выбранной строки в таблице
};

#endif // CONTINFO_H
