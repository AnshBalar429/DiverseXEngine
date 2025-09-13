//
// Created by Ruhaan on 13/09/25.
//

#ifndef PYTHONSYNTAXHIGHLIGHTER_H
#define PYTHONSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QVector>

class PythonSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit PythonSyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat operatorFormat;
    QTextCharFormat decoratorFormat;
    QTextCharFormat selfFormat;
    QTextCharFormat builtinFormat;

    QRegularExpression tripleQuotesStart;
    QRegularExpression tripleQuotesEnd;
    QTextCharFormat multiLineStringFormat;
};

#endif // PYTHONSYNTAXHIGHLIGHTER_H
