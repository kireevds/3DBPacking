#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QElapsedTimer>
#include <container.h>
#include <object.h>
#include <sortingalg.h>
#include <QFileInfoList>
#include <QDir>
#include <result.h>
#include <datasend.h>
#include <QProgressDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendData(DataSend* ds); //Передача данных в форму с результатом

private slots:
    void on_newContainerButton_clicked(); //Добавить строку под контейнер

    void on_newObjectButton_clicked(); //Добавить строку под объект

    void on_deleteContainerButton_clicked(); //Удалить строку с данными о контейнере

    void on_deleteObjectButton_clicked(); //Удалить строку с данными об объекте

    void on_mDataClear_triggered(); //Очистить обе таблицы

    void on_mExit_triggered(); //Меню - Выход

    void on_mDataLoad_triggered(); //Меню - Загрузить данные

    void on_mDataSave_triggered(); //Меню - Сохранить данные

    void on_typeBox_currentIndexChanged(int index); //смена типа задачи

    void on_packButton_clicked(); //главная функция

    void on_mTesting_triggered(); //Массовая упаковка - тестирование

    void on_mTestingAll_triggered();

private:
    Result* resultform;
    Ui::MainWindow *ui;
    DataSend* dataS;
    QList<Container*>* containers;
    QList<Object*>* objects;
    QElapsedTimer timer;
    qint64 time; //Время заполнения

    QString fileName; //полное имя файла для открытия
    QString sourceDir; //директория с файлами-источниками
    QFileInfoList sourceFiles; //список файлов-источников

    bool testing;

    void checkTypeIndex(); //показать колонки таблицы в зависимости от типа задачи
    void createContainersList(); //создание списка контейнеров по табличным данным
    void createObjectsList(); //создание списка объектов по табличным данным
    void sortObjectsList(); //сортировка списка объектов по условию правила выбора
    void locate(); //выбор функции размещения объектов
    void locateInManyContainers();
    void makeData(); //Сгенерировать передаваемые данные
    void hideShowTesting(); //Показать\скрыть объекты интерфейса во время теста

};

#endif // MAINWINDOW_H
