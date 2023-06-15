#include "syntaxhighlight.h"
#include <QFile>
#include <QDebug>

SyntaxHighlight::SyntaxHighlight(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    SetHigilighStyle("./ccppStyle.txt");
}

void SyntaxHighlight::SetHigilighStyle(const char *path)
{
    char buf[256];
    HighlightRule rule;

    // 读取文件中每一行，按@分割
    // 设置高亮文本规则和高亮颜色
    QFile file(path);
    file.open(QFile::ReadOnly);
    while (!file.atEnd()) {
        memset(buf, 0, 256);
        file.readLine(buf, 255);

        QString str(buf);
        QStringList list = str.split('@');

        // 将16进制字符串转为int型
        std::string cRGB;
        cRGB = list[1].trimmed().toStdString();
        int rgb = strtol(cRGB.c_str(), 0, 16);

        rule.pattern = QRegExp(list[0]);
        rule.format.setForeground(QBrush(QColor(rgb)));
        highlightRules.append(rule);
    }
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
