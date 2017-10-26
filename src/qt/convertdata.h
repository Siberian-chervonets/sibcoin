#ifndef CONVERTDATA_H
#define CONVERTDATA_H

#include <QList>
#include "dto.h"

const int decimals = 8;

class ConvertData {
public:
    static QtOfferInfo toQtOfferInfo(const OfferInfo &offer);
    static QList<QtOfferInfo> toListQtOfferInfo(const std::list<OfferInfo> &offers);
    static OfferInfo fromQtOfferInfo(const QtOfferInfo &qtOffer);

    static QtMyOfferInfo toQtMyOfferInfo(const MyOfferInfo &offer);
    static QList<QtMyOfferInfo> toListQtMyOfferInfo(const std::list<MyOfferInfo> &offers);
    static MyOfferInfo fromQtMyOfferInfo(const QtMyOfferInfo &qtOffer);

    static QString toQString(const std::string &str);
    static QString toTr(const std::string &str);
    static std::string fromQString(const QString &str);

    static QString toUiPrice(const quint64 &i);
    static quint64 fromUiPrice(QString str);
};

#endif
