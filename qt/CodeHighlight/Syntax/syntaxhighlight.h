#ifndef SYNTAXHIGHLIGHT_H
#define SYNTAXHIGHLIGHT_H

#include <QColor>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QSyntaxHighlighter>

class SyntaxHighlight : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit SyntaxHighlight(QTextDocument *parent = 0);

public slots:
    void SetHigilighStyle(const char* path);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> highlightRules;

signals:

public slots:

};

#endif // SYNTAXHIGHLIGHT_H
