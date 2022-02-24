#ifndef LEDBUTTON_H
#define LEDBUTTON_H

#include <QAbstractButton>

class LEDButton : public QAbstractButton
{
    Q_OBJECT

public:
    LEDButton(QWidget *parent = nullptr);

    void updateChecked(bool checked);
    void updateState(bool clean);

protected:
    void paintEvent(QPaintEvent *ev) override;

private:
    QColor _borderColor = _unchecked;
    QBrush _insideColor = QBrush(_clean);
    int _penWidth = 4;
    static constexpr QColor _clean = QColor(144,238,144);
    static constexpr QColor _modified = QColor(240,128,128);
    static constexpr QColor _checked = QColor(144, 144, 238);
    static constexpr QColor _unchecked = QColor(255, 255, 255);
};

#endif // LEDBUTTON_H
