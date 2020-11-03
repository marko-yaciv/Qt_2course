#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QElapsedTimer>
#include <algorithm>
#include <random>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tableWidget->setRowCount(this->tableRows);
    ui->tableWidget->setColumnCount(this->tableColumns);

    int n = 1024;
    for (int i = 0; i < tableRows; ++i) {
        QTableWidgetItem * itm = new QTableWidgetItem;
        itm->setText(QString::number(n));
        ui->tableWidget->setVerticalHeaderItem(i,itm);
        arraySizes.append(double(n));
        n *= 2;
    }

    QVector<QString> methods = {"Bubble","Selection","Shell","Merge","Quick","Count"};
    for(int j = 0; j < tableColumns;++j){
        QTableWidgetItem * itm = new QTableWidgetItem;
        itm->setText(methods[j]);
        ui->tableWidget->setHorizontalHeaderItem(j,itm);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

const int RANGE = 1000;
void MainWindow::bubbleSort(QVector<int>& arr){
    int s = arr.size();

    for(int i = 0; i < s; ++i){
        int stop = true;
        for(int j = 0; j < s-1; ++j){
            if(arr[j]>arr[j+1]){
                qSwap(arr[j], arr[j+1]);
                stop = false;
            }
        }
        if(stop){
            break;
        }
    }
}
void MainWindow::selectionSort(QVector<int>& arr){

    for(int i = 0 ; i < arr.size();++i){
        int minIndx = i;
        for(int j = i+1 ; j < arr.size(); ++j){
            if(arr[j]<arr[minIndx]){
                minIndx = j;
            }
        }
        qSwap(arr[i], arr[minIndx]);
    }
}
void MainWindow::shellSort(QVector<int>& arr){
    int sz = arr.size();

    for(int step = sz/2;step>0;step/=2){
        for(auto i = step;i<sz;++i){
            for(int j = i-step;j>=0;j-=step){
                if(arr[j] > arr[j+step]){
                    qSwap(arr[j],arr[j+step]);
                }
            }
        }
    }
}
void MainWindow::merge(QVector<int>& arr, int leftStart, int rightStart, int mid){
    int lSize = mid - leftStart+1;
    int rSize = rightStart - mid;
    QVector<double> L(lSize), R(rSize);


    for(int i = 0; i < lSize; i++)
        L[i] = arr[leftStart + i];
    for(int j = 0; j < rSize; j++)
        R[j] = arr[mid + 1 + j];



    int leftSubArrIndex = 0;
    int rightSubArrIndex = 0;
    int mergedArrInex = leftStart;

    while (leftSubArrIndex < lSize && rightSubArrIndex < rSize)
    {
        if (L[leftSubArrIndex] <= R[rightSubArrIndex])
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

}
void MainWindow::mergeSort(QVector<int>& arr, int leftStart, int rightStart){
    if(leftStart < rightStart){

        int mid = leftStart + (rightStart - leftStart)/2;
        mergeSort(arr, leftStart, mid);
        mergeSort(arr, mid+1, rightStart);

        merge(arr,leftStart,rightStart, mid);
    }
}

void MainWindow::quickSort(QVector<int>& arr,int left, int right)
{


   if(left < right){
       int *pivot = &arr[(right+left)/2];
       int i = (left - 1);  // Index of smaller element

       for (int j = left; j < right; j++)
       {
           if (arr[j] <= *pivot)
           {
               i++;
               qSwap(arr[i], arr[j]);
           }
       }
       qSwap(arr[++i], *pivot);

       quickSort(arr, left, i - 1);
       quickSort(arr, i + 1, right);
   }
}



void MainWindow::countSort(QVector<int>& arr)
{
    QVector<int> count(RANGE);
    QVector<int> out(arr.size());
    for(int i = 0; i < arr.size(); ++i){
        ++count[arr[i]];
    }

    for (int i = 1; i < RANGE; ++i) {
        count[i]+=count[i-1];
    }

    for (int i = 0; i < arr.size(); ++i) {
        out[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = out[i];
    }
}


void MainWindow::fillTheArr(QVector<int>& arr){
    for(int& i: arr) i  = qrand()%RANGE;
}

void MainWindow::sortAndClock(f method, int row, int column){
    QElapsedTimer t;
    qint64 elapsed;


    QVector<int> tmpArr(arr.size());
    int j = 0;
    for(auto&i : arr){
        tmpArr[j++] = i;
    }
    switch (method) {
    case f::bubble:
        t.start();
        bubbleSort(tmpArr);
        elapsed = t.nsecsElapsed();
        break;
    case f::selection:
        t.start();
        selectionSort(tmpArr);
        elapsed = t.nsecsElapsed();
        break;
    case f::shell:
        t.start();
        shellSort(tmpArr);
        elapsed = t.nsecsElapsed();
        break;
    case f::merge:
        t.start();
        mergeSort(tmpArr,0, tmpArr.size()-1);
        elapsed = t.nsecsElapsed();
        break;
    case f::quick:
        t.start();
        quickSort(tmpArr,0,tmpArr.size()-1);
        elapsed = t.nsecsElapsed();
        break;
    case f::count:
        t.start();
        countSort(tmpArr);
        elapsed = t.nsecsElapsed();
        break;
    }
    //std::shuffle(arr.begin(), arr.end(),std::default_random_engine(time(NULL)));

    QTableWidgetItem*itm = new QTableWidgetItem;
    itm->setText(QString::number(elapsed/1000000)+"ms");
    ui->tableWidget->setItem(row, column, itm);
}
void MainWindow::on_sortB_clicked()
{

    for (int i = 0, j = 0; i < tableRows; ++i) {
        arr.clear();

        arr.resize(ui->tableWidget->verticalHeaderItem(i)->data(Qt::DisplayRole).toInt());
        fillTheArr(arr);

        sortAndClock(f::bubble, i,j++);
        sortAndClock(f::selection, i,j++);
        sortAndClock(f::shell, i,j++);
        sortAndClock(f::merge, i,j++);
        sortAndClock(f::quick, i,j++);
        sortAndClock(f::count, i,j);
        j=0;
    }

}
QVector<QVector<double>> MainWindow::getTimes(){
    QVector<QVector<double>> timeMatrix;
    timeMatrix.resize(tableColumns);

    for(int i = 0; i < tableColumns;++i){
        for (int j = 0; j < tableRows;++j) {
            timeMatrix[i].append(ui->tableWidget->item(j,i)->text().remove("ms").toDouble());
        }
    }
    return timeMatrix;
}
void MainWindow::drawGraph(const QVector<QVector<double>> timeMatr){
    QVector<QColor> colors = {Qt::black, Qt::green, Qt::blue, Qt::red, Qt::darkCyan, Qt::magenta};

    ui->customPlot->legend->clear();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QPen* pen = new QPen;
    for(int i = 0; i < tableColumns; ++i){

        ui->customPlot->legend->setVisible(true);
        QFont legendFont = font();
        legendFont.setPointSize(9);
        ui->customPlot->legend->setFont(legendFont);
        ui->customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
        ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);

        // create graph and assign data to it:
        ui->customPlot->addGraph();

        pen->setColor(colors[i]);
        ui->customPlot->graph(i)->setPen(*pen);
        ui->customPlot->graph(i)->setName(ui->tableWidget->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString());
        ui->customPlot->graph(i)->setData(arraySizes,timeMatr[i]);
        ui->customPlot->graph(i)->setScatterStyle
                (QCPScatterStyle(QCPScatterStyle::ssDisc,QPen(colors[i]),QBrush(Qt::white),5) );
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("Array size");
        ui->customPlot->yAxis->setLabel("Sorting Time (ms)");
        // set axes ranges, so we see all data:
        ui->customPlot->xAxis->setRange(arraySizes.first(), arraySizes.last());
        ui->customPlot->yAxis->setRange(0, 1000);
        ui->customPlot->replot();
    }
}

void MainWindow::on_drawGraph_clicked()
{
    drawGraph(getTimes());
}
