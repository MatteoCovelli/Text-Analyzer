#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QMainWindow>


#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCarica_triggered();

    void on_btnAnalizza_clicked();

    int caratteri();
    int caratteriNoSpazi();
    int frasi();
    int paragrafi();
    int parole();
    int massimo(int c,int cNS, int par, int f, int p);

private:
    Ui::MainWindow *ui;

    QString filePath;

    QChartView *chartView = nullptr;
};
#endif // MAINWINDOW_H
