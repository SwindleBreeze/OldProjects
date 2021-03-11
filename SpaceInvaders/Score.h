#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
    void setScore(int n);
    int setHighScore();
private:
    int score;
    int HighScore;
};

#endif // SCORE_H
