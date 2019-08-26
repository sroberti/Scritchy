#ifndef TOUCHSCREEN_HH
#define TOUCHSCREEN_HH

#include <sys/time.h>
#include <vector>
#include <functional>




class PenState
//Store most recent state of all input parameters
//and allow asynchronous updates.
{
public:
  //Return the most recent values for relevant components of pen's state.
  //Throws exception if called while state is not synchronous.
  int getX() const;
  int getY() const;
  int getPressure() const;
  bool getButton() const;
  bool getEraser() const;

  //Register a callback function to execute when an update is complete.
  void registerCallback(std::function<void() > _callback);


private:
  //Timestamp of most recent partial update.
  timeval timestamp;

  //Most recent values for X and Y coordinates.
  int x;
  int y;

  //True if coordinate has been updated since last completed update.
  bool x_updated, y_updated;
  //Pen pressure.
  unsigned int pressure;

  //True if the pen tip or eraser is contacting the screen.
  bool touch;
  //True if the side button is pressed.
  bool button;
  //True if the eraser is near the screen.
  bool eraser;

  //Functions to be executed when an update is completed.
  std::vector<std::function<void()>> callbacks;

  //Handle a complete update.
  void onCompleteUpdate();

  //Handle pen lifting off of screen.
  void onPenLift();

  //Check if both x and y coordinates are new.
  bool isComplete() const;


};


#endif
