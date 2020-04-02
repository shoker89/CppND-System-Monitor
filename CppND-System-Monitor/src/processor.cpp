#include "processor.h"
#include "linux_parser.h"
#include <iostream>
using std::vector;
using std::string;
using std::stof;

// TODO: Return the aggregate CPU utilization
//Cpu = active / total
float Processor::Utilization() { 
  vector<string> jiffiesList = LinuxParser::CpuUtilization();
  float active=0, idle =0, cpuUtil=0, total, prevTotal, diffTotal, diffIdle;
  for (int i=0; i<9; i++){
    if (i==3 || i== 4)
      idle += stof(jiffiesList[i]);
    else
      active += stof(jiffiesList[i]);
  }

  total = idle + active;  
  prevTotal = prevIdle + prevActive;
  diffTotal = total - prevTotal;
  diffIdle = idle - prevIdle;

  cpuUtil = (diffTotal - diffIdle) / diffTotal;

  prevActive = active;
  prevIdle = idle;

  return cpuUtil;
}