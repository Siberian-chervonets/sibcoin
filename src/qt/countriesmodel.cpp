#include "countriesmodel.h"

CountriesModel::CountriesModel(const QList<QtCountryInfo> &countries, QObject *parent) : SettingsModel(2, parent), countries(countries)
{
    listHead << tr("Name") << tr("ISO") << tr("Enabled");
}

void CountriesModel::setCountries(const QList<QtCountryInfo> &countries)
{
    this->countries = countries;
    Q_EMIT layoutChanged();
}

QList<QtCountryInfo> CountriesModel::getCountries() const
{
    return countries;
}

QVariant CountriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= countries.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return countries[index.row()].name;
        case 1:
            return countries[index.row()].iso;
        case 2:
            return countries[index.row()].enabled ? QString("x") : QString("");
        default:
            break;
        }
    }

    return QVariant();
}

bool CountriesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) {
        return false;
    }

    if (index.column() == 2) {
        countries[index.row()].enabled = value.toBool();
        Q_EMIT dataChanged();
    }

    return true;
}

int CountriesModel::rowCount(const QModelIndex &parent) const
{
    return countries.size();
}

bool CountriesModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!data->hasFormat("application/country.pos")) {
        return false;
    }

    if (action == Qt::IgnoreAction) {
        return true;
    }

    int endRow = 0;
    if (!parent.isValid() && row < 0) {
        endRow = countries.count();
    } else if (!parent.isValid()) {
        endRow = qMin(row, countries.count());
    } else {
        endRow = parent.row();
    }

    QByteArray encodedData = data->data("application/country.pos");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        int pos;
        stream >> pos;
        beginMoveRows(parent, pos, pos, parent, endRow);
        countries.move(pos, endRow);
        endMoveRows();
        endRow++;
    }

    Q_EMIT dataChanged();
    return true;
}
