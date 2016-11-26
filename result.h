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
    void sendData2(QList<Object*>* objL);


public slots:
    void recieveData(QList<Container*>* c, QList<Object *>* o, qint64 t, QString f, QString type, QString dir, QString objrule, QString pkrule, QString spin, bool tes, int nap, int objr, int pkr, QString rd);

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

    QString generateOccupation(float occup); //Подсчёт процентов заполнения
    qint64 time; //Время заполнения
    QString fileN; //Имя файла с исходными данными
    QString fileNT; //Имя файла без расширения с исходными данными
    QString typeBox; //Тип задачи
    QString direction; //Направление загрузки
    QString objRule; //Правило выбора объектов
    QString PKRule; //Правило выбора ПК
    QString spinStatus; //Возможность вращения

    int contCount; //Количество заполненных контейнеров
    int contNotCount; //Количество незаполненных контейнеров
    int objCount; //Количество размещенных объектов
    int objNotCount; //Количество неразмещенных объектов
    float avgOccup; //Средняя заполняемость контейнеров
    float minOccup; //Минимальная заполняемость контейнеров
    float maxOccup; //Максимальная заполняемость контейнеров

    bool testing; //Для теста
    int napr;
    int objru;
    int PKru;
    QString resDir;
};

#endif // RESULT_H
