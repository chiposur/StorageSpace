#include "fileresultstabledelegate.h"

#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QStyleOptionButton>

void FileResultsTableDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    bool isOpenOrDeleteIndex = index.column() == 2 || index.column() == 3;
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
    auto btn = QStyleOptionButton();
    int margin = 4;
    btn.rect =
        QRect(
            option.rect.left() + margin,
            option.rect.top() + margin,
            option.rect.width() - margin * 2,
            option.rect.height() - margin * 2);
    btn.text = btnText;
    if (option.state == (option.state | QStyle::State_MouseOver))
    {
        btn.state = QStyle::State_Enabled | QStyle::State_MouseOver;
    }
    painter->save();
    auto font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &btn, painter);
    painter->restore();
}
