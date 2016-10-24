#include "container.h"

Container::Container()
{

}

Container::Container(QString t, int w, int l, int h, int dir, int pcr)
{
    type = t;
    width = w;
    length = l;
    height = h;

    direction = dir;
    PotConRule = pcr;

    myobjects = new QList<Object*>;
    myPotCons = new QList<Object*>;

    Object* newPotCon = new Object; //Базовый ПК
    newPotCon->width = w;
    newPotCon->length = l;
    newPotCon->height = h;
    newPotCon->x = 0;
    newPotCon->y = 0;
    newPotCon->z = 0;
    newPotCon->result = 0;
    myPotCons->append(newPotCon);
}


Container::Container(QString t, int w, int h, int dir, int pcr)
{
    type = t;
    width = w;
    length = 0;
    height = h;
    direction = dir;
    PotConRule = pcr;
}

Container::Container(QString t, int dir, int pcr)
{
    type = t;
    width = 0;
    length = 0;
    height = 0;
    direction = dir;
    PotConRule = pcr;
}

void Container::createmyPotConsList()
{
    int wx = myobjects->last()->width;
    int wy = myobjects->last()->length;
    int wz = myobjects->last()->height;
    int x = myobjects->last()->x;
    int y = myobjects->last()->y;
    int z = myobjects->last()->z;

    int end = myPotCons->size();
    for (int i = 0; i < end; i++) //Перекрытие объекта и ПК - создание нового ПК
    {
        Object* tempPotCon = new Object(*myPotCons->takeFirst());
        int px = tempPotCon->width;
        int py = tempPotCon->length;
        int pz = tempPotCon->height;
        int xk = tempPotCon->x;
        int yk = tempPotCon->y;
        int zk = tempPotCon->z;

        if (x>xk && x<(xk+px))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->width = x+xk;
            myPotCons->append(newPotCon);
        }

        if ((x+wx)>xk && (x+wx)<(xk+px))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->width = xk+px-x-wx;
            newPotCon->x = x+wx;
            myPotCons->append(newPotCon);
        }

        if ((x<=xk || x>=(xk+px)) && ((x+wx)<=xk || (x+wx)>=(xk+px)) && wx!=px) //Объект и ПК не пересекаются по x
        {
            Object * newPotCon = new Object(*tempPotCon);
            myPotCons->append(newPotCon);
        }


        if (y>yk && y<(yk+py))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->length = y+yk;
            myPotCons->append(newPotCon);
        }

        if ((y+wy)>yk && (y+wy)<(yk+py))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->length = yk+py-y-wy;
            newPotCon->y = y+wy;
            myPotCons->append(newPotCon);
        }

        if ((y<=yk || y>=(yk+py)) && ((y+wy)<=yk || (y+wy)>=(yk+py)) && wy!=py) //Объект и ПК не пересекаются по y
        {
            Object * newPotCon = new Object(*tempPotCon);
            myPotCons->append(newPotCon);
        }


        if (z>zk && z<(zk+pz))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->height = z+zk;
            myPotCons->append(newPotCon);
        }

        if ((z+wz)>zk && (z+wz)<(zk+pz))
        {
            Object * newPotCon = new Object(*tempPotCon);
            newPotCon->height = zk+pz-z-wz;
            newPotCon->z = z+wz;
            myPotCons->append(newPotCon);
        }

        if ((z<=zk || z>=(zk+pz)) && ((z+wz)<=zk || (z+wz)>=(zk+pz)) && wz!=pz) //Объект и ПК не пересекаются по z
        {
            Object * newPotCon = new Object(*tempPotCon);
            myPotCons->append(newPotCon);
        }
    }

    checkinside();

//    qDebug()<<"o"<<myobjects->size();
//    qDebug()<<"pk"<<myPotCons->size();
//    qDebug()<<"obj"<<obj->x<<obj->y<<obj->z<<obj->height<<obj->length<<obj->width;
//    qDebug()<<"pk"<<PotCon->x<<PotCon->y<<PotCon->z<<PotCon->height<<PotCon->length<<PotCon->width;
}

void Container::checkinside()
{
    for (int i = 0; i< myPotCons->size()-1; i++) //Проверка ПК на вложенность
    {
        Object* PotCon1 = myPotCons->at(i);
        for (int j = i+1; j< myPotCons->size(); j++)
        {
            Object* PotCon2 = myPotCons->at(j);
            if ((PotCon1->x >= PotCon2->x)  &&  ((PotCon1->x+PotCon1->width) <= (PotCon2->x+PotCon2->width)) &&
                    (PotCon1->y >= PotCon2->y)  &&  ((PotCon1->y+PotCon1->length) <= (PotCon2->y+PotCon2->length)) &&
                    (PotCon1->z >= PotCon2->z)  &&  ((PotCon1->z+PotCon1->height) <= (PotCon2->z+PotCon2->height)))
                PotCon1->flag = true;
            if ((PotCon2->x >= PotCon1->x)  &&  ((PotCon2->x+PotCon2->width) <= (PotCon1->x+PotCon1->width)) &&
                    (PotCon2->y >= PotCon1->y)  &&  ((PotCon2->y+PotCon2->length) <= (PotCon1->y+PotCon1->length)) &&
                    (PotCon2->z >= PotCon1->z)  &&  ((PotCon2->z+PotCon2->height) <= (PotCon1->z+PotCon1->height)))
                PotCon2->flag = true;
        }
    }

    QMutableListIterator<Object*> it(*myPotCons); //Удаление вложенных ПК
    while (it.hasNext())
    {
        Object* PotCon = it.next();
        if(PotCon->flag == true)
            it.remove();
    }

//    qDebug()<<"Spisok PC";
//    QMutableListIterator<Object*> it3(*myPotCons);
//    while (it3.hasNext())
//    {
//        Object* PotCon = it3.next();
//        qDebug()<<"pk"<<PotCon->x<<PotCon->y<<PotCon->z<<" "<<PotCon->width<<PotCon->length<<PotCon->height;
//    }

}

void Container::sortPotCon(Object *obj)
{
    switch(PotConRule)
    {
    case 0:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->result = myPotCons->at(it)->width * myPotCons->at(it)->length * myPotCons->at(it)->height;
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowV);
        break;

    case 1:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->result = myPotCons->at(it)->width * myPotCons->at(it)->length * myPotCons->at(it)->height;
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::lowToMaxV);
        break;

    case 2:
    {
        switch (direction)                                      //в зависимости от направления загрузки
        {
        case 0:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCXYZ);
            break;
        case 1:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCXZY);
            break;
        case 2:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCYXZ);
            break;
        case 3:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCYZX);
            break;
        case 4:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCZXY);
            break;
        case 5:
            std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxToLowCZYX);
            break;
        }
    }
        break;

    case 3:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->result = myPotCons->at(it)->width * myPotCons->at(it)->length;
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxW1W2minW3);
        break;

    case 4:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->result = myPotCons->at(it)->width * myPotCons->at(it)->length;
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::minW1W2maxW3);
        break;

    case 5:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->wx = QString::number(obj->width);
            myPotCons->at(it)->wy = QString::number(obj->length);
            myPotCons->at(it)->wz = QString::number(obj->height);
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::minPw_w);
        break;

    case 6:
        for (int it = 0; it < myPotCons->size(); it++)
        {
            myPotCons->at(it)->wx = QString::number(obj->width);
            myPotCons->at(it)->wy = QString::number(obj->length);
            myPotCons->at(it)->wz = QString::number(obj->height);
        }
        std::sort(myPotCons->begin(), myPotCons->end(), &SortingAlg::maxPw_w);
        break;
    }
}

bool Container::locateObject(Object* obj)
{
    sortPotCon(obj);
    QMutableListIterator<Object*> it(*myPotCons);
    while (it.hasNext())
    {
        Object* PotCon = it.next();
        if(PotCon->width >= obj->width && PotCon->length >= obj->length && PotCon->height >= obj->height) //есть ли ПК, в который поместится obj
        {
            obj->x = PotCon->x;
            obj->y = PotCon->y;
            obj->z = PotCon->z;
            myobjects->append(obj);
            createmyPotConsList();
            return true;
        }
    }
    return false; //Объект не размещён
}
