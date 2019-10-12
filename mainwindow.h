#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamodel.h"
#include "QtCharts"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateGraph();

private:
    Ui::MainWindow *ui;
    QChart* m_chart;
    QChartView* m_chartView;
    DataModel* m_dataModel;
};

#endif // MAINWINDOW_H
