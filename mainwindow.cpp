#include "mainwindow.h"
#include "ui_mainwindow.h"

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

