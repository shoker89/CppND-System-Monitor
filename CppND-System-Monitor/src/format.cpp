 #include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  string totTime, HH, MM,SS;
  long time = seconds;
  HH = to_string(time / 3600);
  time = time % 3600;
  MM = to_string(time /60);
  time = time % 60 ;
  SS = to_string(time);
  
  return string(HH + ":" + MM + ":" + SS); 
}