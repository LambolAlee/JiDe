#include "ledbutton.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>

LEDButton::LEDButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setFixedSize(32,32);
    connect(this, &LEDButton::toggled, this, &LEDButton::updateChecked);
}

void LEDButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPen pen;
    pen.setWidth(_penWidth);
    pen.setColor(_borderColor);
    painter.setPen(pen);

    int w = width();
    int h = height();

    QPoint center(w/2, h/2);
    int radius = __min(w, h)/2 - _penWidth/2;

    painter.drawEllipse(center, radius, radius);

    QPainterPath path;
    path.addEllipse(center, radius - _penWidth/2, radius - _penWidth/2);
    painter.fillPath(path, _insideColor);
}

void LEDButton::updateState(bool clean)
{
    if (clean)
        _insideColor.setColor(_clean);
    else
        _insideColor.setColor(_modified);
    update();
}

void LEDButton::updateChecked(bool checked)
{
    if (checked)
        _borderColor = _checked;
    else if (!sender())
        _borderColor = _unchecked;
}
