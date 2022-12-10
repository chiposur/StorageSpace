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
};

#endif // FILERESULTSTABLEDELEGATE_H
