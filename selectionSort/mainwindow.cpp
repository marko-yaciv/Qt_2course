#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
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
void MainWindow::printVect(QVector<int>& v, int row){
    for(int i=0; i < v.size(); ++i){
       QTableWidgetItem* itm = new QTableWidgetItem;
       itm->setText(QString::number(v[i]));

       ui->tableWidget->setItem(row,i, itm);
    }
}

void MainWindow::showSwapIndxs(int i1, int i2, int row, int iter){
    int newColCnt = ui->tableWidget->columnCount();

    QTableWidgetItem* itm = new QTableWidgetItem;
    QTableWidgetItem* iteration = new QTableWidgetItem;

    itm->setText(QString::number(i1) + " <-> " + QString::number(i2)+" Iter: " + QString::number(iter));
    iteration->setText(QString::number(iter));

    ui->tableWidget->setItem(row,newColCnt-1, itm);
}

QVector<int> MainWindow::selectionSort(QVector<int>& vect){

    for(int i = 0; i < vect.size();++i){
        int minIndx = i;
        for(int j = i+1 ; j < vect.size(); ++j){
            if(vect[j] < vect[minIndx]){
                minIndx = j;
            }
        }
        qSwap(vect[i], vect[minIndx]);
        if(!ui->ifClock->isChecked()){
            ui->tableWidget->setRowCount(i+2);
            printVect(vect, i+1);
            showSwapIndxs(i, minIndx,i+1,i);
        }
    }
    return vect;
}
void MainWindow::fillTheRow(int width, QVector<int>& v1, QVector<int>& v2)
{
    qsrand(time(NULL));
    for (int i = 0;i<width;++i) {
        v1.push_back(qrand()%30-10);
        v2.push_back(qrand()%30-10);
    }
}

void MainWindow::on_sortB_clicked()
{
    ui->tableWidget->setColumnCount(vect.size()+1);
    ui->tableWidget->setRowCount(1);
    printVect(vect,0);
    QElapsedTimer t;
    long long time;
    if(ui->ifClock->isChecked())
    {
        t.start();
        selectionSort(vect);
        time = t.nsecsElapsed();
        ui->tableWidget->setRowCount(2);
        printVect(vect,1);
        ui->time->setText(QString::number(time/1000) + "ms");
    }else{
        selectionSort(vect);
    }
}

void MainWindow::on_pushButton_clicked()
{
    vect.clear();
    ui->ar1->clear();
    ui->ar2->clear();
    QVector<int> v1, v2;
    auto seed = time(NULL);
    qsrand(seed);
    int s = qrand()%10 + 5;

    fillTheRow(s, v1, v2);

    for(auto i = 0; i<s; ++i){
        ui->ar1->setText(ui->ar1->text() + QString::number(v1[i]) + " ");
        ui->ar2->setText(ui->ar2->text() + QString::number(v2[i]) + " ");
    }

    for(int i = 0; i < s; ++i){
        if(v1[i] % 2 == 0){
            this->vect.append(v1[i]);
        }
        if(!(v2[i] % 2 == 0)) {
            this->vect.append(v2[i]);
        }
    }

    v1.clear();
    v2.clear();
}
