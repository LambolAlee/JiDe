#ifndef NAVITAGSBAR_H
#define NAVITAGSBAR_H

#include <QWidget>

// tags system will add later

namespace Ui {
class NaviTagsBar;
}

class NaviTagsBar : public QWidget
{
    Q_OBJECT

public:
    explicit NaviTagsBar(QWidget *parent = nullptr);
    ~NaviTagsBar();

private:
    Ui::NaviTagsBar *ui;
};

#endif // NAVITAGSBAR_H
