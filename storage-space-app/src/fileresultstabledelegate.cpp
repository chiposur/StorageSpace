#include "fileresultstable.h"
#include "fileresultstabledelegate.h"

#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QStyleHints>
#include <QStyleOptionButton>
#include <QtSystemDetection>

const QString FileResultsTableDelegate::OPEN_IN_FOLDER_TXT = "Open in folder";
const QString FileResultsTableDelegate::DELETE_TXT = "Delete";

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
    else if (index.column() == FileResultsTable::OPEN_IN_FOLDER_COL)
    {
        btnText = OPEN_IN_FOLDER_TXT;
    }
    else
    {
        btnText = DELETE_TXT;
    }
    if (isMac)
    {
        // QStyleOptionButton doesn't work correctly for Mac
        paintCustomMacButton(painter, option, btnText);
        return;
    }
    QStyleOptionButton btn;
    btn.rect = getRectFromOption(option, 4);
    btn.text = btnText;
    btn.state |= QStyle::State_Enabled;
    auto font = painter->font();
    int pixelSize = 14;
    font.setPixelSize(pixelSize);
    if (option.state & QStyle::State_MouseOver)
    {
        btn.state |= QStyle::State_MouseOver;
    }
    painter->save();
    painter->setFont(font);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &btn, painter);
    painter->restore();
}

void FileResultsTableDelegate::paintCustomMacButton(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QString &text) const
{
    painter->save();
    bool darkMode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
    auto btnBg = darkMode ? QColor::fromRgb(101, 101, 101) : QColor::fromRgb(236, 236, 236);
    auto bgRect = getRectFromOption(option, 4);
    painter->fillRect(bgRect, btnBg);
    auto font = painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    painter->setPen(darkMode ? QColor::fromRgb(231, 231, 231) : Qt::black);
    QTextOption textOption(Qt::AlignmentFlag::AlignVCenter | Qt::AlignHCenter);
    painter->drawText(QRectF(bgRect), text, textOption);
    painter->restore();
}

QRect FileResultsTableDelegate::getRectFromOption(const QStyleOptionViewItem &option, int margin)
{
    return QRect(
        option.rect.left() + margin,
        option.rect.top() + margin,
        option.rect.width() - margin * 2,
        option.rect.height() - margin * 2);
}
