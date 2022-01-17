#ifndef FORMULARTABLEFORM_H
#define FORMULARTABLEFORM_H

#include <QWidget>
#include "data/formularmodel.h"

namespace Ui {
class FormularTableForm;
}

class FormularTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit FormularTableForm(QWidget *parent = nullptr);
    ~FormularTableForm();

private:
    Ui::FormularTableForm *ui;

    FormularModel *_model;
};

#endif // FORMULARTABLEFORM_H
