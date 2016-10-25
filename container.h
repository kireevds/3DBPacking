#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <QList>
#include <object.h>
#include <QtDebug>
#include <sortingalg.h>


class Container
{
public:

    QString type;
    int width; //ширина
    int length; //длина
    int height; //высота

    int direction; //направление загрузки
    int PotConRule; //Правило выбора ПК

    QList<Object*>* myPotCons; //Список потенциальных контейнеров в данном контейнере
    void createmyPotConsList(); //Cоздание списка потенциальных контейнеров в данном контейнере

    QList<Object*>* myobjects; //Список размещённых объектов в данном контейнере

    Container();
    Container(QString t, int w, int l, int h, int dir, int pcr);
    Container(QString t, int w, int h, int dir, int pcr);
    Container(QString t, int dir, int pcr);
    Container(const Container &cont);

    bool locateObject(Object *obj); //Разместить объект
    void checkinside(); //Проверить ПК на вложенность
    void sortPotCon(Object* obj); //Сортировка ПК

};

#endif // CONTAINER_H
