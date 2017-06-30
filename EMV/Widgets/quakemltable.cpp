#include "quakemltable.h"

QuakeMLTableWidget::QuakeMLTableWidget(QWidget* parent)
    : QTableWidget(0, 6, parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

//    using Item = QTableWidgetItem;
    setHorizontalHeaderItem(0, new QTableWidgetItem{"ID"});
    setHorizontalHeaderItem(1, new QTableWidgetItem{"Date Time"});
    setHorizontalHeaderItem(2, new QTableWidgetItem{"Lat."});
    setHorizontalHeaderItem(3, new QTableWidgetItem{"Lon."});
    setHorizontalHeaderItem(4, new QTableWidgetItem{"Depth"});
    setHorizontalHeaderItem(5, new QTableWidgetItem{"Magnitude"});

    setSortingEnabled(true);

//    horizontalHeader()->setAlternatingRowColors(true);
//    horizontalHeader()->setSectionsClickable(true);
//    horizontalHeader()-;
}

void QuakeMLTableWidget::AddQuakeMLEvent(QuakeMLEvent event)
{
    using Item = QTableWidgetItem;
    QVector<QTableWidgetItem*> items {
        new Item{event.id},
        new Item{event.dateTime},
        new Item{event.latitude},
        new Item{event.longitude},
        new Item{event.depth},
        new Item{event.magnitude}
    };

    setSortingEnabled(false);

    insertRow(rowCount());

    for (int i = 0; i < items.count(); i++)
        setItem(rowCount() - 1, i, items.at(i));

    setSortingEnabled(true);
}

void QuakeMLTableWidget::AddQuakeMLEvents(QVector<QuakeMLEvent> events)
{
    for (auto event : events)
        AddQuakeMLEvent(event);

    this->selectRow(0);
}


