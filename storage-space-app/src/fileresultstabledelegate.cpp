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
    auto font = painter->font();
    int pixelSize = 14;
    font.setPixelSize(pixelSize);
    btn.rect = getRectFromOption(option, btnText, font, 4);
    btn.text = btnText;
    btn.state |= QStyle::State_Enabled;
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
    auto font = painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    auto bgRect = getRectFromOption(option, text, font, 4);
    painter->setBrush(btnBg);
    painter->setPen(btnBg);
    painter->drawRoundedRect(bgRect, 4, 4);
    painter->setPen(darkMode ? QColor::fromRgb(231, 231, 231) : Qt::black);
    QTextOption textOption(Qt::AlignmentFlag::AlignVCenter | Qt::AlignHCenter);
    painter->drawText(QRectF(bgRect), text, textOption);
    painter->restore();
}

QRect FileResultsTableDelegate::getRectFromOption(
    const QStyleOptionViewItem &option,
    const QString &text,
    const QFont &font,
    int margin)
{
    QFontMetrics fontMetrics(font);
    int txtWidth = fontMetrics.horizontalAdvance(text);
    int horizontalPadding = 12;
    int btnWidth = txtWidth + horizontalPadding * 2;
    int leftOffset = (option.rect.width() - btnWidth) / 2;
    return QRect(
        option.rect.left() + leftOffset,
        option.rect.top() + margin,
        btnWidth,
        option.rect.height() - margin * 2);
}
