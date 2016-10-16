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
    ui->objectsTable->clear();
    ui->objectsTable->setRowCount(1);
}

void MainWindow::on_mExit_triggered()
{
    this->close();
}

void MainWindow::on_mDataLoad_triggered()
{

}

void MainWindow::on_mDataSave_triggered()
{

}
