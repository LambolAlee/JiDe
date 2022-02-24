#ifndef STATEPANEL_H
#define STATEPANEL_H

#include <QWidget>

#include "ledbutton.h"

namespace Ui {
class StatePanel;
}

class StatePanel : public QWidget
{
    Q_OBJECT

signals:
    void submit();
    void cancel();

public:
    explicit StatePanel(QWidget *parent = nullptr);
    ~StatePanel();

    void addRedoAction(QAction *action);
    void addUndoAction(QAction *action);

public slots:
    void updateState(bool clean);

protected:
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;

private:
    Ui::StatePanel *ui;
    LEDButton *_led;    
};

#endif // STATEPANEL_H
