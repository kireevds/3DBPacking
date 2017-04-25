#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QElapsedTimer>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <container.h>
#include <object.h>
#include <continfo.h>
#include <datasend.h>

namespace Ui {
class Result;
}

class Result : public QWidget
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = 0);
    ~Result();

signals:
//    void sendData2(QList<Object*>* objL);
    void sendData2(Container*);


public slots:
    void recieveData(DataSend *ds);

private slots:
    void on_objShowButton_clicked();

    void on_objNotShowButton_clicked();

    void on_contShowButton_clicked(); //Отобразить список контейнеров

    void on_contNotShowButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_showObjListButton_clicked();

    void on_saveResultButton_clicked();


private:
    ContInfo* contInformation;
    Ui::Result *ui;
    QList<Object*>* objects;
    QList<Container*>* containers;
    QList<Container*>* fullContainers;
    DataSend* dtr;

    QString generateOccupation(float occup); //Подсчёт процентов заполнения

    QString fileNT; //Имя файла без расширения с исходными данными

    int contCount; //Количество заполненных контейнеров
    int contNotCount; //Количество незаполненных контейнеров
    int objCount; //Количество размещенных объектов
    int objNotCount; //Количество неразмещенных объектов
    float avgOccup; //Средняя заполняемость контейнеров
    float minOccup; //Минимальная заполняемость контейнеров
    float maxOccup; //Максимальная заполняемость контейнеров

    bool testing; //Для теста

};

#endif // RESULT_H
