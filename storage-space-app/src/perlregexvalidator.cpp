#include "perlregexvalidator.h"

QValidator::State PerlRegexValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos)
    QRegularExpression expr(input);
    if (expr.isValid())
    {
        return QValidator::Acceptable;
    }
    return QValidator::Invalid;
}

void PerlRegexValidator::fixup(QString &input) const
{
    Q_UNUSED(input)
}
