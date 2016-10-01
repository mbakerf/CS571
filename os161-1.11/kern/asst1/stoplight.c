/*
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 *
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>

char * action_to_string(int action);
char * direction_to_string(int direction);

typedef enum {SE=0, SW=1, NE=2, NW=3} Direction;

static struct lock *nw_lock;
static struct lock *ne_lock;
static struct lock *sw_lock;
static struct lock *se_lock;

static count_straight = 0;


/*
 *
 * Constants
 *
 */

/*
 * Number of cars created.
 */

#define NCARS 20


/*
 *
 * Function Definitions
 *
 */


/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber)
{
    count_straight++;
    if(cardirection == NW){
      lock_acquire(sw_lock);
      cardirection = SW;
      kprintf("Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n \
               Entering SW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
      kprintf("Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n", carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
    }
    else if(cardirection == SW){
      lock_acquire(se_lock);
      cardirection = SE;
      kprintf("Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n \
               Entering SE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
      kprintf("Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n", carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
    }
    else if(cardirection == SE){
      lock_acquire(ne_lock);
      cardirection = NE;
      kprintf("Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n \
               Entering NE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
      kprintf("Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n", carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
    }
    else if(cardirection == NE){
      lock_acquire(nw_lock);
      cardirection = NW;
      kprintf("Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Straight\n \
               Entering NW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
      kprintf("Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Straight\n", carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
    }

    count_straight--;

}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber)
{

    count_straight++;

    if(cardirection == NW){
      lock_acquire(sw_lock);
      cardirection = SW;
      kprintf("Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering SW: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
      count_straight--;
      count_straight++;
      lock_acquire(se_lock);
      kprintf("Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering SE: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
      kprintf("Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Left\n", carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
    }
    else if(cardirection == SW){
      lock_acquire(se_lock);
      cardirection = SE;
      kprintf("Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering SE: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
      count_straight--;
      count_straight++;
      lock_acquire(ne_lock);
      kprintf("Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering NE: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
      kprintf("Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Left\n", carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
    }
    else if(cardirection == SE){
      lock_acquire(ne_lock);
      cardirection = NE;
      kprintf("Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering NE: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
      count_straight--;
      count_straight++;
      lock_acquire(nw_lock);
      kprintf("Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering NW: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
      kprintf("Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Left\n", carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
    }
    else if(cardirection == NE){
      lock_acquire(nw_lock);
      cardirection = NW;
      kprintf("Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering NW: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
      lock_acquire(sw_lock);
      kprintf("Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Left\n \
               Entering SW: CarNum=%lu | ApproachDirection=%s | Action=Left\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
      kprintf("Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Left\n", carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
    }

    count_straight--;
}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
          unsigned long carnumber)
{
    if(cardirection == NW){
      kprintf("Entered NW: CarNum=%lu | ApproachDirection=%s | Action=Right\n \
               Leaving NW: CarNum=%lu | ApproachDirection=%s | Action=Right\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(nw_lock);
    }
    else if(cardirection == SW){
      kprintf("Entered SW: CarNum=%lu | ApproachDirection=%s | Action=Right\n \
               Leaving SW: CarNum=%lu | ApproachDirection=%s | Action=Right\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(sw_lock);
    }
    else if(cardirection == SE){
      kprintf("Entered SE: CarNum=%lu | ApproachDirection=%s | Action=Right\n \
               Leaving SE: CarNum=%lu | ApproachDirection=%s | Action=Right\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(se_lock);
    }
    else if(cardirection == NE){
      kprintf("Entered NE: CarNum=%lu | ApproachDirection=%s | Action=Right\n \
               Leaving NE: CarNum=%lu | ApproachDirection=%s | Action=Right\n",
                carnumber, direction_to_string(cardirection), carnumber, direction_to_string(cardirection));
      lock_release(ne_lock);
    }
}


/*
 * approachintersection()
 *
 * Arguments:
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */

static
void
approachintersection(void * unusedpointer,
                     unsigned long carnumber)
{
        int cardirection;
        int caraction;
        /*
         * cardirection and caraction are set randomly.
         */

        cardirection = random() % 4;
        caraction = 1;//random() % 3;

        kprintf("Approaching: CarNum=%lu | ApproachDirection=%s | Action=%s\n", carnumber, direction_to_string(cardirection), action_to_string(caraction));

        int m = splhigh();

        if(cardirection==NW){
          if((caraction == 0 || caraction == 1) && count_straight < 3){
              lock_acquire(nw_lock);
              kprintf("Entered NW: CarNum=%lu | ApproachDirection=%s | Action=%s\n", carnumber, direction_to_string(cardirection), action_to_string(caraction));
            }
        }
        else if(cardirection==NE){
          if((caraction == 0 || caraction == 1) && count_straight < 3){
              lock_acquire(ne_lock);
              kprintf("Entered NE: CarNum=%lu | ApproachDirection=%s | Action=%s\n", carnumber, direction_to_string(cardirection), action_to_string(caraction));
          }
        }
        else if(cardirection==SW){
          if((caraction == 0 || caraction == 1) && count_straight < 3){
            lock_acquire(sw_lock);
            kprintf("Entered SW: CarNum=%lu | ApproachDirection=%s | Action=%s\n", carnumber, direction_to_string(cardirection), action_to_string(caraction));
          }
        }
        else if(cardirection==SE){
          if((caraction == 0 || caraction == 1) && count_straight < 3){
            lock_acquire(se_lock);
            kprintf("Entered SE: CarNum=%lu | ApproachDirection=%s | Action=%s\n", carnumber, direction_to_string(cardirection), action_to_string(caraction));
          }
        }

        splx(m);

        if(caraction == 0){
          gostraight(cardirection, carnumber);
        }
        else if(caraction == 1){
          turnleft(cardirection, carnumber);
        }
        else if(caraction == 2){
          turnright(cardirection, carnumber);
        }
}


char * direction_to_string(int direction){
  if(direction == 0){
      return "SE";
  }
  else if(direction == 1){
    return "SW";
  }
  else if(direction == 2){
    return "NE";
  }
  else if(direction == 3){
    return "NW";
  }
  else{
    return "Something went very wrong....";
  }
}

char * action_to_string(int action){
  if(action == 0){
      return "Straight";
  }
  else if(action == 1){
    return "Left";
  }
  else if(action == 2){
    return "Right";
  }
  else{
    return "Something went very wrong....";
  }
}


/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
           char ** args)
{
        int index, error;

        /*
         * Avoid unused variable warnings.
         */

        (void) nargs;
        (void) args;

        nw_lock = lock_create("NW");
        ne_lock = lock_create("NE");
        sw_lock = lock_create("SW");
        se_lock = lock_create("SE");

        /*
         * Start NCARS approachintersection() threads.
         */

        for (index = 0; index < NCARS; index++) {


            error = thread_fork("approachintersection thread",
                                NULL,
                                index,
                                approachintersection,
                                NULL
                                );

            /*
             * panic() on error.
             */

            if (error) {

                    panic("approachintersection: thread_fork failed: %s\n",
                          strerror(error)
                          );
            }
        }

        return 0;
}
