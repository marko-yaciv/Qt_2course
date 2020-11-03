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

    void countSort(QVector<int>& towns);
    QVector<int> findEquivalent(QVector<QString>& townList, int townListfirstLetter);
    void printVect(QVector<QString> vect, int row);
    void printVect(QVector<int> vect, int row);
private slots:
    void on_sortB_clicked();

    void on_size_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
