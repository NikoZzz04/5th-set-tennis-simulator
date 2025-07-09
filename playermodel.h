// playermodel.h
#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "core/tennis.h"
#include <QAbstractListModel>
#include <vector>

class PlayerModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit PlayerModel(std::vector<Zawodnik>* data, QObject *parent = nullptr);

    // Wymagane metody dla QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Metody do zarządzania danymi
    void addPlayer(const Zawodnik& player);
    void removePlayer(int index);
    void updatePlayer(int index, const Zawodnik& player);

    // Metody do CSV
    void saveToCSV(const QString& filename);
    void loadFromCSV(const QString& filename);

private:
    std::vector<Zawodnik>* players;
};

#endif // PLAYERMODEL_H
