//
// Created by hifly_admin on 12/28/21.
//

#pragma once

#include <QWidget>
#include <QPushButton>

class MemoryCard : public QWidget { // Card subclass

    Q_OBJECT

 public:
    enum CardMode { // enum to identify the state of cards
            HIDDEN,
            SHOWN,
            ACTIVE
    };

 private:
   int x, y; // position of cards
   int N; // value of cards
   CardMode m_CardMode;
   QPushButton *m_Button;

 public:
    MemoryCard(int i, int j, int n); // constructor
    inline int getN() { return N; } // getter for n
    inline CardMode getMode() { return m_CardMode; } // getter to identify cards' mode
    void setMode(CardMode e); // setter of cardmode

 public slots:
    void clicked(); // clicked slot

 signals:
    void selected(int i, int j, int n); // signal that shows card is selected

};
