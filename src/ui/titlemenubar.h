#ifndef TITLEMENUBAR_H
#define TITLEMENUBAR_H

#include <QWidget>


class QLabel;
class QMenuBar;

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

    void setIconMaximized();
    void setIconNormal();

protected:
     //bool eventFilter(QObject *obj, QEvent *ev) override;

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
