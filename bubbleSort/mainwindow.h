#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTableWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showSwapIndxs(int n1, int n2, int row, int iter);
    void printVect(QVector<double>& v, int row);
    QPair<int, int> findNegativeIndexes(QVector<double>& v);
    QVector<double> bubbleSort(QVector<double>& vect);

    void fillTheRow();
private slots:
    void on_cntOfNums_valueChanged(int arg1);

    void on_sortB_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
