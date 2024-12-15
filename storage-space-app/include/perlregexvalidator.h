#ifndef PERLREGEXVALIDATOR_H
#define PERLREGEXVALIDATOR_H

#include <QValidator>

class PerlRegexValidator : public QValidator
{
    Q_OBJECT

public:
    PerlRegexValidator();

    QValidator::State validate(QString &input, int &pos) const;
    void fixup(QString &input) const;
};

#endif // PERLREGEXVALIDATOR_H
