#ifndef RECORDEDITORAREA_H
#define RECORDEDITORAREA_H

#include <QMdiArea>

class RecordEditorArea : public QMdiArea
{
    Q_OBJECT
public:
    RecordEditorArea(QWidget *parent = nullptr);

    void openRecord();
};

#endif // RECORDEDITORAREA_H
