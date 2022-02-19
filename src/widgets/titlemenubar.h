#ifndef TITLEMENUBAR_H
#define TITLEMENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QLabel>

namespace Ui {
class TitleMenuBar;
}

class TitleMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleMenuBar(QMenuBar *menuBar = nullptr, QWidget *parent = nullptr);
    ~TitleMenuBar();

    void setParentWidget(QWidget *w) { _parentWidget = w; }
    QLabel *title();

private slots:
    void on_minButton_clicked();
    void on_maxButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::TitleMenuBar *ui;
    QWidget *_parentWidget;
    QMenuBar *_menuBar;

    void updateMenuBar();
};

#endif // TITLEMENUBAR_H
