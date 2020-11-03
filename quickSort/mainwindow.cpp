#include "mainwindow.h"
#include "ui_mainwindow.h"
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

void MainWindow::fillTheArr(QVector<int>& arr)
{
    for (auto& i : arr) {
        i = (int(qrand()%30-10)/int(qrand()%5+1));
    }
}

void MainWindow::printArr(int row, QVector<int>& arr)
{
    for (int i = 0; i< arr.size(); ++i) {
        QTableWidgetItem* itm = new QTableWidgetItem;
        itm->setText(QString::number(arr[i]));
        ui->arr->setItem(row,i,itm);
    }
}

void MainWindow::showSwapIndxs(int i1, int i2, int row){

    QTableWidgetItem* itm = new QTableWidgetItem;
    itm->setText(QString::number(i1) + " <-> " + QString::number(i2));
    QFont f;
    f.setBold(true);
    itm->setFont(f);
    ui->arr->setItem(row,arr.size(), itm);
}

void MainWindow::changeArr(QVector<int>& vect)
{
    for (auto i = vect.begin(); i < vect.end();) {
        if(*i % 3 == 0){
            vect.erase(i);
        }else{
        *i *= *i;
        ++i;
        }
    }

}

int k = 1;
void MainWindow::quickSort(QVector<int>& arr,int left, int right)
{
   if(left < right){
       int *pivot = &arr[right];
       int i = (left - 1);  // Index of smaller element

       for (int j = left; j < right; j++)
       {
           if (arr[j] >= *pivot)
           {
               i++;
               qSwap(arr[i], arr[j]);
               if(!ui->ifClock->isChecked()){
                   ui->arr->setRowCount(k+1);
                   showSwapIndxs(i,j,k);
                   printArr(k++, arr);
               }
           }
       }
       qSwap(arr[++i], *pivot);

       quickSort(arr, left, i - 1);
       quickSort(arr, i + 1, right);
   }
}


void MainWindow::on_sortB_clicked()
{
    //changeArr(arr);
    ui->arr->setRowCount(1);
    printArr(0,arr);

    if(ui->ifClock->isChecked()){
        QElapsedTimer e;
        e.start();

        quickSort(arr, 0, arr.size()-1);

        auto t = e.nsecsElapsed();
        ui->arr->setRowCount(2);
        printArr(1,arr);
        ui->time->setText(QString::number(t/1000000) + "ms");
    }else{
        quickSort(arr, 0, arr.size()-1);
    }

}

void MainWindow::on_sz_valueChanged(int arg1)
{
    ui->arr->setRowCount(1);
    ui->arr->setColumnCount(arg1+1);
    ui->arr->clear();
    arr.resize(arg1);

    fillTheArr(arr);
    printArr(0,arr);
}


/*
0 4 6 -1 5 7 3 9 3 6 2
p = 0

-1   0   4 6 5 7 3 9 3 6 2
-1   0   4 6 5 7 3 9 3 6 2

-1   0   3 3 2   4   6 5 7 9 6



*/




