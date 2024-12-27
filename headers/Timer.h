#ifndef INCLUDE_HEADERS_TIMER_H_
#define INCLUDE_HEADERS_TIMER_H_

/*class Timer {
public:
  Timer(unsigned int clock = 0);

  void reset();
  void set(unsigned int clock);
  void advance();
  void add(int time);
  unsigned int get();

private:
  unsigned int clock;
};
*/

class Timer {
private:
  unsigned int startTime;

public:
  Timer(unsigned int startTime);
  unsigned int getStartTime() const;
};

#endif // INCLUDE_HEADERS_TIMER_H_
