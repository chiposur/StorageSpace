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
#if (defined (Q_OS_MAC))
    bool isMac = true;
#else
    bool isMac = false;
#endif
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
    int margin = isMac ? 0 : 4;
    btn.rect =
        QRect(
            option.rect.left() + margin,
            option.rect.top() + margin,
            option.rect.width() - margin * 2,
            option.rect.height() - margin * 2);
    btn.text = btnText;
    btn.state |= QStyle::State_Enabled;
    auto font = painter->font();
    int pixelSize = isMac ? 12 : 14;
    font.setPixelSize(pixelSize);
    if (option.state & QStyle::State_MouseOver)
    {
        btn.state |= QStyle::State_MouseOver;
        if (isMac)
        {
            btn.palette.setColor(QPalette::ButtonText, QColor::fromRgb(0, 102, 255));
        }
    }
    painter->save();
    painter->setFont(font);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &btn, painter);
    painter->restore();
}
