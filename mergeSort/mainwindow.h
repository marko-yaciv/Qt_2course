#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<double> v;

    void merge(QVector<double>& arr, int leftStart, int rightStart, int mid);
    void mergeSort(QVector<double>& arr, int leftStart, int rightStart);

    void fillTheArr(QVector<double>& arr);
    void printVect(QVector<double>& v, int row, int, int, QColor color);
    void showSwapIndxs(int i1, int i2, int row);

    int findMaxValue(QVector<double>v);
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_sortB_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
