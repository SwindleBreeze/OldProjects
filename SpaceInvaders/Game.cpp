#include <QApplication>
#include "SpaceShip.h"
#include "Enemy.h"
#include "Game.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QElapsedTimer>
#include <QTimer>
#include <QtDebug>
#include <QGraphicsTextItem>
#include <ctime>
#include "EnemyBullet.h"
#include <QObject>
#include <QMediaPlayer>
#include <QImage>
#include <QBrush>
#include "BUttons.h"
#include "HP.h"
#include "Score.h"

Game::Game(QWidget *parent)
{
    int randtime=rand()%2500+500;
    //Naredi sceno
    scene = new QGraphicsScene();
    //nastavi velikost scene, ki je ista kot view in ustavi povečevanje scene
    scene->setSceneRect(/*kje zacne*/0,/*Kje konca*/0,/*velikost*/700,600);

    setBackgroundBrush(QBrush(QImage(":/images/prenos.png")));
    setScene(scene);
    //onemogoči povečevanje scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //nastavi velikost viewa
    setFixedSize(700,600);


    //naredi stvar, ki ustavis v sceno
    player = new SpaceShip();
    player->setPixmap(QPixmap(":/images/baseshipb.ico"));
    //Nastavi pozicijo igralca
    player->setPos(330,525);
    //naredi igralca focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // dodaj igralca v sceno
    scene->addItem(player);

    //dodaj score
    score = new Score();
    scene->addItem(score);

    //dodaj HP
    health=new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);


    //spawn enemy
    mark = new EnemyMarker();
    scene->addItem(mark);
    int XPos=5;
    int YPos=5;
    for(int i=0;i<39;i++)
    {
        if(XPos<650)
        {
            enemy=new Enemy();
            enemy->setX(XPos);
            enemy->setY(YPos);
            scene->addItem(enemy);
            XPos+=58;
        }
        else
        {
            XPos=5;
            YPos+=30;
        }

    }
    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(1000);

    //igranje background muzike
    QMediaPlayer *predvajalnik = new QMediaPlayer();
    predvajalnik->setMedia(QUrl("qrc:/sounds/spaceinvaders1.mp3"));
    predvajalnik->play();
}
void Game::zazeni()
{
    scene->clear();
    show();
    srand(time(NULL));
    int randtime=rand()%2500+500;
    //Naredi sceno
    scene = new QGraphicsScene();
    //nastavi velikost scene, ki je ista kot view in ustavi povečevanje scene
    scene->setSceneRect(/*kje zacne*/0,/*Kje konca*/0,/*velikost*/700,600);

    setBackgroundBrush(QBrush(QImage(":/images/prenos.png")));
    setScene(scene);
    //onemogoči povečevanje scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //nastavi velikost viewa
    setFixedSize(700,600);


    //naredi stvar, ki ustavis v sceno
    player = new SpaceShip();
    player->setPixmap(QPixmap(":/images/baseshipb.ico"));
    //Nastavi pozicijo igralca
    player->setPos(330,525);
    //naredi igralca focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // dodaj igralca v sceno
    scene->addItem(player);

    //dodaj score
    score = new Score();
    scene->addItem(score);

    //dodaj HP
    health=new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);


    //spawn enemy
    mark = new EnemyMarker();
    scene->addItem(mark);
    int XPos=5;
    int YPos=5;
    for(int i=0;i<39;i++)
    {
        if(XPos<650)
        {
            enemy=new Enemy();
            enemy->setX(XPos);
            enemy->setY(YPos);
            scene->addItem(enemy);
            XPos+=58;
        }
        else
        {
            XPos=5;
            YPos+=30;
        }

    }
    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(1000);


    //igranje background muzike
    QMediaPlayer *predvajalnik = new QMediaPlayer();
    predvajalnik->setMedia(QUrl("qrc:/sounds/spaceinvaders1.mp3"));
    predvajalnik->play();
}

void Game::zapri()
{
    scene->clear();
    close();
}

void Game::prikazMainMenu()
{
    //naredi tekst
    scene->clear();
    scene = new QGraphicsScene();
    //nastavi velikost scene, ki je ista kot view in ustavi povečevanje scene
    scene->setSceneRect(/*kje zacne*/0,/*Kje konca*/0,/*velikost*/700,600);

    setBackgroundBrush(QBrush(QImage(":/images/MenuTest1.png")));
    setScene(scene);
    //onemogoči povečevanje scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //nastavi velikost viewa
    setFixedSize(700,600);
    //naredi play button
    Button* playButton = new Button(QString("Play"));
    int bxPos= this->width()/2-playButton->boundingRect().width()/2;
    int byPos = 400;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(zazeni()));
    scene->addItem(playButton);

    //naredi exit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos= this->width()/2-quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(zapri()));
    scene->addItem(quitButton);
    show();

}

void Game::prikazContinue()
{
    //naredi tekst
    int HighScore=score->getScore();
    player->setEnabled(false);
    scene->clear();
    scene = new QGraphicsScene();

    //nastavi velikost scene, ki je ista kot view in ustavi povečevanje scene
    scene->setSceneRect(/*kje zacne*/0,/*Kje konca*/0,/*velikost*/700,600);

    QGraphicsTextItem *Game_over= new QGraphicsTextItem;
    QGraphicsTextItem *HIScore = new QGraphicsTextItem;

    Game_over->setDefaultTextColor(Qt::green);
    Game_over->setX(scene->width()/2-90);
    Game_over->setY(scene->height()/2);
    Game_over->setScale(3);
    Game_over->setPlainText("Game Over");
    HIScore->setDefaultTextColor(Qt::green);
    HIScore->setY(scene->height()/2+60);
    HIScore->setX(scene->width()/2-55);
    scene->addItem(Game_over);
    HIScore->setPlainText(QString("HIGH SCORE : ")+QString::number(HighScore));
    scene->addItem(HIScore);
    setScene(scene);
    //onemogoči povečevanje scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //nastavi velikost viewa
    setFixedSize(700,600);
    //naredi play button
    Button* playButton = new Button(QString("Continue"));
    int bxPos= this->width()/2-playButton->boundingRect().width()/2;
    int byPos = 400;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(zazeni()));
    scene->addItem(playButton);

    //naredi exit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos= this->width()/2-quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(zapri()));
    scene->addItem(quitButton);
    show();

}


