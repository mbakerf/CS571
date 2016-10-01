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

struct lock dir_to_lock(int dir);

typedef enum {SE=0, SW=1, NE=2, NW=3} Direction;
typedef enum {STRAIGHT, LEFT, RIGHT} Action;

struct lock nw_lock;
struct lock ne_lock;
struct lock sw_lock;
struct lock se_lock;

typedef struct Cars {
  int number;
  Direction approach;
  Direction dest;
  Action action;
} Car;


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

      cardirection = SW;
    }
    else if(cardirection == SW){
      cardirection = SE;
    }
    else if(cardirection == SE){
      cardirection = NE;
    }
    else if(cardirection == NE){
      cardirection = NW;
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
        /*
         * Avoid unused variable warnings.
         */

        (void) cardirection;
        (void) carnumber;
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
        /*
         * Avoid unused variable warnings.
         */

        (void) cardirection;
        (void) carnumber;
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
approachintersection(Car * car,
                     unsigned long carnumber)
{
        int cardirection;


        /*
         * cardirection is set randomly.
         */

        cardirection = random() % 4;

        lock_acquire(dir_to_lock(cardirection));

        if(car->action == STRAIGHT){
          gostraight(cardirection, car->approach);
        }
        else if(car->action == LEFT){
          turnleft(cardirection, car->approach);
        }
        else if(car->action == RIGHT){
          turnright(cardirection, car->approach);
        }
}


struct lock
dir_to_lock(int dir){
  if(dir==NW){
    return nw_lock;
  }
  else if(dir==NE){
    return ne_lock;
  }
  else if(dir==SW){
    return sw_lock;
  }
  else if(dir==SE){
    return se_lock;
  }
  else{
    return -1;
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

            Car car;
            car.number = index;
            car.approach = NW;
            car.action = STRAIGHT;


            error = thread_fork("approachintersection thread",
                                &car,
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
