#ifndef RECORDDOCUMENT_H
#define RECORDDOCUMENT_H

#include <QMainWindow>
#include <QStandardItemModel>

class RecordCardFrame;

namespace Ui {
class RecordDocument;
}

class RecordDocument : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecordDocument(QWidget *parent = nullptr);
    ~RecordDocument();

    void addCard(RecordCardFrame *frame);

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::RecordDocument *ui;
    QStandardItemModel _model;

    void updateIndexWdiget();
};

#endif // RECORDDOCUMENT_H
