#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(),height());

    m_chartView = new QChartView(this);
    m_chart = new QChart();

    m_dataModel = new DataModel();
    ui->tableView->setModel(m_dataModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(m_chartView);

    updateGraph();

    m_chartView->setChart(m_chart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGraph()
{
    //m_chart->removeAllSeries();

    QValueAxis* axisX = new QValueAxis;
    axisX->setLabelFormat("%i");
    axisX->setRange(0, 5);
    m_chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setRange(0, 5);
    m_chart->addAxis(axisY, Qt::AlignLeft);

    DataHolder dh = m_dataModel->GetDataHolder();

    for (int i = 0; i < dh.GetNumOfClasses(); i++)
    {
        QScatterSeries* series = new QScatterSeries();
        series->setName(dh.GetClassAt(i).GetData());
        QList<DataFeature> dataFeatures = m_dataModel->GetDataHolder().GetDataFeaturesOfClass(dh.GetClassAt(i).GetId());
        for (DataFeature& df : dataFeatures)
        {
            series->append(df.GetFeatureAt(0), df.GetFeatureAt(1));
        }
        m_chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
}
