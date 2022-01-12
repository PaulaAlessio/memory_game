//
// Created by hifly_admin on 12/28/21.
//

#include "MemoryGrid.h"
#include "MemoryCard.h"
#include "MemoryTimer.h"
#include <QGridLayout>
#include <QTimer>
#include <QMessageBox>
#include <QLCDNumber>



//extern QHash <int, int> hash; // hash table that stores game properties

extern QLCDNumber * gamelcd;
extern QLCDNumber * score1;
extern QLCDNumber * score2;

MemoryGrid::MemoryGrid(int size)  // constructor
  : m_size(size), m_x(-1), m_y(0) // setting size and default positions
{
    QGridLayout *layout = new QGridLayout;  // creating grid layout
    setLayout(layout); // setting layout
    int n;
    for(n = 0; n < size*(size-1); n++)
    {
        // Choose the position of the card
        int r = (int)( ((double)rand()) / RAND_MAX * (size*(size-1)-n) );

        // Looking for empty grid cell
        int p = 0;
        while(r >= 0)
        {
            if(layout->itemAtPosition(p/size, p%size) == NULL) // if cell not null
            {
                r--;
                if(r < 0)
                {
                    MemoryCard *c = new MemoryCard(p/size, p%size, n/2 + 1); // create card
                    connect(c, SIGNAL(selected(int, int, int)), // when selected, call card selected
                        this, SLOT(cardSelected(int, int, int)));
                    layout->addWidget(c, p/size, p%size);
                }
            }
            p++;
        }
    }

    m_Wait = new QTimer;  // timer for waiting for cards that are chosen wrong
    m_Wait->setSingleShot(true);

    connect(m_Wait, SIGNAL(timeout()), this, SLOT(hideCards()));

}

#define GET_CARD(i, j) static_cast<MemoryCard*>(grid->itemAtPosition((i), (j))->widget()) // get card at i-th, j-th position

void MemoryGrid::cardSelected(int x, int y, int n) // when card is selected
{

    if(m_Wait->isActive()) // if there ara already active cards, return
        return ;

    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    GET_CARD(x, y)->setMode(MemoryCard::ACTIVE);  // setting card active

    if(m_x == -1) // if it is the first selected card, store position for comparing them later
    {
        m_x = x;
        m_y = y;
    }
    else
    {
        if(GET_CARD(m_x, m_y)->getN() == n)  // if cards match
        {
            GET_CARD(m_x, m_y)->setMode(MemoryCard::SHOWN); // set cards mode as shown because cards match
            GET_CARD(x, y)->setMode(MemoryCard::SHOWN);
            m_x = -1; // set temporary x -1 again
            int i, j;
            for(i = 0; i < m_size-1; i++)  // check every card if there are hidden cards(if game should end)
            {
                for(j = 0; j < m_size; j++)
                {
                    if(GET_CARD(i, j)->getMode() == MemoryCard::HIDDEN){ // if there is hidden card( game not ended )
                        if(player1){ // if player 1 gain the point
                            emit increment1(++scoreP1);
                            emit stop1();
                            emit start2();
                        }
                        else{  // if player 2 gain the point
                            emit increment2(++scoreP2);
                            emit stop2();
                            emit start1();
                        }
                        player1 = !player1;  // change the player
                        return ;
                    }
                }

            }
            if(player1){  // if these codes are running, it means that game is ended :) if player 1 who play last
                emit increment1(++scoreP1);
                emit stop1();
            }
            else{ // if player 2 play last
                emit increment2(++scoreP2);
                emit stop2();
            }
            emit gameWon(); // game has ended

        }
        else  // this means cards does not match
        {
            if(player1){ // player 1 played last, change timers
                emit stop1();
                emit start2();
            }
            else{  // player 2 played last, change timers
                emit stop2();
                emit start1();
            }
            m_x = -1;
            m_Wait->start(1500); // wait for 1.5 secs to see the nonmatching cards
            player1 = !player1;  // change player
        }
    }
}

void MemoryGrid::hideCards() // function that hides cards
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < m_size-1; i++)  // look at each cards if there is active card, change its mode to hidden
    {
        for(j = 0; j < m_size; j++)
        {
            if(GET_CARD(i, j)->getMode() == MemoryCard::ACTIVE)
                GET_CARD(i, j)->setMode(MemoryCard::HIDDEN);
        }
    }

}

void MemoryGrid::newGame()  // function that starts new game
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < m_size-1; i++) // firstly, player wants to play a new game, all cards must be at mode hidden
    {
        for(j = 0; j < m_size; j++)
        {
            if(GET_CARD(i, j)->getMode() == MemoryCard::ACTIVE || GET_CARD(i, j)->getMode() == MemoryCard::SHOWN)
                GET_CARD(i, j)->setMode(MemoryCard::HIDDEN); // change all cards' modes to hidden
        }
    }
    // Move to last game
    int currentGameno;
    do {
        currentGameno = gameno;
        nextf();
    } while (currentGameno != gameno);

    hash.insertMulti(gameno, scoreP1);  // store previous games' properties to hash table
    hash.insertMulti(gameno, scoreP2);
    hash.insertMulti(gameno, simulation1);
    hash.insertMulti(gameno, simulation2);

    simulation1=0;  // reset timers
    simulation2=0;
    emit updateTimer1(simulation1);
    emit updateTimer2(simulation2);
    emit stop2();
    emit start1();

    if(highestscore==0){  // change high score

        if(scoreP1 > scoreP2){
            highestscore = scoreP1;
        }
        else {
            highestscore = scoreP2;
        }
    }else{
        if(scoreP1 > highestscore){
            highestscore = scoreP1;
        }
        else if(highestscore < scoreP2){
            highestscore = scoreP2;
        }

    }
    emit updateHighestScore(highestscore);

    scoreP1=0;  // reset player points
    scoreP2=0;
    emit increment1(scoreP1);
    emit increment2(scoreP2);
    emit updateGameNo(++gameno); // increment game number
}

void MemoryGrid::prevf()  // show previous games' results
{
    QList<int> values = hash.values(--gameno);  // parse previous game's properties from hash table

    if(!values.empty()){  // show previous results

    score1->display(values[3]);
    score2->display(values[2]);
    emit updateTimer1(values[1]);
    emit updateTimer2(values[0]);
    emit updateGameNo(gameno);
    emit stop1();
    emit stop2();
    }
    else{
        ++gameno; // if values empty do not increment game number stupidly
    }
}
void MemoryGrid::nextf()  // show nextgames' results
{
    QList<int> currentValues = hash.values(gameno);
    if (currentValues.empty())
    {
       return; // We are already in the present game
    }
    QList<int> values = hash.values(++gameno); // parse next games'properties from hash table
    emit updateGameNo(gameno);
    if(!values.empty()){  // show properties
      score1->display(values[3]);
      score2->display(values[2]);
      emit updateTimer1(values[1]);
      emit updateTimer2(values[0]);
      emit stop1();
      emit stop2();
    }
    else
    {
        score1->display(scoreP1);
        score2->display(scoreP2);
        emit updateTimer1(simulation1);
        emit updateTimer2(simulation2);
        if (player1) {
            emit stop2();
            emit start1();
        }
        else {
            emit stop1();
            emit start2();
        }
    }
}

void MemoryGrid::gameWonMessage()  // if game ended pop up this awesome message :D
{   if(scoreP1 > scoreP2){
        QMessageBox::information(this, tr("Victory"),
            tr("Player 1 won the game!"));
    }
    else if(scoreP1 < scoreP2){
        QMessageBox::information(this, tr("Victory"),
            tr("Player 2 won the game!"));
    }
}