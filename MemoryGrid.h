//
// Created by hifly_admin on 12/28/21.
//
#pragma once

#include <QWidget>


class MemoryGrid: public QWidget { // subclass of QWidget to implement grid layout for cards
        Q_OBJECT

 private:
    int m_size; // size of grid, it can be changed in constructor
    int m_x, m_y; // temporary position's of selected cards
    QTimer *m_Wait; // timer for waiting after cards are shown
    int scoreP1 = 0;
    int scoreP2 = 0;
    int highestscore = 0;
    int gameno = 1;
    int simulation1 = 0;
    int simulation2 = 0;
    QHash <int, int> hash;  // hash table that stores game properties

 public:
    MemoryGrid(int size); // constructor
    bool player1 = true; // boolean to detect if current player is player 1 or player2

 public slots:
    void cardSelected(int x, int y, int n); // slot of cards selected
    void hideCards(); // slot that hide cards if not match
    void gameWonMessage(); // slot that pops message when game ends
    void newGame(); // slot that starts new game
    void prevf(); // slot for previous results button
    void nextf(); // slot for next button

 signals:
     void gameWon(); // signal for game has been won
     void increment1(int); // signal to increment player1's point
     void increment2(int); // signal to increment player1's point
     void stop1(); // signal to stop timer of player 1
     void stop2(); // signal to stop timer of player 2
     void start1(); //signal to start timer of player 1
     void start2(); // signal to start timer of player 2
     void newgame(); // signal to start a new game
     void updateHighestScore(int); // signal to update highestscore
     void updateGameNo(int); // signal to update game number
     void updateTimer1(int); // signal to update player 1 timer
     void updateTimer2(int); // signal to update player 2 timer

};



