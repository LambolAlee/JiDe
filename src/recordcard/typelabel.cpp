#include "typelabel.h"

#include <QPainter>
#include <QDebug>

TypeLabel::TypeLabel(QWidget *parent)
    : QWidget(parent)
{
}

TypeLabel::TypeLabel(const QString &text, QWidget *parent)
    : TypeLabel(parent)
{
    setText(text);
}

void TypeLabel::setText(const QString &text)
{
    _text = text;
    QFont f;
    f.setPointSize(11);
    QFontMetrics fm(f);
    int h = fm.height();
    int w = fm.horizontalAdvance(_text);
    setMinimumSize(w + 40, h);
}

void TypeLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPen pen;
    pen.setColor(QColor(Qt::white));
    pen.setWidth(1);
    painter.setPen(pen);

    painter.setBrush(QBrush(QColor(196, 196, 196)));

    QRect r = this->rect();
    int w = r.width(); int h = r.height();
    int mx = 1; int my = 1;
    QPolygon polygon;
    polygon
        << QPoint(mx, my)
        << QPoint(w-h/2, my)
        << QPoint(w-mx, h/2)
        << QPoint(w-h/2, h-my)
        << QPoint(mx, h-my);
    painter.drawPolygon(polygon);
    QRect labelArea(QPoint(mx, my), QPoint(w-h/2, h-my));
    QFont f;
    f.setPointSize(11);
    painter.setFont(f);
    painter.drawText(labelArea, Qt::AlignCenter, _text);
}
