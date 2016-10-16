#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->containersTable->setRowCount(1);
    ui->containersTable->setColumnCount(5);
    ui->containersTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота" << "Количество");

    ui->objectsTable->setRowCount(1);
    ui->objectsTable->setColumnCount(5);
    ui->objectsTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота" << "Количество");
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
    ui->containersTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота" << "Количество");
    ui->objectsTable->clear();
    ui->objectsTable->setRowCount(1);
    ui->objectsTable->setHorizontalHeaderLabels(QStringList() << "Тип" << "Ширина" << "Длина" << "Высота" << "Количество");
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

    if(fileName == "")
        return;

    on_mDataClear_triggered();
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Внимание!", "Ошибка чтения файла " + fileName);
    }

    bool isOld;
    if(fileName.right(4) == ".txt") //Совместимость со старым форматом
    {
        file.readLine();
        file.readLine();
        isOld = true;
    }

    QString newline = file.readLine();
    int containersNumber = newline.toInt();
    ui->containersTable->setRowCount(containersNumber);

    for (int i = 0; i<containersNumber; i++) //Обработка списка контейнеров
    {
        newline = file.readLine();
        if(isOld)
        {
            newline.replace(QRegExp("\\s"),";"); //Для совместимости со старым форматом
        }

        QStringList datalist = newline.split(";");

        QTableWidgetItem *item = new QTableWidgetItem;
        int value = datalist[0].toInt(); //Количество контейнеров данного типа
        item->setData(Qt::EditRole, value);
        ui->containersTable->setItem(i,4, item);

        for (int j = 1; j<4; j++)
        {
            QTableWidgetItem *sizeItem = new QTableWidgetItem;
            value = datalist[j].toInt(); //Ширина, длина, высота контейнеров
            sizeItem->setData(Qt::EditRole, value);
            ui->containersTable->setItem(i,j, sizeItem);
        }

        if(isOld)
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = QString::number(i+1) + "-й тип"; //Тип контейнеров
            typeItem->setData(Qt::EditRole, containerType);
            ui->containersTable->setItem(i,0, typeItem);
        }
        else
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = datalist[4]; //Тип контейнеров
            typeItem->setData(Qt::EditRole, containerType);
            ui->containersTable->setItem(i,0, typeItem);
        }

    }


    newline = file.readLine();
    int objectsNumber = newline.toInt();
    ui->objectsTable->setRowCount(objectsNumber);

    for (int i = 0; i<objectsNumber; i++) //Обработка списка объектов
    {
        newline = file.readLine();
        if(isOld)
        {
            newline.replace(QRegExp("\\s"),";"); //Для совместимости со старым форматом
        }

        QStringList datalist = newline.split(";");

        QTableWidgetItem *item = new QTableWidgetItem;
        int value = datalist[0].toInt(); //Количество объектов данного типа
        item->setData(Qt::EditRole, value);
        ui->objectsTable->setItem(i,4, item);

        for (int j = 1; j<4; j++)
        {
            QTableWidgetItem *sizeItem = new QTableWidgetItem;
            value = datalist[j].toInt(); //Ширина, длина, высота объектов
            sizeItem->setData(Qt::EditRole, value);
            ui->objectsTable->setItem(i,j, sizeItem);
        }

        if(isOld)
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = QString::number(i+1) + "-й тип"; //Тип контейнеров
            typeItem->setData(Qt::EditRole, containerType);
            ui->objectsTable->setItem(i,0, typeItem);
        }
        else
        {
            QTableWidgetItem *typeItem = new QTableWidgetItem;
            QString containerType = datalist[4]; //Тип контейнеров
            typeItem->setData(Qt::EditRole, containerType);
            ui->objectsTable->setItem(i,0, typeItem);
        }

    }

    file.close();
}

void MainWindow::on_mDataSave_triggered()
{

}
