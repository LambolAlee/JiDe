#ifndef TYPELABEL_H
#define TYPELABEL_H

#include <QWidget>

class TypeLabel : public QWidget
{
    Q_OBJECT
public:
    explicit TypeLabel(QWidget *parent = nullptr);
    TypeLabel(const QString &text, QWidget *parent = nullptr);

    void setText(const QString &text);
    const QString &text() const { return _text; }

protected:
    void paintEvent(QPaintEvent *ev) override;

private:
    QString _text;

};

#endif // TYPELABEL_H
