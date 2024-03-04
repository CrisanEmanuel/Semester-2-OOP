#include "model_view.h"
#include <utility>

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return int(tasks.size());
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        auto task = tasks[index.row()];
        if (index.column() == 0) return QString::number(task.get_id());
        else if (index.column() == 1) return QString::fromStdString(task.get_descriere());
        else if (index.column() == 2) return QString::fromStdString(task.get_stare());
        else if (index.column() == 3) return QString::number(task.get_programatori().size());
    }

    return QVariant{};
}

void MyTableModel::setTasks(vector<Task> t) {
    this->tasks = std::move(t);
    auto topLeft = createIndex(0,0);
    auto bottomRight = createIndex(rowCount(), columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}
