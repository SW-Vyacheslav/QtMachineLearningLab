#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "datamodel.h"
#include "paintwidget.h"

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

public slots:
    void CheckButtonClicked();

private:
    Ui::MainWindow *ui;
    QChart* m_chart;
    QChartView* m_chartView;
    DataModel* m_dataModel;
    PaintWidget* m_paintWidget;
};

#endif // MAINWINDOW_H
