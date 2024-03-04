#pragma once
#pragma once
#include "service.h"
#include <QApplication>
#include <QString>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <QTableView>
#include <QListView>
#include <QPainter>

class MyTableModel: public QAbstractTableModel {
private:
    vector<Task> tasks;

public:

    explicit MyTableModel(const vector<Task>& t): tasks {t} {}

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setTasks(vector<Task> p);
};