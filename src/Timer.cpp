#include "../headers/Timer.h"

Timer::Timer(unsigned int c) : clock(c) {}

void Timer::reset() { clock = 0; }
void Timer::set(unsigned int c) { clock = c; }
void Timer::advance() { clock += 1; }
void Timer::add(int time) { clock += time; }
unsigned int Timer::get() { return clock; }



