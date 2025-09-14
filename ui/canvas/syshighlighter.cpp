//
// Created by Ruhaan on 13/09/25.
//

#include "syshighlighter.h"

PythonSyntaxHighlighter::PythonSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    const QColor keywordColor = QColor("#C678DD");
    const QColor classColor = QColor("#E5C07B");
    const QColor functionColor = QColor("#61AFEF");
    const QColor stringColor = QColor("#98C379");
    const QColor commentColor = QColor("#5C6370");
    const QColor numberColor = QColor("#D19A66");
    const QColor operatorColor = QColor("#56B6C2");
    const QColor decoratorColor = QColor("#E06C75");
    const QColor selfColor = QColor("#E06C75");
    const QColor builtinColor = QColor("#56B6C2");

    keywordFormat.setForeground(keywordColor);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns = {
        "\\bFalse\\b", "\\bNone\\b", "\\bTrue\\b", "\\band\\b", "\\bas\\b", "\\bassert\\b",
        "\\bbreak\\b", "\\bclass\\b", "\\bcontinue\\b", "\\bdef\\b", "\\bdel\\b", "\\belif\\b",
        "\\belse\\b", "\\bexcept\\b", "\\bfinally\\b", "\\bfor\\b", "\\bfrom\\b", "\\bglobal\\b",
        "\\bif\\b", "\\bimport\\b", "\\bin\\b", "\\bis\\b", "\\blambda\\b", "\\bnonlocal\\b",
        "\\bnot\\b", "\\bor\\b", "\\bpass\\b", "\\braise\\b", "\\breturn\\b", "\\btry\\b",
        "\\bwhile\\b", "\\bwith\\b", "\\byield\\b"
    };

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // class name ??
    classFormat.setForeground(classColor);
    classFormat.setFontWeight(QFont::Bold);
    HighlightingRule rule;
    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z0-9_]*\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    // calls!!
    functionFormat.setForeground(functionColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\s*\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // str?
    stringFormat.setForeground(stringColor);
    rule.pattern = QRegularExpression("\"[^\"\\\\]*(\\\\.[^\"\\\\]*)*\"|'[^'\\\\]*(\\\\.[^'\\\\]*)*'");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    // lol comments?
    commentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    // nums
    numberFormat.setForeground(numberColor);
    rule.pattern = QRegularExpression("\\b\\d+\\.?\\d*\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    // ops
    operatorFormat.setForeground(operatorColor);
    rule.pattern = QRegularExpression("[\\+\\-\\*\\/\\%\\=\\<\\>\\!\\&\\|\\^\\~]");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    // decorators??
    decoratorFormat.setForeground(decoratorColor);
    rule.pattern = QRegularExpression("@[A-Za-z0-9_\\.]+");
    rule.format = decoratorFormat;
    highlightingRules.append(rule);

    // self??
    selfFormat.setForeground(selfColor);
    selfFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("\\bself\\b");
    rule.format = selfFormat;
    highlightingRules.append(rule);

    // build in function?
    builtinFormat.setForeground(builtinColor);
    QStringList builtinPatterns = {
        "\\babs\\b", "\\ball\\b", "\\bany\\b", "\\bascii\\b", "\\bbin\\b", "\\bbool\\b", "\\bbytearray\\b",
        "\\bbytes\\b", "\\bcallable\\b", "\\bchr\\b", "\\bclassmethod\\b", "\\bcompile\\b", "\\bcomplex\\b",
        "\\bdelattr\\b", "\\bdict\\b", "\\bdir\\b", "\\bdivmod\\b", "\\benumerate\\b", "\\beval\\b",
        "\\bexec\\b", "\\bfilter\\b", "\\bfloat\\b", "\\bformat\\b", "\\bfrozenset\\b", "\\bgetattr\\b",
        "\\bglobals\\b", "\\bhasattr\\b", "\\bhash\\b", "\\bhelp\\b", "\\bhex\\b", "\\bid\\b", "\\binput\\b",
        "\\bint\\b", "\\bisinstance\\b", "\\bissubclass\\b", "\\biter\\b", "\\blen\\b", "\\blist\\b",
        "\\blocals\\b", "\\bmap\\b", "\\bmax\\b", "\\bmemoryview\\b", "\\bmin\\b", "\\bnext\\b",
        "\\bobject\\b", "\\boct\\b", "\\bopen\\b", "\\bord\\b", "\\bpow\\b", "\\bprint\\b", "\\bproperty\\b",
        "\\brange\\b", "\\brepr\\b", "\\breversed\\b", "\\bround\\b", "\\bset\\b", "\\bsetattr\\b",
        "\\bslice\\b", "\\bsorted\\b", "\\bstaticmethod\\b", "\\bstr\\b", "\\bsum\\b", "\\bsuper\\b",
        "\\btuple\\b", "\\btype\\b", "\\bvars\\b", "\\bzip\\b", "\\b__import__\\b"
    };

    for (const QString &pattern : builtinPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = builtinFormat;
        highlightingRules.append(rule);
    }

    // multiplie str??
    multiLineStringFormat.setForeground(stringColor);
    tripleQuotesStart = QRegularExpression("('''|\"\"\")");
    tripleQuotesEnd = QRegularExpression("('''|\"\"\")");
}

void PythonSyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
    int startIndex = 0;

    if (previousBlockState() != 1) {
        startIndex = text.indexOf(tripleQuotesStart);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = tripleQuotesEnd.match(text, startIndex + 3);
        int endIndex = match.capturedStart();
        int blockLength;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            blockLength = text.length() - startIndex;
        } else {
            blockLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, blockLength, multiLineStringFormat);
        startIndex = text.indexOf(tripleQuotesStart, startIndex + blockLength);
    }
}
