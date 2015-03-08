/*  In alarm.c, the first function, ding, simulates an alarm clock.  */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int alarm_fired = 0;

void ding(int sig)
{
    alarm_fired = 1;
}

/*  In main, we tell the child process to wait for five seconds
    before sending a SIGALRM signal to its parent.  */

int main()
{
    int pid;

    printf("alarm application starting\n");

    if((pid = fork()) == 0) {
    printf("%d",getppid());
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(0);
    }

/*  The parent process arranges to catch SIGALRM with a call to signal
    and then waits for the inevitable.  */

    printf("waiting for alarm to go off\n");
    (void) signal(SIGALRM, ding);

    pause();
    if (alarm_fired)
        printf("Ding!\n");

    printf("done\n");
    exit(0);
}
