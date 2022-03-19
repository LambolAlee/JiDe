#include "titlemenubar.h"
#include "ui_titlemenubar.h"

#include <QStyle>

TitleMenuBar::TitleMenuBar(QMenuBar *menuBar, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleMenuBar),
    _menuBar(menuBar)
{
    ui->setupUi(this);
    ui->closeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->maxButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    ui->minButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMinButton));
    updateMenuBar();
}

TitleMenuBar::~TitleMenuBar()
{
    delete ui;
}

QLabel *TitleMenuBar::title()
{
    return ui->title;
}

void TitleMenuBar::setIconMaximized()
{
    ui->maxButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMaxButton));
}

void TitleMenuBar::setIconNormal()
{
    ui->maxButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarNormalButton));
}

void TitleMenuBar::on_minButton_clicked()
{
    _parentWidget->showMinimized();
}

void TitleMenuBar::on_maxButton_clicked()
{
    if (_parentWidget->isMaximized()){
        _parentWidget->showNormal();
        setIconMaximized();
    }
    else{
        _parentWidget->showMaximized();
        setIconNormal();
    }
}

void TitleMenuBar::on_closeButton_clicked()
{
    _parentWidget->close();
}

void TitleMenuBar::updateMenuBar()
{
    if (_menuBar) {
        //_menuBar->hide();
        ui->menuLayout->addWidget(_menuBar);
        _menuBar->setStyleSheet("QMenuBar{background:transparent; margin-bottom:5px; min-height:27px;}");
//        for (auto &&action: _menuBar->actions()) {
//            QToolButton *button = new QToolButton(this);
//            button->setAutoRaise(true);
//            button->setProperty("class", "MenuButton");
//            button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//            button->setDefaultAction(action);
//            button->setPopupMode(QToolButton::InstantPopup);
//            button->setStyleSheet("QToolButton::menu-indicator{image:none;}");
//            button->setFocusPolicy(Qt::NoFocus);
//            ui->menuLayout->addWidget(button);
//        }
    }
}
