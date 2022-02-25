#ifndef RECORDCARDFRAME_H
#define RECORDCARDFRAME_H

#include <QWidget>
#include <QPushButton>

#include "typelabel.h"
#include "statepanel.h"
#include "recordcardbody.h"

namespace Ui {
class RecordCardFrame;
}

class RecordCardFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RecordCardFrame(QWidget *parent = nullptr);
    ~RecordCardFrame();

    void initUndoSystem();

    void setBody(RecordCardBody *w);
    RecordCardBody *body() { return _body; };

    void setText(const QString &text);
    const QString text() const { return _typeLabel->text(); };

    void setTitle(const QString &title);
    const QString title() const;

    void addRedoAction(QAction *action) { _statePanel->addRedoAction(action); }
    void addUndoAction(QAction *action) { _statePanel->addUndoAction(action); }

protected slots:
    virtual void submit();
    virtual void cancel();

private:
    Ui::RecordCardFrame *ui;
    QPushButton *_typeLabel;
    StatePanel *_statePanel;
    RecordCardBody *_body;
};

#endif // RECORDCARDFRAME_H
