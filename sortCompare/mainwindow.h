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
    QVector<double> arraySizes;
    const int tableRows = 4;
    const int tableColumns = 6;
    enum class f
    {
       bubble, selection, shell, merge, quick,count
    };

    void bubbleSort(QVector<int>& arr);
    void selectionSort(QVector<int>& arr);
    void shellSort(QVector<int>& arr);
    void merge(QVector<int>& arr, int leftStart, int rightStart, int mid);
    void mergeSort(QVector<int>& arr, int leftStart, int rightStart);
    void quickSort(QVector<int>& arr,int left, int right);
    void countSort(QVector<int>& arr);

    void fillTheArr(QVector<int>& arr);
    void sortAndClock(f, int row, int column);

    QVector<QVector<double>> getTimes();
    void drawGraph(QVector<QVector<double>> timeMatr);
private slots:
    void on_sortB_clicked();

    void on_drawGraph_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
