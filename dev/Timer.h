/* 
 * File:   Timer.h
 * Author: dabraleli
 *
 * Created on 28 Март 2014 г., 11:37
 */

#ifndef TIMER_H
#define	TIMER_H

class Timer
{
    private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;

    public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();
};

#endif	/* TIMER_H */

