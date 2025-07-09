#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/tenni2s.cpp"
#include "core/playercategory.h"
#include "core/tennis.h"
#include "playermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::vector<Zawodnik> atpPlayersVector;
    std::vector<Zawodnik> wtaPlayersVector;
    std::vector<Turniej> season;
    int currentTournamentIndex = 0;

    PlayerModel* atpPlayers;
    PlayerModel* wtaPlayers;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updatePlayerList();
    // void simulateNextTournament();

private slots:
    void on_pushButton_addPlayer_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
