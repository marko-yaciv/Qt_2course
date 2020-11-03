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

void MainWindow::fillTheArr(QVector<double>& arr)
{
    for (auto& i: arr){
        i = double(qrand()%30+10)/double(qrand()%10+1);
    }
}

void MainWindow::printVect(QVector<double>& v, int row, int l, int r, QColor color){
    ui->tableWidget->setRowCount(row+1);
    int i = 0;
    while(l < r){
       QTableWidgetItem* itm = new QTableWidgetItem;
       itm->setText(QString::number(v[l++]));
       itm->setBackground(color);
        if(color == Qt::blue)
            itm->setForeground(Qt::white);

       ui->tableWidget->setItem(row,i++, itm);
    }
}

int MainWindow::findMaxValue(QVector<double> v)
{
    double max = v.first();
    for(auto&i : v){
        if(i > max){
            max = i;
        }
    }
    return v.indexOf(max);
}


int k = 1;
void MainWindow::merge(QVector<double>& arr, int leftStart, int rightStart, int mid){
    int lSize = mid - leftStart+1;
    int rSize = rightStart - mid;
    QVector<double> L(lSize), R(rSize);

    for(int i = 0; i < lSize; i++)
        L[i] = arr[leftStart + i];
    for(int j = 0; j < rSize; j++)
        R[j] = arr[mid + 1 + j];

    if((lSize || rSize >= 1) && !ui->ifClock->isChecked()){
        printVect(L, k++, 0, lSize, Qt::green);
        printVect(R, k++, 0, rSize, Qt::red);
    }
    int leftSubArrIndex = 0;
    int rightSubArrIndex = 0;
    int mergedArrInex = leftStart;

    while (leftSubArrIndex < lSize && rightSubArrIndex < rSize)
    {
        if (L[leftSubArrIndex] >= R[rightSubArrIndex])
        {
            arr[mergedArrInex] = L[leftSubArrIndex++];
        }
        else{
            arr[mergedArrInex] = R[rightSubArrIndex++];
        }
        mergedArrInex++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (leftSubArrIndex < lSize)
        arr[mergedArrInex++] = L[leftSubArrIndex++];

    // Copy the remaining elements of
    // R[], if there are any
    while (rightSubArrIndex < rSize)
        arr[mergedArrInex++] = R[rightSubArrIndex++];

    if(!ui->ifClock->isChecked())printVect(arr, k++, leftStart, mergedArrInex, Qt::cyan);
}

void MainWindow::mergeSort(QVector<double>& arr, int leftStart, int rightStart){
    if(leftStart < rightStart){

        int mid = leftStart + (rightStart - leftStart)/2;
        mergeSort(arr, leftStart, mid);
        mergeSort(arr, mid+1, rightStart);

        merge(arr,leftStart,rightStart, mid);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    v.resize(arg1);
    ui->tableWidget->setColumnCount(arg1);
    ui->tableWidget->setRowCount(1);
    fillTheArr(v);
    printVect(v,0,0, v.size(),Qt::gray);
}

void MainWindow::on_sortB_clicked()
{
    int maxIndx = findMaxValue(v);
    ui->maxIndx->setText("Index of max Value: " + QString::number(maxIndx+1));
    if(ui->ifClock->isChecked()){
        QElapsedTimer t;
        t.start();
        mergeSort(v,maxIndx+1,v.size()-1);
        auto time = t.nsecsElapsed();
        ui->time->setText(QString::number(time/1000));

        printVect(v,ui->tableWidget->rowCount()+1,0,v.size(),Qt::blue);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,maxIndx)->setBackground(Qt::darkRed);
    }else{
        mergeSort(v,maxIndx+1,v.size()-1);

        printVect(v,ui->tableWidget->rowCount()+1,0,v.size(),Qt::blue);
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,maxIndx)->setBackground(Qt::darkRed);
    }
}



/*
2 5 0 6 8 4 9 7
2 5 0 6
2 5
2   5


25


0 6

0   6
06


0256


8 4 9 7
*/




