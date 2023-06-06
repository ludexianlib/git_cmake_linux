#include "syntaxhighlight.h"

SyntaxHighlight::SyntaxHighlight(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    HighlightRule rule;

    // 关键字高亮规则
    QStringList keywords;
    keywords << "\\bFMAX\\b" << "\\bF\\d+\\b";
    foreach(const QString& pattern, keywords) {
        // 高亮表达式
        rule.pattern = QRegExp(pattern);

        // 高亮颜色
        rule.format.setForeground(QBrush(QColor(220, 150, 15)));
        highlightRules.append(rule);
    }

    // 行号高亮规则
    rule.pattern = QRegExp("^\\d+\\b");
    rule.format.setForeground(QBrush(QColor(10, 138, 158)));
    highlightRules.append(rule);

    // ; 注释高亮规则
    rule.pattern = QRegExp(";.*");
    rule.format.setForeground(QBrush(QColor(10, 159, 10)));
    highlightRules.append(rule);

    // 数字坐标规则
    rule.pattern = QRegExp("[+-]*\\d+\\.\\d{0,}|[+-]\\d+");
    rule.format.setForeground(QBrush(QColor(20, 60, 210)));
    highlightRules.append(rule);

    // ""高亮规则
    rule.pattern = QRegExp("\".*\"");
    rule.format.setForeground(QBrush(QColor(198, 98, 23)));
    highlightRules.append(rule);
}

void SyntaxHighlight::highlightBlock(const QString &text)
{
    // 遍历vector 查找text中符合高亮的语法
    foreach (const HighlightRule &rule, highlightRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            // 获取匹配的语法高亮显示
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    // 保存文本块状态
    setCurrentBlockState(0);
}
