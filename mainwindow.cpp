#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamodel.h"
#include "paintwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(),height());

    m_paintWidget = new PaintWidget(ui->frame);
    m_chartView = new QChartView(this);
    m_chart = new QChart();

    m_dataModel = new DataModel();
    ui->tableView->setModel(m_dataModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(m_chartView);

    updateGraph();

    m_chartView->setChart(m_chart);

    connect(ui->clearButton, &QPushButton::clicked, m_paintWidget, &PaintWidget::ClearImage);
    connect(ui->checkButton, &QPushButton::clicked, this, &MainWindow::CheckButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGraph()
{
    QValueAxis* axisX = new QValueAxis;
    axisX->setLabelFormat("%.0f");
    axisX->setRange(0.0, 5.0);
    axisX->setTickInterval(1.0);
    axisX->setTickType(QValueAxis::TickType::TicksDynamic);
    m_chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis;
    axisY->setLabelFormat("%.0f");
    axisY->setRange(0.0, 5.0);
    axisY->setTickInterval(1.0);
    axisY->setTickType(QValueAxis::TickType::TicksDynamic);
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

void MainWindow::CheckButtonClicked()
{
    QImage image = m_paintWidget->GetImage();
    DataFeature df;
    int crossCount = 0;
    for (int i = 0; i < image.height(); i++)
    {
        if (image.pixelColor(image.width()/2, i) == Qt::black)
        {
            i += m_paintWidget->GetPenWidth()*3;
            crossCount++;
        }
    }
    df.AddFeature(crossCount);
    crossCount = 0;
    for (int i = 0; i < image.width(); i++)
    {
        if (image.pixelColor(i, image.height()/3) == Qt::black)
        {
            i += m_paintWidget->GetPenWidth()*3;
            crossCount++;
        }
    }
    df.AddFeature(crossCount);
    DataClass dc = m_dataModel->GetDataHolder().FindClassByFeatures(df);
    ui->match->setText(dc.GetData().isEmpty() ? "None" : dc.GetData());
}
