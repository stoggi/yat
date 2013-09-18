/**************************************************************************************************
* Copyright (c) 2012 Jørgen Lind
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
* associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
* NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
* OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
***************************************************************************************************/

#ifndef TEXT_SEGMENT_LINE_H
#define TEXT_SEGMENT_LINE_H

#include <QtCore/QObject>

#include "text.h"

class Screen;
class QQuickItem;

class Block : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(Screen *screen READ screen CONSTANT)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
public:
    Block(Screen *screen);
    ~Block();

    Q_INVOKABLE Screen *screen() const;

    void clear();
    void clearCharacters(int from, int to);
    void deleteCharacters(int from, int to, int margin = -1);

    void setWidth(int width);
    int width() const;

    void replaceAtPos(int i, const QString &text, const TextStyle &style);
    void insertAtPos(int i, const QString &text, const TextStyle &style);

    int index() const;
    void setIndex(int index);

    QString *textLine();

    void setVisible(bool visible);
    bool visible() const;

    void dispatchEvents();
    void releaseTextObjects();

    QVector<TextStyleLine> style_list();

    void printStyleList() const;
    void printStyleList(QDebug &debug) const;
signals:
    void indexChanged();
    void visibleChanged();
    void widthChanged();
private:
    void mergeCompatibleStyles();
    Screen *m_screen;
    QString m_text_line;
    QVector<TextStyleLine> m_style_list;
    int m_index;
    int m_new_index;

    bool m_visible;
    QVector<Text *> m_to_delete;
    bool m_changed;

    bool m_delete_handle;
};

#endif // TEXT_SEGMENT_LINE_H
