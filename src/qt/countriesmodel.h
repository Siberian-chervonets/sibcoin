#ifndef COUNTRIESMODEL_H
#define COUNTRIESMODEL_H

#include "settingsmodel.h"
#include "dto.h"

class CountriesModel : public SettingsModel
{
    Q_OBJECT

public:
    CountriesModel(const QList<QtCountryInfo> &countries, QObject *parent = nullptr);

    void setCountries(const QList<QtCountryInfo> &countries);
    QList<QtCountryInfo> getCountries() const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

private:
    QList<QtCountryInfo> countries;
};

#endif
