#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    contInformation = new ContInfo;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->showObjListButton, SIGNAL(clicked()), contInformation, SLOT(show()));
    connect(this, SIGNAL(sendData2(QList<Object*>*)), contInformation, SLOT(recieveData2(QList<Object*>*)));
}

Result::~Result()
{
    delete ui;
}

void Result::recieveData(QList<Container*>* c, QList<Object*>* o, qint64 t) //Разобраться, почему вызывается n++ раз!!!!!!!!!!
{
    contCount = 0;
    contNotCount = 0;
    objCount = 0;
    objNotCount = 0;
    avgOccup = 0;
    minOccup = 1000;
    maxOccup = -1;

    containers = c;
    objects = o;
    objNotCount = objects->size();
    time = t;
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
    int ccont = objCount-1;                                     //Таблица заполняется снизу!!!!!!!!!!Переделать
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

                ccont = ccont - 1;
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
    int ccont = objNotCount-1;
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

        ccont = ccont - 1;
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
    int ccont = contCount-1;                                     //Таблица заполняется снизу!!!!!!!!!!Переделать
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

            ccont = ccont - 1;
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
    int ccont = contNotCount-1;
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

            ccont = ccont - 1;
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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить данные в файл .csv"),
                                                    QDir::currentPath(),
                                                    tr("Save file (*.csv)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Внимание!", "Имя файла не выбрано");
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "Внимание!", "Ошибка создания файла");
        return;
    }

    QTextStream out(&file);
    out << "Результат упаковки объектов в контейнер"<<endl;

                                                                                          // Дописать функцию, найти причину проблемы с кодировкой

    file.close();
}
