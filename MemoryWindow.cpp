//
// Created by hifly_admin on 1/7/22.
//

#include "MemoryWindow.h"
#include "MemoryGrid.h"
#include <QLabel>
#include "MemoryTimer.h"
#include "MemoryGrid.h"
#include <QPushButton>
#include <QTime>
#include <QWidget>
#include <QTimer>
#include <QLCDNumber>
#include <QHBoxLayout>

QLCDNumber * score1;
QLCDNumber * score2;

MemoryWindow::MemoryWindow() {

    auto *game = new MemoryGrid(6);

    auto simulationTimer1 = new MemoryTimer;  // timer that for player 1's lcd
    simulationTimer1->start(1000);  // 1 sec
    QWidget::connect(simulationTimer1, SIGNAL(timeout()),simulationTimer1, SLOT(countup())); // each 1 sec, count up
    QWidget::connect(game, SIGNAL(stop1()),simulationTimer1, SLOT(stop()));  // stop when player changed
    QWidget::connect(game, SIGNAL(start1()),simulationTimer1, SLOT(startf()));  // start when player changed

    auto simulationTimer2 = new MemoryTimer;  // timer that for player 1's lcd
    QWidget::connect(simulationTimer2, SIGNAL(timeout()),simulationTimer2, SLOT(countup()));
    // each 1 sec, count up
    QWidget::connect(game, SIGNAL(stop2()),simulationTimer2, SLOT(stop()));  // stop when player changed
    QWidget::connect(game, SIGNAL(start2()),simulationTimer2, SLOT(startf()));  // start when player changed


    // Layouts
    QHBoxLayout *main, *left,  *rightcenter, *rightbottom;
    QVBoxLayout *right, *righttop, *rightbottomleft, *rightbottomcenter, *rightbottomright;


    // Left (game)
    QWidget::connect(game, SIGNAL(gameWon()), game, SLOT(gameWonMessage())); // pop up message at game End


    // Right-top
    QPushButton *new_game = new QPushButton("New game");  // creates new game button
    QWidget::connect(new_game, SIGNAL(clicked()), game, SLOT(newGame()));  // when new game is clicked, create new game

    QPushButton *prev = new QPushButton("Prev. Results");  // creates prev. button
    QWidget::connect(prev, SIGNAL(clicked()), game, SLOT(prevf()));  // when prev. clicked, show prev results

    QPushButton *next = new QPushButton("Next Results");  // creates next button
    QWidget::connect(next, SIGNAL(clicked()), game, SLOT(nextf()));  // when clicked, show ne    xt results

    righttop = new QVBoxLayout;  // right-top layout
    righttop->addWidget(new_game);
    righttop->addWidget(prev);
    righttop->addWidget(next);

    // Medium layout
    rightcenter = new QHBoxLayout; // right-center layout

    auto *gamehrz = new QHBoxLayout; // horizontal layout for game score and lcd
    auto *gamelbl = new QLabel("Game No: ");
    auto *gamelcd = new QLCDNumber;
    gamelcd->display(1);
    QWidget::connect(game, SIGNAL(updateGameNo(int)), gamelcd, SLOT(display(int)));
    gamehrz->addWidget(gamelbl);
    gamehrz->addWidget(gamelcd);

    auto *highhrz = new QHBoxLayout;
    auto *highlbl = new QLabel("Highest score: ");
    auto *highlcd = new QLCDNumber;
    highlcd->display(0);
    QWidget::connect(game, SIGNAL(updateHighestScore(int)), highlcd, SLOT(display(int)));
    // highlcd->setFixedSize(100,30);
    highhrz->addWidget(highlbl);
    highhrz->addWidget(highlcd);

    // Right down
    QLabel *bos = new QLabel(" "); // boş label
    QLabel *score = new QLabel("        Score");  // score label
    QLabel *time = new QLabel("        Time");  // time label


    QLabel *pl1 = new QLabel("Player 1 ");  // player 1 label
    score1 = new QLCDNumber;  // score 1 lcd
    QWidget::connect(game, SIGNAL(increment1(int)), score1, SLOT(display(int)));


    auto time1 = new QLCDNumber;
    auto time2 = new QLCDNumber;
    QWidget::connect(simulationTimer1, SIGNAL(updateTimer(int)), time1, SLOT(display(int)));
    QWidget::connect(simulationTimer2, SIGNAL(updateTimer(int)), time2, SLOT(display(int)));
    QWidget::connect(game, SIGNAL(updateTimer1(int)), simulationTimer1, SLOT(setTimer(int)));
    QWidget::connect(game, SIGNAL(updateTimer2(int)), simulationTimer2, SLOT(setTimer(int)));
    QWidget::connect(game, SIGNAL(updateTimer1(int)), time1, SLOT(display(int)));
    QWidget::connect(game, SIGNAL(updateTimer2(int)), time2, SLOT(display(int)));



    QLabel *pl2 = new QLabel("Player 2");
    score2 = new QLCDNumber;
    QWidget::connect(game, SIGNAL(increment2(int)), score2, SLOT(display(int)));

    rightbottom = new QHBoxLayout;
    rightbottomleft = new QVBoxLayout;
    rightbottomleft->addWidget(bos);
    rightbottomleft->addWidget(score);
    rightbottomleft->addWidget(time);

    rightbottomcenter = new QVBoxLayout;
    rightbottomcenter->addWidget(pl1);
    rightbottomcenter->addWidget(score1);
    rightbottomcenter->addWidget(time1);

    rightbottomright = new QVBoxLayout;
    rightbottomright->addWidget(pl2);
    rightbottomright->addWidget(score2);
    rightbottomright->addWidget(time2);


    rightbottom->addLayout(rightbottomleft);
    rightbottom->addLayout(rightbottomcenter);
    rightbottom->addLayout(rightbottomright);



    rightcenter->addLayout(gamehrz);
    rightcenter->addLayout(highhrz);

    right = new QVBoxLayout;  // right layout
    right->addLayout(righttop);
    right->addLayout(rightcenter);
    right->addLayout(rightbottom);

    left = new QHBoxLayout;  // bottom layout
    left->addWidget(game);


    main = new QHBoxLayout;  // main layout
    main->addLayout(left);
    main->addLayout(right);


    setLayout(main);

    setMinimumHeight(300);
    setMinimumWidth(600);
    //widget.setFixedHeight(300); // fixed sizes of windows
    //widget.setFixedWidth(600);
    show();
}
