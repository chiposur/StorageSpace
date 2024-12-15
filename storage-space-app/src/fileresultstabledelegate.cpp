#include "fileresultstable.h"
#include "fileresultstabledelegate.h"

#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QStyleOptionButton>
#include <QtSystemDetection>

void FileResultsTableDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    bool isOpenOrDeleteIndex =
        index.column() == FileResultsTable::OPEN_IN_FOLDER_COL ||
        index.column() == FileResultsTable::DELETE_COL;
    QString btnText;
    if (!isOpenOrDeleteIndex)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    else if (index.column() == 2)
    {
        btnText = "Open in folder";
    }
    else
    {
        btnText = "Delete";
    }
    QStyleOptionButton btn;
#if (defined (Q_OS_MAC))
    int margin = 0;
#else
    int margin = 4;
#endif
    btn.rect =
        QRect(
            option.rect.left() + margin,
            option.rect.top() + margin,
            option.rect.width() - margin * 2,
            option.rect.height() - margin * 2);
    btn.text = btnText;
    btn.state |= QStyle::State_Enabled;
    auto font = painter->font();
#if (defined (Q_OS_MAC))
    int pixelSize = 12;
#else
    int pixelSize = 14;
#endif
    font.setPixelSize(pixelSize);
    if (option.state & QStyle::State_MouseOver)
    {
        btn.palette.setColor(QPalette::ButtonText, QColor::fromRgb(0, 102, 255));
    }
    painter->save();
    painter->setFont(font);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &btn, painter);
    painter->restore();
}
