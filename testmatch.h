#ifndef TESTMATCH_H
#define TESTMATCH_H

#include <QMainWindow>

#include "core/match.h"
#include<optional>

namespace Ui {
class TestMatch;
}

class TestMatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMatch(QWidget *parent = nullptr);
    ~TestMatch();
    void beginMatch(){
        Player playerFirst={"Swiatek", "Iga", 24, "Poland",15,15,15,15,15,15,15,15,15};
        Player playerSecond={"Sabalenka", "Aryna", 28, "Neutral",14,14,14,14,14,14,14,14,14};
        MatchRules rules{2,6,10,7};
        match=Match{playerFirst, playerSecond, rules};

    }
private slots:
    void on_pushButton_clicked();

private:
    Ui::TestMatch *ui;
    std::optional<Match>match;

};

#endif // TESTMATCH_H
