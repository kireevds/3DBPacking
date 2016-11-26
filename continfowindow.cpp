#include "continfowindow.h"
#include "ui_continfowindow.h"

Continfowindow::Continfowindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Continfowindow)
{
    ui->setupUi(this);
}

Continfowindow::~Continfowindow()
{
    delete ui;
}

void Continfowindow::recieveData2(QList<Object *> *objL)
{
    objects = objL;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Тип" << "X" << "Y" << "Z" << "Ширина" << "Длина" << "Высота");
    ui->tableWidget->setRowCount(objects->size());
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    rowSC = 0;
    ui->tableWidget->selectRow(rowSC);

    ui->horizontalSlider->setRange(0,objects->size()-1);
    ui->horizontalSlider->setSingleStep(1);
    ui->horizontalSlider->setValue(0);

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
        int value2 = tempObject->x;
        item2->setData(Qt::EditRole, value2);
        ui->tableWidget->setItem(ccont,1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        int value3 = tempObject->y;
        item3->setData(Qt::EditRole, value3);
        ui->tableWidget->setItem(ccont,2, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        int value4 = tempObject->z;
        item4->setData(Qt::EditRole, value4);
        ui->tableWidget->setItem(ccont,3, item4);

        QTableWidgetItem *item5 = new QTableWidgetItem;
        item5->setFlags(item5->flags() ^ Qt::ItemIsEditable);
        int value5 = tempObject->width;
        item5->setData(Qt::EditRole, value5);
        ui->tableWidget->setItem(ccont,4, item5);

        QTableWidgetItem *item6 = new QTableWidgetItem;
        item6->setFlags(item6->flags() ^ Qt::ItemIsEditable);
        int value6 = tempObject->length;
        item6->setData(Qt::EditRole, value6);
        ui->tableWidget->setItem(ccont,5, item6);

        QTableWidgetItem *item7 = new QTableWidgetItem;
        item7->setFlags(item7->flags() ^ Qt::ItemIsEditable);
        int value7 = tempObject->height;
        item7->setData(Qt::EditRole, value7);
        ui->tableWidget->setItem(ccont,6, item7);

        ccont = ccont + 1;
    }
}

void Continfowindow::on_upButton_clicked()
{
    if (rowSC != 0)
        rowSC = rowSC - 1;
    ui->tableWidget->selectRow(rowSC);
    ui->horizontalSlider->setValue(rowSC);
}

void Continfowindow::on_downButton_clicked()
{
    if (rowSC != ui->tableWidget->rowCount() -1)
        rowSC = rowSC + 1;
    ui->tableWidget->selectRow(rowSC);
    ui->horizontalSlider->setValue(rowSC);
}

void Continfowindow::on_tableWidget_cellClicked(int row, int column)
{
    rowSC = row;
    Q_UNUSED (column);
    ui->horizontalSlider->setValue(rowSC);
}

void Continfowindow::on_horizontalSlider_valueChanged(int value)
{
    rowSC = value;
    ui->tableWidget->selectRow(rowSC);
}
