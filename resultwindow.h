#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QElapsedTimer>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <container.h>
#include <object.h>
#include <continfowindow.h>

namespace Ui {
class Resultwindow;
}

class Resultwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Resultwindow(QWidget *parent = 0);
    ~Resultwindow();

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

    void on_closeButton_clicked();

private:
    Continfowindow* contInformation;
    Ui::Resultwindow *ui;
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

#endif // RESULTWINDOW_H
