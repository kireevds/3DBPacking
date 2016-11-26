#include "result.h"
#include "ui_result.h"
#include <qtextcodec.h>

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    contInformation = new ContInfo;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget->setSortingEnabled(true); //неправильно работает: при переключении таблиц теряются столбцы

    connect(ui->showObjListButton, SIGNAL(clicked()), contInformation, SLOT(show()));
    connect(this, SIGNAL(sendData2(QList<Object*>*)), contInformation, SLOT(recieveData2(QList<Object*>*)));
}

Result::~Result()
{
    delete ui;
}

void Result::recieveData(QList<Container*>* c, QList<Object*>* o, qint64 t, QString f, QString type, QString dir, QString objrule, QString pkrule, QString spin, bool tes, int nap, int objr, int pkr, QString rd)
{
    qDebug()<<"recieved "<<nap<<" "<<objr<<" "<<pkr;
    contCount = 0;
    contNotCount = 0;
    objCount = 0;
    objNotCount = 0;
    avgOccup = 0;
    minOccup = 1000;
    maxOccup = -1;
    ui->comboBox->clear();

    testing = tes;
    napr = nap;
    objru = objr;
    PKru = pkr;
    resDir = rd;

    containers = c;
    objects = o;
    objNotCount = objects->size();
    time = t;
    fileN = f;
    fileNT = fileN;
    fileNT.chop(4);
    typeBox = type;
    direction = dir;
    objRule = objrule;
    PKRule = pkrule;
    spinStatus = spin;

    QString stime = QString::number(time);
    stime.chop(3);
    ui->timeCount->setText(stime + " мкс");

    fullContainers = new QList<Container*>;
    QListIterator<Container*> it(*containers);
    while (it.hasNext())
    {
        Container* PotCon = it.next();
        if(PotCon->myobjects->isEmpty())
        {
            contNotCount = contNotCount + 1;
        }
        else
        {
            Container * newCont = new Container(*PotCon);
            fullContainers->append(newCont);

            contCount = contCount + 1;
            objCount = objCount + PotCon->myobjects->size();

            //-----------Подсчет заполненного объёма------------
            float volCont = PotCon->width * PotCon->length * PotCon->height;
            float volObj = 0;
            QListIterator<Object*> ito(*PotCon->myobjects);
            while (ito.hasNext())
            {
                Object* tempObject = ito.next();
                volObj = volObj + tempObject->width * tempObject->length * tempObject->height;
            }
            float contOccup = volObj / volCont;
            avgOccup = avgOccup + contOccup;
            if(contOccup < minOccup)
                minOccup = contOccup;
            if(contOccup > maxOccup)
                maxOccup = contOccup;
            //-----------
        }
    }

    avgOccup = avgOccup / contCount;
    ui->averageOccup->setText(generateOccupation(avgOccup));
    ui->minOccup->setText(generateOccupation(minOccup));
    ui->maxOccup->setText(generateOccupation(maxOccup));

    ui->contCount->setText(QString::number(contCount));
    ui->contNotCount->setText(QString::number(contNotCount));
    ui->objCount->setText(QString::number(objCount));
    ui->objNotCount->setText(QString::number(objNotCount));
    on_contShowButton_clicked();


    for(int i=0; i<fullContainers->size(); i++)
    {
        ui->comboBox->addItem(QString::number(i+1));
    }

    if(testing)
        on_saveResultButton_clicked();
}

void Result::on_objShowButton_clicked()
{
    ui->objShowButton->setEnabled(false);
    ui->objNotShowButton->setEnabled(true);
    ui->contShowButton->setEnabled(true);
    ui->contNotShowButton->setEnabled(true);
    ui->objShow->show();
    ui->objNotShow->hide();
    ui->contShow->hide();
    ui->contNotShow->hide();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота");
    ui->tableWidget->setRowCount(objCount);
    int ccont = 0;
    QListIterator<Container*> it(*containers);
    while (it.hasNext())
    {
        Container* PotCon = it.next();
        if(!PotCon->myobjects->isEmpty())
        {
            QListIterator<Object*> ito(*PotCon->myobjects);
            while (ito.hasNext())
            {
                Object* tempObject = ito.next();
                QTableWidgetItem *item1 = new QTableWidgetItem;
                item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
                QString value1 = tempObject->type;
                item1->setData(Qt::EditRole, value1);
                ui->tableWidget->setItem(ccont,0, item1);

                QTableWidgetItem *item2 = new QTableWidgetItem;
                item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
                int value2 = tempObject->width;
                item2->setData(Qt::EditRole, value2);
                ui->tableWidget->setItem(ccont,1, item2);

                QTableWidgetItem *item3 = new QTableWidgetItem;
                item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
                int value3 = tempObject->length;
                item3->setData(Qt::EditRole, value3);
                ui->tableWidget->setItem(ccont,2, item3);

                QTableWidgetItem *item4 = new QTableWidgetItem;
                item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
                int value4 = tempObject->height;
                item4->setData(Qt::EditRole, value4);
                ui->tableWidget->setItem(ccont,3, item4);

                ccont = ccont + 1;
            }
        }
    }
}

void Result::on_objNotShowButton_clicked()
{
    ui->objShowButton->setEnabled(true);
    ui->objNotShowButton->setEnabled(false);
    ui->contShowButton->setEnabled(true);
    ui->contNotShowButton->setEnabled(true);
    ui->objShow->hide();
    ui->objNotShow->show();
    ui->contShow->hide();
    ui->contNotShow->hide();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота");
    ui->tableWidget->setRowCount(objNotCount);
    int ccont = 0;
    QListIterator<Object*> ito(*objects);
    while (ito.hasNext())
    {
        Object* tempObject = ito.next();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        QString value1 = tempObject->type;
        item1->setData(Qt::EditRole, value1);
        ui->tableWidget->setItem(ccont,0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        int value2 = tempObject->width;
        item2->setData(Qt::EditRole, value2);
        ui->tableWidget->setItem(ccont,1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        int value3 = tempObject->length;
        item3->setData(Qt::EditRole, value3);
        ui->tableWidget->setItem(ccont,2, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        int value4 = tempObject->height;
        item4->setData(Qt::EditRole, value4);
        ui->tableWidget->setItem(ccont,3, item4);

        ccont = ccont + 1;
    }
}

void Result::on_contShowButton_clicked()
{
    ui->objShowButton->setEnabled(true);
    ui->objNotShowButton->setEnabled(true);
    ui->contShowButton->setEnabled(false);
    ui->contNotShowButton->setEnabled(true);
    ui->objShow->hide();
    ui->objNotShow->hide();
    ui->contShow->show();
    ui->contNotShow->hide();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота");
    ui->tableWidget->setRowCount(contCount);
    int ccont = 0;
    QListIterator<Container*> it(*containers);
    while (it.hasNext())
    {
        Container* PotCon = it.next();
        if(!PotCon->myobjects->isEmpty())
        {
            QTableWidgetItem *item1 = new QTableWidgetItem;
            item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
            QString value1 = PotCon->type;
            item1->setData(Qt::EditRole, value1);
            ui->tableWidget->setItem(ccont,0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
            int value2 = PotCon->width;
            item2->setData(Qt::EditRole, value2);
            ui->tableWidget->setItem(ccont,1, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
            int value3 = PotCon->length;
            item3->setData(Qt::EditRole, value3);
            ui->tableWidget->setItem(ccont,2, item3);

            QTableWidgetItem *item4 = new QTableWidgetItem;
            item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
            int value4 = PotCon->height;
            item4->setData(Qt::EditRole, value4);
            ui->tableWidget->setItem(ccont,3, item4);

            ccont = ccont + 1;
        }
    }
}

void Result::on_contNotShowButton_clicked()
{
    ui->objShowButton->setEnabled(true);
    ui->objNotShowButton->setEnabled(true);
    ui->contShowButton->setEnabled(true);
    ui->contNotShowButton->setEnabled(false);
    ui->objShow->hide();
    ui->objNotShow->hide();
    ui->contShow->hide();
    ui->contNotShow->show();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота");
    ui->tableWidget->setRowCount(contNotCount);
    int ccont = 0;
    QListIterator<Container*> it(*containers);
    while (it.hasNext())
    {
        Container* PotCon = it.next();
        if(PotCon->myobjects->isEmpty())
        {
            QTableWidgetItem *item1 = new QTableWidgetItem;
            item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
            QString value1 = PotCon->type;
            item1->setData(Qt::EditRole, value1);
            ui->tableWidget->setItem(ccont,0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem;
            item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
            int value2 = PotCon->width;
            item2->setData(Qt::EditRole, value2);
            ui->tableWidget->setItem(ccont,1, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
            int value3 = PotCon->length;
            item3->setData(Qt::EditRole, value3);
            ui->tableWidget->setItem(ccont,2, item3);

            QTableWidgetItem *item4 = new QTableWidgetItem;
            item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
            int value4 = PotCon->height;
            item4->setData(Qt::EditRole, value4);
            ui->tableWidget->setItem(ccont,3, item4);

            ccont = ccont + 1;
        }
    }
}

QString Result::generateOccupation(float occup)
{
    QString SOccup = QString::number(occup);
    if(SOccup.left(1) == "1")
    {
        SOccup = "100" + QString(" %");
    }
    else
    {
        SOccup.remove(0,2);
        SOccup.insert(2, QString("."));
        SOccup = SOccup.left(7) + QString(" %");
    }
    return SOccup;
}

void Result::on_comboBox_currentIndexChanged(int index)
{
    if(index == -1)
        return;
    ui->contType->setText(fullContainers->at(index)->type);
    QString size = QString::number(fullContainers->at(index)->width);
    size.append(" * ");
    size.append(QString::number(fullContainers->at(index)->length));
    size.append(" * ");
    size.append(QString::number(fullContainers->at(index)->height));
    int contVol = fullContainers->at(index)->width * fullContainers->at(index)->length * fullContainers->at(index)->height;
    ui->contVol->setText(QString::number(contVol));
    ui->contSize->setText(size);
    ui->contObjCount->setText(QString::number(fullContainers->at(index)->myobjects->size()));
    int objVol=0;
    for(int i=0; i<fullContainers->at(index)->myobjects->size(); i++)
    {
        objVol = objVol + fullContainers->at(index)->myobjects->at(i)->width * fullContainers->at(index)->myobjects->at(i)->length * fullContainers->at(index)->myobjects->at(i)->height;
    }
    ui->contObjVol->setText(QString::number(objVol));
    float objVolF = (float)objVol / contVol;
    ui->contOccup->setText(generateOccupation(objVolF));
}

void Result::on_showObjListButton_clicked()
{
    int i = ui->comboBox->currentIndex();
    QList<Object*>* objList = fullContainers->at(i)->myobjects;
    emit sendData2(objList);
}

void Result::on_saveResultButton_clicked()
{
    QString fileName;

    if(!testing)
    {
            fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить результат в файл .csv"),
                                                    fileNT + "-результат",
                                                    tr("Save file (*.csv)"));
    }
    else
    {
        fileName = resDir+fileNT+"-результат-"+QString::number(napr)+"-"+QString::number(objru)+"-"+QString::number(PKru)+".csv";
    }

    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Внимание!", "Имя файла не выбрано");
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "Внимание!", "Ошибка создания файла"+fileName);
        return;
    }

    QTextStream out(&file);

//--------  Для записи текста в кодировке, открывающейся в excel, раскомментировать 2 строчки
    QTextCodec *codec = QTextCodec::codecForName("cp1251");
    out.setCodec(codec);
//--------

    out << QString("Результат упаковки по данным из файла")<<";"<<fileN<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Тип решаемой задачи")<<";"<<typeBox<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Направление загрузки контейнера")<<";"<<direction<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Правило выбора объектов")<<";"<<objRule<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Правило выбора ПК")<<";"<<PKRule<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Возможность вращения объектов")<<";"<<spinStatus<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out <<"- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;"<<endl;
    out << QString("Количество размещенных объектов")<<";"<<objCount<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Количество неразмещенных объектов")<<";"<<objNotCount<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Количество заполненных контейнеров")<<";"<<contCount<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Количество незаполненных контейнеров")<<";"<<contNotCount<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Средняя заполняемость контейнеров")<<";"<<QString(generateOccupation(avgOccup))<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Максимальная заполняемость контейнеров")<<";"<<QString(generateOccupation(maxOccup))<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out << QString("Минимальная заполняемость контейнеров")<<";"<<QString(generateOccupation(minOccup))<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    QString stime = QString::number(time);
    stime.chop(3);
    out << QString("Общее время размещения объектов")<<";"<<stime<<QString(" мкс")<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out <<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    out <<"- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;- - - - -;"<<endl;
    out <<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;

    for (int i=0; i<fullContainers->size(); i++)
    {
        out << QString("КОНТЕЙНЕР №")<<QString::number(i+1)<<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << QString("Тип контейнера")<<";"<<QString(fullContainers->at(i)->type)<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        QString size = QString::number(fullContainers->at(i)->width);
        size.append(" * ");
        size.append(QString::number(fullContainers->at(i)->length));
        size.append(" * ");
        size.append(QString::number(fullContainers->at(i)->height));
        out << QString("Размеры контейнера")<<";"<<QString(size)<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        int contVol = fullContainers->at(i)->width * fullContainers->at(i)->length * fullContainers->at(i)->height;
        out << QString("Объём контейнера")<<";"<<QString::number(contVol)<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << QString("Количество упакованных объектов в контейнере")<<";"<<QString::number(fullContainers->at(i)->myobjects->size())<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        int objVol=0;
        for(int index=0; index<fullContainers->at(i)->myobjects->size(); index++)
        {
            objVol = objVol + fullContainers->at(i)->myobjects->at(index)->width * fullContainers->at(i)->myobjects->at(index)->length * fullContainers->at(i)->myobjects->at(index)->height;
        }
        out << QString("Объём упакованных объектов")<<";"<<QString::number(objVol)<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        float objVolF = (float)objVol / contVol;
        out << QString("Заполняемость контейнера")<<";"<<QString(generateOccupation(objVolF))<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << QString("Список размещённых объектов в контейнере")<<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << ";"<<QString("Тип")<<";"<<QString("X")<<";"<<QString("Y")<<";"<<QString("Z")<<";"<<QString("Ширина")<<";"<<QString("Длина")<<";"<<QString("Высота")<<endl;
        QListIterator<Object*> ito(*fullContainers->at(i)->myobjects);
        int countobj = 1;
        while (ito.hasNext())
        {
            Object* tempObject = ito.next();
            out <<QString("№")<<QString::number(countobj)<<";"<<QString(tempObject->type)<<";"<<QString::number(tempObject->x)<<";"<<QString::number(tempObject->y)<<";"<<QString::number(tempObject->z)
               <<";"<<QString::number(tempObject->width)<<";"<<QString::number(tempObject->length)<<";"<<QString::number(tempObject->height)<<endl;
            countobj = countobj + 1;
        }
        out <<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out <<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
    }

    if (objNotCount != 0)
    {
        out <<"- - - - - -;- - - - - -;- - - - - -;- - - - - -;- - - - - -;- - - - - -;- - - - - -;"<<endl;
        out <<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << QString("Список неразмещенных объектов")<<";"<<";"<<";"<<";"<<";"<<";"<<";"<<endl;
        out << ";"<<QString("Тип")<<";"<<QString("Ширина")<<";"<<QString("Длина")<<";"<<QString("Высота")<<";"<<";"<<";"<<endl;
        QListIterator<Object*> ito(*objects);
        int countobj = 1;
        while (ito.hasNext())
        {
            Object* tempObject = ito.next();
            out <<QString("№")<<QString::number(countobj)<<";"<<QString(tempObject->type)<<";"<<QString::number(tempObject->width)<<";"<<QString::number(tempObject->length)<<";"<<QString::number(tempObject->height)<<";"<<";"<<";"<<endl;
            countobj = countobj + 1;
        }
    }

    file.close();

    qDebug()<<"recorded "<<napr<<" "<<objru<<" "<<PKru;
}
