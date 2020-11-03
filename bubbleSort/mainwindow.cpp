#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qrandom.h>
#include <QtAlgorithms>
#include <math.h>
#include <QElapsedTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showSwapIndxs(int i1, int i2, int row, int iter){
    int newColCnt = ui->tableWidget->columnCount();

    QTableWidgetItem* itm = new QTableWidgetItem;
    itm->setText(QString::number(i1) + " <-> " + QString::number(i2) +" Iter: " + QString::number(iter));
    ui->tableWidget->setItem(row,newColCnt-1, itm);
}
void MainWindow::printVect(QVector<double>& v, int row){
    for(int i = 0; i < v.size(); ++i){
       QTableWidgetItem* itm = new QTableWidgetItem;

       itm->setText(QString::number(v[i]));


       ui->tableWidget->setItem(row,i, itm);
    }



}

QPair<int, int> MainWindow::findNegativeIndexes(QVector<double>& v){
    QPair<int, int> indexes = {0, v.size()-1};
    QVector<double> tmp(v);

    indexes.first = v.indexOf(*std::find_if(v.begin(),v.end(),[](double n){return (n < 0)?true:false;})) + 1;

    std::reverse_copy(v.begin(), v.end(), tmp.begin());
    indexes.second = v.size() - 1 - tmp.indexOf(*std::find_if(tmp.begin(),tmp.end(), [](double n){return (n < 0)?true:false;}));
    if(indexes.first >= indexes.second)
        indexes = {0,v.size() - 1};

    return indexes;
}
QVector<double> MainWindow::bubbleSort(QVector<double>& v){
    QPair<int, int> limits = findNegativeIndexes(v);
    int s = v.size();
    int k = 1;
        for(int i = 0; i < s; ++i){
            int stop = true;
            for(auto j = limits.first; j < limits.second-1; ++j){

                if(v[j] > v[j+1]){
                    qSwap(v[j], v[j+1]);
                    stop = false;
                    if(!ui->ifClock->isChecked()){
                        ui->tableWidget->setRowCount(k+1);
                        showSwapIndxs(j,j+1,k, i);
                        printVect(v, k++);
                    }
                }
            }

            if(stop){
                break;
            }
        }
    return v;
}

void MainWindow::fillTheRow()
{
    for (int i = 0;i<ui->cntOfNums->value();++i) {
     QTableWidgetItem* itm = new QTableWidgetItem;
     itm->setText(QString::number((double(qrand()%30-10)/double(qrand()%10+1))));

     ui->tableWidget->setItem(0,i,itm);
    }
}



void MainWindow::on_cntOfNums_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
    ui->tableWidget->setRowCount(1);
}

void MainWindow::on_sortB_clicked()
{
    QVector<double> arr;
    int s = ui->cntOfNums->value();
    fillTheRow();
    for (int i = 0;i < s; ++i) {
        arr.append(ui->tableWidget->item(0,i)->text().toDouble());
    }
    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+1);
    printVect(arr,0);

    QElapsedTimer t;
    long long time;
    if(ui->ifClock->isChecked())
    {
        t.start();
        bubbleSort(arr);
        time = t.nsecsElapsed();
        ui->tableWidget->setRowCount(2);
        printVect(arr,1);
        ui->time->setText(QString::number(time/1000) + "ms");
    }else{
        bubbleSort(arr);

    }

}
