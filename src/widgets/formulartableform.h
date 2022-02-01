#ifndef FORMULARTABLEFORM_H
#define FORMULARTABLEFORM_H

#include <QWidget>
#include "formular/formularmodel.h"

namespace Ui {
class FormularTableForm;
}

class FormularTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit FormularTableForm(QWidget *parent = nullptr);
    ~FormularTableForm();

private slots:
    void on_exportButton_clicked();

private:
    Ui::FormularTableForm *ui;

    FormularModel *_model;
    void initActions();
    void initModel();
};

#endif // FORMULARTABLEFORM_H
