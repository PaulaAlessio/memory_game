//
// Created by hifly_admin on 12/28/21.
//

#pragma once

#include <QTimer>

class MemoryTimer : public QTimer { // subclass of QTimer that has useful slots :))

Q_OBJECT

private:
  int simulation = 0;

public slots:
    void countup();  // slot that increments timer of player 1
    void setTimer(int);
  //  void countup2();  // slot that increments timer of player 2
 //   void stop1f();  // slot that stops timer of player 1
 //   void stop2f();  // slot that stops timer of player 2
 //   void start1f();  // slot that starts timer of player 1
 //   void start2f();  // slot that starts timer of player 2
    void startf();
//    void prevf();  // slot for previous button
//    void nextf();  // slot for next button

signals:
    void updateTimer(int);  // updates timer

};