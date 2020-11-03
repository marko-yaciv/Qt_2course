#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<int> vect;

    void printVect(QVector<int>& v, int row);
    QVector<int> selectionSort(QVector<int>& vect);
    void fillTheRow(int width,QVector<int>& v1, QVector<int>& v2);
    void showSwapIndxs(int i1, int i2, int row, int iter);
private slots:
    void on_sortB_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
