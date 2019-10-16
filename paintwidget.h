#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget* parent = nullptr);

    bool OpenImage(const QString& fileName);
    void SetPenColor(const QColor& color);
    void SetPenWidth(const int& width);

    bool IsModified() const { return m_isModified; }
    QColor GetPenColor() const { return m_penColor; }
    int GetPenWidth() const { return m_penWidth; }
    QImage GetImage() const { return m_image; }

public slots:
    void ClearImage();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    void DrawLineTo(const QPoint& endPoint);
    void ResizeImage(QImage* image, const QSize& size);

    bool m_isModified;
    bool m_isDrawing;
    int m_penWidth;
    QColor m_penColor;
    QImage m_image;
    QPoint m_startPoint;
};

#endif // PAINTWIDGET_H
