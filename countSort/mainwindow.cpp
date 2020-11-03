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
void MainWindow::printVect(QVector<QString> vect, int row)
{
    ui->tableWidget->setRowCount(row);
    for(int i=0; i < vect.size(); ++i){
       QTableWidgetItem* itm = new QTableWidgetItem;
       itm->setText(vect[i]);

       ui->tableWidget->setItem(row-1,i, itm);
    }
}
void MainWindow::printVect(QVector<int> vect, int row)
{
    ui->tableWidget->setRowCount(row);
    for(int i=0; i < vect.size(); ++i){
       QTableWidgetItem* itm = new QTableWidgetItem;
       itm->setText(QString::number(vect[i]));

       ui->tableWidget->setItem(row-1,i, itm);
    }
}

int k = 2;
void MainWindow::countSort(QVector<int>& towns)
{
    QVector<int> count(255);
    QVector<int> out(towns.size());
    for(int i = 0; i < towns.size(); ++i){
        ++count[towns[i]];
    }

    for (int i = 1; i < 255; ++i) {
        count[i]+=count[i-1];
    }

    for (int i = 0; i < towns.size(); ++i) {
        out[count[towns[i]]-1] = towns[i];
        --count[towns[i]];
    }

    if(!ui->ifClock->isChecked()) printVect(out,k++);

    for (int i = 0; i < towns.size(); ++i) {
        towns[i] = out[i];
    }
}

QVector<int> MainWindow::findEquivalent(QVector<QString>& townList, int townListfirstLetter){
    QVector<int> indx;
    for(int i = 0;i < townList.size();++i){
        if(townList[i].front().unicode() == townListfirstLetter)
            indx.push_back(i);
    }
    return indx;
}
void MainWindow::on_sortB_clicked()
{
    QVector<QString> townList;

    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        auto tmp = ui->tableWidget->item(0,i)->text().simplified();
        if(tmp.length()<=8)townList.push_back(tmp);
    }

    QVector<int> townListfirstLetters(townList.size());
    int j = 0;
    for (auto& i : townListfirstLetters) {
        i = townList[j++].front().unicode();
    }

    if(ui->ifClock->isChecked()){
        QElapsedTimer t;
        t.start();
        countSort(townListfirstLetters);
        auto time = t.nsecsElapsed();
        ui->time->setText(QString::number(time/1000) + "mcs");

    }else{
        countSort(townListfirstLetters);
    }

    QVector<QString> newTowns;
    for (auto i = 0; i < townListfirstLetters.size(); ++i) {
        QVector<int> indxs = findEquivalent(townList,townListfirstLetters[i]);
        if(indxs.size() > 1){
            i=indxs.size();
            for (auto&j : indxs) {
                newTowns.push_back(townList[j]);
            }
        }else{
            newTowns.push_back(townList[indxs.first()]);
        }
    }
    townList = newTowns;

    printVect(townList,k++);
}

void MainWindow::on_size_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
    ui->tableWidget->setRowCount(1);

}
