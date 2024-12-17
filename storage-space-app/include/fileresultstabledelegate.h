#ifndef FILERESULTSTABLEDELEGATE_H
#define FILERESULTSTABLEDELEGATE_H

#include <QStyledItemDelegate>

class FileResultsTableDelegate : public QStyledItemDelegate
{
public:
    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

private:
    void paintCustomMacButton(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QString &text
    ) const;

    static QRect getRectFromOption(
        const QStyleOptionViewItem &option,
        const QString &text,
        const QFont &font,
        int margin);

    static const QString OPEN_IN_FOLDER_TXT;
    static const QString DELETE_TXT;
};

#endif // FILERESULTSTABLEDELEGATE_H
