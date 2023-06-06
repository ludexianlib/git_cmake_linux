#include "codeeditor.h"
#include <QPainter>
#include <QDebug>
#include <QTextBlock>

CodeEditor::CodeEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    // 行号区域的绘图事件
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::white);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();

    // 获取文本块的顶部和底部
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    // 绘制可见区域
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(128, 128, 128));
            painter.drawText(0, top, lineNumberArea->width() - 8, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

int CodeEditor::lineNumberAreaWidth()
{
    // 计算行号区域的宽度
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 10 + fontMetrics().width(QLatin1Char('9')) * digits;
    return space;
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    // resize 事件
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int /*newBlockCount*/)
{
    // 更新行号的宽度
    // 根据行号宽度设置页边距
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::highlightCurrentLine()
{
    // 高亮光标行
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(230, 240, 255);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//        selection.format.setForeground(Qt::black);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    // 文本框滚动时更新行号区域
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
