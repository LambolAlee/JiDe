#ifndef RECORDCARDBODY_H
#define RECORDCARDBODY_H

#include <QWidget>
#include <QUndoStack>

class RecordCardBody : public QWidget
{
    Q_OBJECT
public:
    explicit RecordCardBody(QWidget *parent = nullptr);

    QUndoStack *undoStack() { return _stack; }

private:
    QUndoStack *_stack;


};

#endif // RECORDCARDBODY_H
