#include "Score.h"
#include <QFont>
#include "Game.h"
#include "HP.h"

extern Game *game;
int prev;
int prevscore;
Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // inicializacija score na 0
    score = 0;

    //nariši text
    setFont(QFont("times",16));
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::green);
    // size okna je 700,600
    setPos(500,570);

}

void Score::increase()
{
    score+=100;
    setPlainText(QString("Score: ") + QString::number(score));
    if(score%3600==0)
    {
        setHighScore();
        prev=game->health->getHealth();
        prevscore=game->score->getScore();
        game->close();
        game= new Game;
        game->show();
        game->health->setHealth(prev);
        game->score->setScore(prevscore);
    }
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int n)
{
    score=n;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::setHighScore()
{
    HighScore+=score;
    return HighScore;
}
