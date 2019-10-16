#include "paintwidget.h"
#include <QMouseEvent>
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    m_penColor = Qt::black;
    m_penWidth = 5;
    m_isModified = false;
    m_isDrawing = false;
    ResizeImage(&m_image, parent->size());
    resize(parent->size());
}

bool PaintWidget::OpenImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName)) return false;
    QSize newSize = loadedImage.size().expandedTo(size());
    ResizeImage(&loadedImage, newSize);
    m_image = loadedImage;
    m_isModified = false;
    update();
    return true;
}

void PaintWidget::SetPenColor(const QColor& color)
{
    m_penColor = color;
}

void PaintWidget::SetPenWidth(const int &width)
{
    m_penWidth = width;
}

void PaintWidget::ClearImage()
{
    m_image.fill(Qt::white);
    m_isModified = true;
    update();
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDrawing = true;
        m_startPoint = event->pos();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_isDrawing) DrawLineTo(event->pos());
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing)
    {
        m_isDrawing = false;
        DrawLineTo(event->pos());
    }
}

void PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, m_image, rect);
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.drawLine(0, height()/3, width(), height()/3);
    painter.drawLine(width()/2, 0, width()/2, height());
}

void PaintWidget::DrawLineTo(const QPoint &endPoint)
{
    QPainter painter(&m_image);
    painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(m_startPoint, endPoint);
    m_isModified = true;
    int rad = (m_penWidth / 2) + 2;
    update(QRect(m_startPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    m_startPoint = endPoint;
}

void PaintWidget::ResizeImage(QImage *image, const QSize &size)
{
    if (image->size() == size) return;
    QImage newImage(size, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
