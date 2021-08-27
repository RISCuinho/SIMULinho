/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "memorytable.h"

#include <QScrollBar>
#include <QHeaderView>

MemoryTable::MemoryTable(QWidget *parent): QTableView(parent){
    fieldNameTableView = new QTableView(this);
}

MemoryTable::MemoryTable(QAbstractItemModel * model)
{
      fieldNameTableView = new QTableView(this);

      init(model);
}


MemoryTable::~MemoryTable()
{
      delete fieldNameTableView;
}

void MemoryTable::init(QAbstractItemModel *model){
    setModel(model);

    init();

    //connect the headers and scrollbars of both tableviews together
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &MemoryTable::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &MemoryTable::updateSectionHeight);

    connect(fieldNameTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            fieldNameTableView->verticalScrollBar(), &QAbstractSlider::setValue);

}

void MemoryTable::init()
{
      fieldNameTableView->setModel(model());
      fieldNameTableView->setFocusPolicy(Qt::NoFocus);
      fieldNameTableView->verticalHeader()->hide();
      fieldNameTableView->horizontalHeader()
              ->setSectionResizeMode(QHeaderView::Fixed);

      viewport()->stackUnder(fieldNameTableView);

      fieldNameTableView->setStyleSheet(
                  "QTableView { border: none;"
                  "background-color: #8EDE21;"
                  "selection-background-color: #999}"); //for demo purposes

      fieldNameTableView->setSelectionModel(selectionModel());
      for (int col = 1; col < model()->columnCount(); ++col)
            fieldNameTableView->setColumnHidden(col, true);

      fieldNameTableView->setColumnWidth(0, columnWidth(0) );

      fieldNameTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      fieldNameTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      fieldNameTableView->show();

      updateRegisterNamesTableGeometry();

      setHorizontalScrollMode(ScrollPerPixel);
      setVerticalScrollMode(ScrollPerPixel);
      fieldNameTableView->setVerticalScrollMode(ScrollPerPixel);
}

void MemoryTable::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
      if (logicalIndex == 0){
            fieldNameTableView->setColumnWidth(0, newSize);
            updateRegisterNamesTableGeometry();
      }
}

void MemoryTable::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
    fieldNameTableView->setRowHeight(logicalIndex, newSize);
}

void MemoryTable::resizeEvent(QResizeEvent * event)
{
      QTableView::resizeEvent(event);
      updateRegisterNamesTableGeometry();
 }

QModelIndex MemoryTable::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveLeft && current.column() > 0
            && visualRect(current).topLeft().x() < fieldNameTableView->columnWidth(0) ){
        const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - fieldNameTableView->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return current;
}

void MemoryTable::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}


void MemoryTable::updateRegisterNamesTableGeometry()
{
    fieldNameTableView->setGeometry(
                verticalHeader()->width() + frameWidth(),
                frameWidth(), columnWidth(0),
                viewport()->height() + horizontalHeader()->height());
}