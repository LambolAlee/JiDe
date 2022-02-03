#ifndef LINEEDITWITHEXTENSIBLETEXTBOX_H
#define LINEEDITWITHEXTENSIBLETEXTBOX_H

#include <QWidget>

namespace Ui {
class LineEditWithExtensibleTextBox;
}

class LineEditWithExtensibleTextBox : public QWidget
{
    Q_OBJECT

public:
    explicit LineEditWithExtensibleTextBox(QWidget *parent = nullptr);
    ~LineEditWithExtensibleTextBox();

private:
    Ui::LineEditWithExtensibleTextBox *ui;
};

#endif // LINEEDITWITHEXTENSIBLETEXTBOX_H
