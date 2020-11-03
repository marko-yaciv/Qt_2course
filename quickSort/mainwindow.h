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

    QVector<int> arr;

    void fillTheArr(QVector<int>&);
    void printArr(int row, QVector<int>& arr);
    void showSwapIndxs(int i1, int i2, int row);
    void changeArr(QVector<int>& vect);
    void quickSort(QVector<int>& arr,int left, int right);

private slots:
    void on_sortB_clicked();

    void on_sz_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
