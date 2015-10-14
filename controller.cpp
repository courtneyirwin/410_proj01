#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <string>

#include "controller.h"

using namespace std;

int main(int argc, char** argv) {
    if(parse_argv(argc, argv) == false) {
        help_message(argv);
        exit(EXIT_FAILURE);
    }
    else {
        string choice;
        cout << "Controller for process (" << target_pid << ") is running" 
             << endl;

        while(true) {
            print_menu();
            choice = get_input();
            

            if (choice == "d" || choice == "D")
            {
             //double the rate of reporting
              if (interval > MIN_INTERVAL)
              {  
                kill(target_pid, SIGUSR1); 
                interval = interval / 2;
              }
              else
              {
                cout << "Unable to double the report rate. Maximum has been\
                  reached" << endl;
              }
            }


            if (choice == "h" || choice == "H")
            {
            //halve the rate of reporting
              if (interval < MAX_INTERVAL)
              {
                kill(target_pid, SIGUSR2);
                interval = interval * 2;
              }
              else
              {
                cout << "Unable to halve the report rate. Minimum has been\
                  reached" << endl;
              }
            }

            if (choice == "q" || choice == "Q")
            {
              kill(target_pid, SIGKILL);
              exit(0);
            }  
        }
        cout << "Terminating the controller." << endl;
    }
}
