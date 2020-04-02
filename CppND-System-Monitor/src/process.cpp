#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h" 

using std::string;
using std::to_string;
using std::vector;
using std::istream_iterator;
using std::stoi;

Process::Process(int pid) : pid_(pid), cpu_util_(Process::CpuUtilization()){};

// TODO: Return this process's ID
int Process::Pid()const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization () { 
  string line, key, value, pidPath = to_string(Pid());
  long sysUpTime = LinuxParser::UpTime();
  float time = 0, seconds, cpuUtil;


  std::ifstream stream(LinuxParser::kProcDirectory + pidPath+ LinuxParser::kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      istream_iterator<string> start(linestream), end;
      vector<string> v (start, end);

      for (int i=13;i<=16;i++)
        time += stoi(v[i]); //sum of pid time clicks
      
      seconds = sysUpTime - (stoi(v[21]) / sysconf(_SC_CLK_TCK) ); //System uptime - start time click  
      cpuUtil = ((time/ sysconf(_SC_CLK_TCK)) / seconds );

    }
  }  
  
  return cpuUtil;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return (cpu_util_ > a.cpu_util_ );
 }