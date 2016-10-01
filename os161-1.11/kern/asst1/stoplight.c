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

typedef enum {SE=0, SW=1, NE=2, NW=3} Direction;

static struct lock *nw_lock;
static struct lock *ne_lock;
static struct lock *sw_lock;
static struct lock *se_lock;


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

    if(cardirection == NW){
      lock_acquire(sw_lock);
      cardirection = SW;
      lock_release(nw_lock);
    }
    else if(cardirection == SW){
      lock_acquire(se_lock);
      cardirection = SE;
      lock_release(sw_lock);
    }
    else if(cardirection == SE){
      lock_acquire(ne_lock);
      cardirection = NE;
      lock_release(se_lock);
    }
    else if(cardirection == NE){
      lock_acquire(nw_lock);
      cardirection = NW;
      lock_release(ne_lock);
    }

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
    if(cardirection == NW){
      gostraight(cardirection, carnumber);
      gostraight(SW, carnumber);
    }
    else if(cardirection == SW){
      gostraight(cardirection, carnumber);
      gostraight(SE, carnumber);
    }
    else if(cardirection == SE){
      gostraight(cardirection, carnumber);
      gostraight(NE, carnumber);
    }
    else if(cardirection == NE){
      gostraight(cardirection, carnumber);
      gostraight(NW, carnumber);
    }
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
      lock_release(nw_lock);
    }
    else if(cardirection == SW){
      lock_release(sw_lock);
    }
    else if(cardirection == SE){
      lock_release(se_lock);
    }
    else if(cardirection == NE){
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
        caraction = random() % 3;

        kprintf("CarNum=%ul | ApproachDirection=%d", carnumber, cardirection);

        if(cardirection==NW){
          lock_acquire(nw_lock);
        }
        else if(cardirection==NE){
          lock_acquire(ne_lock);
        }
        else if(cardirection==SW){
          lock_acquire(sw_lock);
        }
        else if(cardirection==SE){
          lock_acquire(se_lock);
        }

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
