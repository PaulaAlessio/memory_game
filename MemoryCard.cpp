//
// Created by hifly_admin on 12/28/21.
//

#include "MemoryCard.h"


MemoryCard::MemoryCard(int i, int j, int n) // constructor for Card class
        : x(i), y(j), N(n), m_CardMode(MemoryCard::HIDDEN)  // properties of card objects
{
    m_Button = new QPushButton(QIcon("../memory_figures/hidden.png"), "", this);
    m_Button->setFixedSize(125,125);
    m_Button->setIconSize(QSize(125,125));
    connect(m_Button, SIGNAL(clicked()),
            this, SLOT(clicked()));
    setFixedSize(125,125);
}

void MemoryCard::clicked()  // when clicked
{
    if(m_CardMode == MemoryCard::HIDDEN)
        emit selected(x, y, N);
}

void MemoryCard::setMode(CardMode e)  // set mode of cards
{
    m_CardMode = e;
    switch(e)
    {

        case MemoryCard::HIDDEN: // if hiden, put ?
            m_Button->setIcon(QIcon("../memory_figures/hidden.png"));
            m_Button->setIconSize(QSize(125,125));
            break;
        case MemoryCard::SHOWN:  // if shown display numbers
            m_Button->setIcon(QIcon("../memory_figures/figure" +QString::number(N) + ".png"));
            break;
        case MemoryCard::ACTIVE:  // if active display numbers
            m_Button->setIcon(QIcon("../memory_figures/figure" +QString::number(N) + ".png"));
            break;
    }

    //QFont f = font();
    //f.setBold(m_CardMode == MemoryCard::ACTIVE); // set bold font if active
    //setFont(f);

    //QFont fo = font();
    //fo.setUnderline(m_CardMode == MemoryCard::SHOWN);  // set underlined and bold if shown
    //fo.setBold(m_CardMode == MemoryCard::SHOWN);
    //setFont(fo);
}
