#ifndef DATASEND_H
#define DATASEND_H
#include <QString>
#include <container.h>

class DataSend
{
public:
    QList<Container*>* containersD;
    QList<Object*>* objectsD;
    QString stimeD; //Время заполнения
    QString fileND; //Имя файла с исходными данными
    QString typeTD; //Тип решаемой задачи (текст)
    QString dirTD; //Направление загрузки (текст)
    int dirD; //Направление загрузки
    QString objruleTD; //Правило выбора объектов (текст)
    int objruleD; //Правило выбора объектов
    QString pkruleTD; //Правило выбора ПК (текст)
    int pkruleD; //Правило выбора ПК
    QString spinTD; //Возможность вращения (текст)
    bool testingD; //Проводится тестирование?
    QString resDirD; //Директория хранения результатов
    bool winCode; //Кодировка CP1251
    bool testingAllD; //Сводное тестирование
    QString dirSourceNameD; //Название папки с файлами
    QString fileNameSRD; //Полный путь файла со сводным отчётом
};

#endif // DATASEND_H
