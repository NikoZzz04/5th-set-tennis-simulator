#include "playermodel.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

PlayerModel::PlayerModel(std::vector<Zawodnik>* data, QObject *parent)
    : QAbstractListModel(parent), players(data) {
}

int PlayerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return players->size();
}

QVariant PlayerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= players->size())
        return QVariant();

    const Zawodnik& player = players->at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return QString("%1. %2 %3 (%4, %5 lat) - Ranking: %6")
            .arg(index.row() + 1)
            .arg(QString::fromStdString(player.getImie()))
            .arg(QString::fromStdString(player.getNazwisko()))
            .arg(QString::fromStdString(player.getNarodowosc()))
            .arg(player.getAge())
            .arg(player.getRank());
    case Qt::ToolTipRole:
        return QString("Umiejętności: %1/100").arg(player.getUmiejetnoscTeoretyczna());
    default:
        return QVariant();
    }
}

void PlayerModel::addPlayer(const Zawodnik& player) {
    beginInsertRows(QModelIndex(), players->size(), players->size());
    players->push_back(player);
    endInsertRows();
}

void PlayerModel::removePlayer(int index) {
    if (index >= 0 && index < players->size()) {
        beginRemoveRows(QModelIndex(), index, index);
        players->erase(players->begin() + index);
        endRemoveRows();
    }
}

void PlayerModel::saveToCSV(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Nie można otworzyć pliku do zapisu:" << filename;
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Encoding::Utf8);

    // Nagłówek CSV
    out << "LP,Imie,Nazwisko,Wiek,Narodowosc,Ranking,UmiejetnoscTeoretyczna,TournamentPts\n";

    for (size_t i = 0; i < players->size(); ++i) {
        const Zawodnik& player = players->at(i);
        out << (i + 1) << ","
            << QString::fromStdString(player.getImie()) << ","
            << QString::fromStdString(player.getNazwisko()) << ","
            << player.getAge() << ","
            << QString::fromStdString(player.getNarodowosc()) << ","
            << player.getRank() << ","
            << player.getUmiejetnoscTeoretyczna();

        // Dodaj punkty turniejowe (przykład - 36 tygodni)
        for (int week = 0; week < 36; ++week) {
            out << "," << player.getPtsByWeek(week);
        }
        out << "\n";
    }

    file.close();
    qDebug() << "Zapisano do CSV:" << filename;
}

void PlayerModel::loadFromCSV(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Nie można otworzyć pliku:" << filename;
        return;
    }

    beginResetModel();
    players->clear();

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Encoding::Utf8);

    QString line = in.readLine(); // Pomiń nagłówek

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 7) {
            int lp = fields[0].toInt();
            std::string imie = fields[1].toStdString();
            std::string nazwisko = fields[2].toStdString();
            int wiek = fields[3].toInt();
            std::string narodowosc = fields[4].toStdString();
            int ranking = fields[5].toInt();
            float umiejetnosc = fields[6].toFloat();

            std::vector<int> tournamentPts;
            for (int i = 7; i < fields.size() && i < 43; ++i) {
                tournamentPts.push_back(fields[i].toInt());
            }

            // Uzupełnij do 36 tygodni jeśli brakuje
            while (tournamentPts.size() < 36) {
                tournamentPts.push_back(0);
            }

            Zawodnik player(lp, imie, nazwisko, wiek, narodowosc, umiejetnosc, ranking, tournamentPts);
            players->push_back(player);
        }
    }

    endResetModel();
    file.close();
    qDebug() << "Załadowano z CSV:" << filename << "- zawodników:" << players->size();
}
