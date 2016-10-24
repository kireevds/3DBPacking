#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->containersTable->setRowCount(1);
    ui->containersTable->setColumnCount(5);
    ui->containersTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" <<
                                                   "Высота" << "Количество");

    ui->objectsTable->setRowCount(1);
    ui->objectsTable->setColumnCount(5);
    ui->objectsTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" <<
                                                "Высота" << "Количество");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newContainerButton_clicked()
{
    if(ui->typeBox->currentIndex()!= 0 && ui->containersTable->rowCount()!=0) //Проверка типа задачи
        return;
    ui->containersTable->insertRow(ui->containersTable->rowCount());
}

void MainWindow::on_deleteContainerButton_clicked()
{
    ui->containersTable->removeRow(ui->containersTable->currentRow());
}

void MainWindow::on_newObjectButton_clicked()
{
    ui->objectsTable->insertRow(ui->objectsTable->rowCount());
}

void MainWindow::on_deleteObjectButton_clicked()
{
    ui->objectsTable->removeRow(ui->objectsTable->currentRow());
}

void MainWindow::on_mDataClear_triggered()
{
    ui->containersTable->clear();
    ui->containersTable->setRowCount(1);
    ui->containersTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" <<
                                                   "Высота" << "Количество");
    ui->objectsTable->clear();
    ui->objectsTable->setRowCount(1);
    ui->objectsTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" <<
                                                "Высота" << "Количество");
}

void MainWindow::on_mExit_triggered()
{
    this->close();
}

void MainWindow::on_mDataLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Выберите файл с данными"),
                                                    QDir::currentPath(),
                                                    tr("Data Files (*.txt *.csv)"));

    if(fileName.isEmpty())
        return;

    on_mDataClear_triggered();
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Внимание!", "Ошибка чтения файла " + fileName);
        return;
    }

    bool isOld = false;
    if(fileName.right(4) == ".txt") //Совместимость со старым форматом
    {
        file.readLine();
        file.readLine();
        isOld = true;
    }

    QString newline = file.readLine();
    QStringList datalist = newline.split(";");
    int containersNumber = datalist[0].toInt();
    ui->containersTable->setRowCount(containersNumber);

    for (int i = 0; i<containersNumber; i++) //Обработка списка контейнеров
    {
        newline = file.readLine();
        if(isOld)
        {
            newline.replace(QRegExp("\\s"),";"); //Для совместимости со старым форматом
        }

        datalist = newline.split(";");

        QTableWidgetItem *item = new QTableWidgetItem;
        int value = datalist[0].toInt(); //Количество контейнеров данного типа
        item->setData(Qt::EditRole, value);
        ui->containersTable->setItem(i,4, item);

        for (int j = 1; j<4; j++)
        {
            QTableWidgetItem *sizeItem = new QTableWidgetItem;
            value = datalist[j].toInt(); //Ширина, длина, высота контейнера
            sizeItem->setData(Qt::EditRole, value);
            ui->containersTable->setItem(i,j, sizeItem);
        }

        if(isOld)
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = QString::number(i+1) + "-й тип"; //Тип контейнера
            typeItem->setData(Qt::EditRole, containerType);
            ui->containersTable->setItem(i,0, typeItem);
        }
        else
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = datalist[4].trimmed(); //Тип контейнера
            typeItem->setData(Qt::EditRole, containerType);
            ui->containersTable->setItem(i,0, typeItem);
        }

    }


    newline = file.readLine();
    datalist = newline.split(";");
    int objectsNumber = datalist[0].toInt();
    ui->objectsTable->setRowCount(objectsNumber);

    for (int i = 0; i<objectsNumber; i++) //Обработка списка объектов
    {
        newline = file.readLine();
        if(isOld)
        {
            newline.replace(QRegExp("\\s"),";"); //Для совместимости со старым форматом
        }

        datalist = newline.split(";");

        QTableWidgetItem *item = new QTableWidgetItem;
        int value = datalist[0].toInt(); //Количество объектов данного типа
        item->setData(Qt::EditRole, value);
        ui->objectsTable->setItem(i,4, item);

        for (int j = 1; j<4; j++)
        {
            QTableWidgetItem *sizeItem = new QTableWidgetItem;
            value = datalist[j].toInt(); //Ширина, длина, высота объекта
            sizeItem->setData(Qt::EditRole, value);
            ui->objectsTable->setItem(i,j, sizeItem);
        }

        if(isOld)
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = QString::number(i+1) + "-й тип"; //Тип объекта
            typeItem->setData(Qt::EditRole, containerType);
            ui->objectsTable->setItem(i,0, typeItem);
        }
        else
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = datalist[4].trimmed(); //Тип объекта
            typeItem->setData(Qt::EditRole, containerType);
            ui->objectsTable->setItem(i,0, typeItem);
        }

    }

    file.close();

    checkTypeIndex();
}

void MainWindow::on_mDataSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить данные в файл .csv"),
                                                    QDir::currentPath(),
                                                    tr("Address Book (*.csv)"));
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

    out << ui->containersTable->rowCount() << ";"<< ";"<< ";"<< ";"<< endl;
    for(int i = 0; i < ui->containersTable->rowCount(); i++)
    {
        out << ui->containersTable->item(i,4)->text() << ";" <<
               ui->containersTable->item(i,1)->text() << ";" <<
               ui->containersTable->item(i,2)->text() << ";" <<
               ui->containersTable->item(i,3)->text() << ";" <<
               ui->containersTable->item(i,0)->text() << endl;
    }

    out << ui->objectsTable->rowCount() << ";"<< ";"<< ";"<< ";"<< endl;
    for(int i = 0; i < ui->objectsTable->rowCount(); i++)
    {
        out << ui->objectsTable->item(i,4)->text() << ";" <<
               ui->objectsTable->item(i,1)->text() << ";" <<
               ui->objectsTable->item(i,2)->text() << ";" <<
               ui->objectsTable->item(i,3)->text() << ";" <<
               ui->objectsTable->item(i,0)->text() << endl;
    }

    file.close();
}


void MainWindow::on_typeBox_currentIndexChanged(int index)
{
    Q_UNUSED (index);
    checkTypeIndex();
}

void MainWindow::checkTypeIndex()
{
    int index = ui->typeBox->currentIndex();

    switch(index)
    {
    case 0:
        ui->containersTable->showColumn(1);
        ui->containersTable->showColumn(2);
        ui->containersTable->showColumn(3);
        ui->containersTable->showColumn(4);
        break;

    case 1:
        ui->containersTable->setRowCount(1);
        ui->containersTable->showColumn(1);
        ui->containersTable->showColumn(2);
        ui->containersTable->showColumn(3);
        ui->containersTable->hideColumn(4);
        break;

    case 2:
        ui->containersTable->setRowCount(1);
        ui->containersTable->showColumn(1);
        ui->containersTable->hideColumn(2);
        ui->containersTable->showColumn(3);
        ui->containersTable->hideColumn(4);
        break;

    case 3:
        ui->containersTable->setRowCount(1);
        ui->containersTable->hideColumn(1);
        ui->containersTable->hideColumn(2);
        ui->containersTable->hideColumn(3);
        ui->containersTable->hideColumn(4);
        break;
    }
}

void MainWindow::createContainersList()
{
    int typeoftask = ui->typeBox->currentIndex();
    int dir = ui->directionBox->currentIndex();
    int pcr = ui->pkRuleBox->currentIndex();
    containers = new QList<Container*>;

    for (int i = 0; i < ui->containersTable->rowCount(); i++)
    {
        QString type = ui->containersTable->item(i,0)->data(Qt::EditRole).toString();
        int width = ui->containersTable->item(i,1)->data(Qt::EditRole).toInt();
        int length = ui->containersTable->item(i,2)->data(Qt::EditRole).toInt();
        int height = ui->containersTable->item(i,3)->data(Qt::EditRole).toInt();
        int count = ui->containersTable->item(i,4)->data(Qt::EditRole).toInt();

        switch(typeoftask)
        {
        case 0:
        {
            for (int c = 0; c < count; c++)
            {
                Container* newcontainer = new Container (type, width, length, height, dir, pcr);
                containers->append(newcontainer);
            }
            break;
        }

        case 1:
        {
            Container* newcontainer = new Container (type, width, length, height, dir, pcr);
            containers->append(newcontainer);
            break;
        }

        case 2:
        {
            Container* newcontainer = new Container (type, width, height, dir, pcr);
            containers->append(newcontainer);
            break;
        }

        case 3:
        {
            Container* newcontainer = new Container (type, dir, pcr);
            containers->append(newcontainer);
            break;
        }
        }
    }
}

void MainWindow::createObjectsList()
{
    int objectrule = ui->objectsRuleBox->currentIndex();
    objects = new QList<Object*>;
    for (int i=0; i<ui->objectsTable->rowCount(); i++)
    {
        QString type = ui->objectsTable->item(i,0)->data(Qt::EditRole).toString();
        int width = ui->objectsTable->item(i,1)->data(Qt::EditRole).toInt();
        int length = ui->objectsTable->item(i,2)->data(Qt::EditRole).toInt();
        int height = ui->objectsTable->item(i,3)->data(Qt::EditRole).toInt();
        int count = ui->objectsTable->item(i,4)->data(Qt::EditRole).toInt();

        switch(objectrule)
        {
        case 0: //0 или 1
        case 1:
        {
            for (int c = 0; c < count; c++)
            {
                Object* newobject = new Object (type, width, length, height, width*length*height);
                objects->append(newobject);
            }
            break;
        }

        case 2:
        {
            for (int c = 0; c < count; c++)
            {
                Object* newobject = new Object (type, width, length, height, 0);
                objects->append(newobject);
            }
            break;
        }

        case 3:
        case 4:
        {
            for (int c = 0; c < count; c++)
            {
                Object* newobject = new Object (type, width, length, height, width*length);
                objects->append(newobject);
            }
            break;
        }
        }
    }
}


void MainWindow::sortObjectsList()
{
    int objectrule = ui->objectsRuleBox->currentIndex();
    switch(objectrule)
    {
    case 0:
        std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowV);
        break;
    case 1:
        std::sort(objects->begin(), objects->end(), &SortingAlg::lowToMaxV);
        break;

    case 2:
    {
        int direction = ui->directionBox->currentIndex();
        switch (direction)                                      //в зависимости от направления загрузки
        {
        case 0:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowXYZ);
            break;
        case 1:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowXZY);
            break;
        case 2:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowYXZ);
            break;
        case 3:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowYZX);
            break;
        case 4:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowZXY);
            break;
        case 5:
            std::sort(objects->begin(), objects->end(), &SortingAlg::maxToLowZYX);
            break;
        }
    }
        break;

    case 3:
        std::sort(objects->begin(), objects->end(), &SortingAlg::maxW1W2minW3);
        break;
    case 4:
        std::sort(objects->begin(), objects->end(), &SortingAlg::minW1W2maxW3);
        break;
    }
}

void MainWindow::locate()
{
    int typeoftask = ui->typeBox->currentIndex();
    switch(typeoftask)
    {
    case 0:
        locateInManyContainers();
        break;

    case 1:
        break;

    case 2:
        break;

    case 3:
        break;
    }
}

void MainWindow::locateInManyContainers()
{
    QMutableListIterator<Object*> it(*objects);
    while (it.hasNext()) //Перебор сортированного списка объектов
    {
        Object* obj = it.next();
        QMutableListIterator<Container*> itc(*containers);
        while (itc.hasNext()) //Перебор списка контейнеров
        {
            Container* con = itc.next();
            if (con->locateObject(obj)) //Если объект размещён, выход из обхода контейнеров
            {
                it.remove();
                break;
            }
        }
    }
}

void MainWindow::on_packButton_clicked()
{
    qDebug()<<"start ";
    createContainersList();
    createObjectsList();
    sortObjectsList();
    locate();
    qDebug()<<"end";

}


//
//    QMessageBox::information(this, "Внимание!", QString::number(objects->count()));
//ui->objectsTable->sortByColumn(1, Qt::AscendingOrder);
//ui->objectsTable->sortItems(1, Qt::AscendingOrder); //Вроде как без разницы?
