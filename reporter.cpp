#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>

#include "reporter.h"

using namespace std;


/*
 * name:    sigint_handler
 * purpose: handle the SIGINT signal
 * receive: none
 * return:  none
 */
void sigint_handler(int signo)
{
  if (signo == SIGINT)
  {
    alarm(0);
    //ask user for confirmation
    if (confirm_exit())
    {
      cout << "Program terminates" << endl;
      exit (0);
    }
    else 
    {
      cout << "Program continues" << endl;
      if (interval >=  1){
      alarm(interval);
     }
   else{
      ualarm(interval * 1000000, 0);
    }
    }
  }
}

/*
 * name:    sigusr1_handler
 * purpose: handle the SIGUSR1 signal
 * receive: none
 * return:  none
 */
void sigusr1_handler(int signo)
{
  if (signo == SIGUSR1)
  {
    alarm(0);
    interval = interval / 2;
    if (interval >=  1){
      alarm(interval);
    }
   else{
      ualarm(interval * 1000000, 0);
    }
   print_mem_report();
  
  }
}

/*
 * name:    sigusr2_handler
 * purpose: handle the SIGUSR2 signal
 * receive: none
 * return:  none
 */
void sigusr2_handler(int signo)
{
  if (signo == SIGUSR2)
  {
    alarm(0);
    interval = interval * 2;
     if (interval >=  1){

      alarm(interval);
    }
   else{
      ualarm(interval * 1000000, 0);
    }
   print_mem_report();
  }
  
}

/*
 * name:    sigusr2_handler
 * purpose: handle the SIGUSR2 signal
 * receive: none
 * return:  none
 */
void alarm_handler(int signo)
{
  if (signo == SIGALRM)
  {
    print_mem_report();
    if (interval >=  1){
      alarm(interval);
    }
   else{
      ualarm(interval * 1000000, 0);
    }
  }
  
}

int main(int argc, char** argv) {
  interval = 1; // in seconds
  // Give PID and basic information
  cout << "The reporter program's PID is " << getpid() << endl;
  cout << "The default report interval is " << interval << endl;


  struct sigaction s1;
  s1.sa_handler = sigusr1_handler;

  struct sigaction s2;
  s2.sa_handler = sigusr2_handler;

  struct sigaction sa;
  sa.sa_handler = alarm_handler;


  if (sigaction(SIGALRM, &sa, NULL) == -1)
  {
    cout << "failed to register alarm handler" << endl;
    exit(EXIT_FAILURE);
  }

  if (sigaction(SIGUSR1, &s1, NULL) == -1)
  {
    cout << "failed to register user1 handler" << endl;
    exit(EXIT_FAILURE);
  }

  if (sigaction(SIGUSR2, &s2, NULL) == -1)
  {
    cout << "failed to register user2 handler" << endl;
    exit(EXIT_FAILURE);
  }

  signal(SIGINT, sigint_handler);
   if (interval >=  1){

      alarm(interval);
    }
   else{
      ualarm(interval * 1000000, 0);
    }

   while(1){
     sleep(3);
   }
}
