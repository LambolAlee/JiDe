#include "recordeditorarea.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QTabBar>

RecordEditorArea::RecordEditorArea(QWidget *parent)
    : QMdiArea(parent)
{
    setViewMode(QMdiArea::TabbedView);
    setTabsClosable(true);
    auto *tab = findChild<QTabBar *>();
    tab->setExpanding(false);
}
