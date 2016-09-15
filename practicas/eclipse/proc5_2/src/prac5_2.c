/*  Test_task
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  $Id: tasks.c,v 1.7.2.1 2000/05/05 12:58:06 joel Exp $
 */

#include <rtems.h>

/* functions */

rtems_task Init(
  rtems_task_argument argument
);

rtems_task Test_task(
  rtems_task_argument argument
);

//Declaracion para poder usarlas
rtems_task ROBOTAvoidObstacles (rtems_task_argument unused);

rtems_task ROBOTAdvanceInPath (rtems_task_argument unused);

rtems_task ROBOTCalculatePath(rtems_task_argument unused);

/* global variables */

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

extern rtems_id   Task_id[ 4 ];         /* array of task ids */
extern rtems_name Task_name[ 4 ];       /* array of task names */

//Declaración del identificador del mutex y del nombre como variable global
rtems_id MutexId;
rtems_name MutexName="MUTEX";

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_INIT
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             4

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_EXTRA_TASK_STACKS         (3 * RTEMS_MINIMUM_STACK_SIZE)


#include <confdefs.h>

/*
 *  Handy macros and static inline functions
 */

/*
 *  Macro to hide the ugliness of printing the time.
 */

#define print_time(_s1, _tb, _s2) \
  do { \
    printf( "%s%02d:%02d:%02d   %02d/%02d/%04d%s", \
       _s1, (_tb)->hour, (_tb)->minute, (_tb)->second, \
       (_tb)->month, (_tb)->day, (_tb)->year, _s2 ); \
    fflush(stdout); \
  } while ( 0 )

/*
 *  Macro to print an task name that is composed of ASCII characters.
 *
 */

#define put_name( _name, _crlf ) \
  do { \
    uint32_t c0, c1, c2, c3; \
    \
    c0 = ((_name) >> 24) & 0xff; \
    c1 = ((_name) >> 16) & 0xff; \
    c2 = ((_name) >> 8) & 0xff; \
    c3 = (_name) & 0xff; \
    putchar( (char)c0 ); \
    if ( c1 ) putchar( (char)c1 ); \
    if ( c2 ) putchar( (char)c2 ); \
    if ( c3 ) putchar( (char)c3 ); \
    if ( (_crlf) ) \
      putchar( '\n' ); \
  } while (0)

/*
 *  static inline routine to make obtaining ticks per second easier.
 */

static inline uint32_t get_ticks_per_second( void )
{
  rtems_interval ticks_per_second;
  (void) rtems_clock_get( RTEMS_CLOCK_GET_TICKS_PER_SECOND, &ticks_per_second );  return ticks_per_second;
}


/*
 *  This allows us to view the "Test_task" instantiations as a set
 *  of numbered tasks by eliminating the number of application
 *  tasks created.
 *
 *  In reality, this is too complex for the purposes of this
 *  example.  It would have been easier to pass a task argument. :)
 *  But it shows how rtems_id's can sometimes be used.
 */

#define task_number( tid ) \
  ( rtems_object_id_get_index( tid ) - \
     rtems_configuration_get_rtems_api_configuration()->number_of_initialization_tasks )


#include <stdio.h>
#include <stdlib.h>

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

rtems_id   Task_id[ 4 ];         /* array of task ids */
rtems_name Task_name[ 4 ];       /* array of task names */

rtems_task Init(rtems_task_argument argument)
{

	/*Para definir un Mutex que usa el protocolo de herencia de prioridad se utiliza la
	siguiente combinación de macros.
	rtems_attribute mutex_attribute = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE | RTEMS_INHERIT_PRIORITY;*/

	/*Para definir un Mutex que usa el protocolo de techo de prioridad se utiliza la
	siguiente combinación de macros.
	rtems_attribute mutex_attribute = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE | RTEMS_PRIORITY_CEILING;*/
  rtems_attribute mutex_attribute =	RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE | RTEMS_INHERIT_PRIORITY;

  /*Rutina que permite crear un semáforo, inicializando la estructura de datos
	asociada. Los parámetros especifican el nombre (name), el valor inicial del
	semáforo (count), usado para definir semáforos contadores, los atributos
	(attribute_set ), que permite definir el tipo de semáforo, la prioridad techo
	(priority_ceiling ), sólo para los semáforos con techo de prioridad, y un puntero
	a una variable (id) a la que RTEMS asigna el identificador del semáforo tras
	invocar la función.*/
  rtems_semaphore_create(MutexName,1,mutex_attribute, RTEMS_NO_PRIORITY, &MutexId);

  rtems_status_code status;
  rtems_time_of_day time;

  puts( "\n\n*** CLOCK TICK TEST ***" );

  time.year   = 1998;
  time.month  = 01;
  time.day    = 01;
  time.hour   = 0;
  time.minute = 0;
  time.second = 0;
  time.ticks  = 0;

  status = rtems_clock_set( &time );

  Task_name[ 1 ] = rtems_build_name( 'T', 'A', '1', ' ' );
  Task_name[ 2 ] = rtems_build_name( 'T', 'A', '2', ' ' );
  Task_name[ 3 ] = rtems_build_name( 'T', 'A', '3', ' ' );

  status = rtems_task_create(
    Task_name[ 1 ], 1, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 1 ]
  );
  status = rtems_task_create(
    Task_name[ 2 ], 2, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 2 ]
  );
  status = rtems_task_create(
    Task_name[ 3 ], 3, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id[ 3 ]
  );

  status = rtems_task_start( Task_id[ 1 ], ROBOTAvoidObstacles, 1 );
  status = rtems_task_start( Task_id[ 2 ], ROBOTCalculatePath, 2 );
  status = rtems_task_start( Task_id[ 3 ], ROBOTAdvanceInPath, 3 );

  status = rtems_task_delete( RTEMS_SELF );
}
#include <stdio.h>

rtems_task Test_task(
  rtems_task_argument unused
)
{
  rtems_id          tid;
  rtems_time_of_day time;
  uint32_t  task_index;
  rtems_status_code status;

  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

  task_index = rtems_get_index(tid)-1;
  for ( ; ; ) {
    status = rtems_clock_get( RTEMS_CLOCK_GET_TOD, &time );
    if ( time.second >= 3335 ) {
      puts( "*** END OF CLOCK TICK TEST ***" );
      exit( 0 );
    }
    put_name( Task_name[ task_index ], FALSE );
    print_time( " - rtems_clock_get - ", &time, "\n" );
    status = rtems_task_wake_after( task_index * 5 * get_ticks_per_second() );
  }
}

rtems_task ROBOTAvoidObstacles (rtems_task_argument unused) {
	//completar.
	rtems_id          tid;
	rtems_time_of_day time;
	uint32_t  task_index;
	rtems_status_code status;

	status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

	task_index = rtems_get_index(tid)-1;
	for ( ; ; ) {
		status = rtems_clock_get( RTEMS_CLOCK_GET_TOD, &time );
		if ( time.second >= 3335 ) {
			puts( "*** END OF CLOCK TICK TEST ***" );
			exit( 0 );
		}
		/*Rutina que permite capturar el semáforo. Los parámetros especifican el
		identificador asignado (id) por rtems_semaphore_create , las opciones de
		captura (option_set) y el intervalo máximo de espera en ticks (timeout)para la
		captura del recurso.
		Las opciones de captura del semáforo son : RTEMS_WAIT | RTEMS_NO_WAIT
		-La tarea se bloquea/no se bloquea hasta la captura	del semáforo.
		Mediante la macro RTEMS_NO_TIMEOUT la espera es indefinida*/
		rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
		leon3_print_string("AvoidObstacles\n");
		/*Rutina que permite liberar el semáforo. El parámetro es el identificador asignado
		(id) por rtems_semaphore_create*/
		rtems_semaphore_release(MutexId);
		//Rutina que permite dormir una tarea durante un número de ticks. La función
		//retorna además el estatus de la operación.
		status = rtems_task_wake_after (2);
	}
}

rtems_task ROBOTAdvanceInPath (rtems_task_argument unused) {
	rtems_id          tid;
	rtems_time_of_day time;
	uint32_t  task_index;
	rtems_status_code status;

	status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

	task_index = rtems_get_index(tid)-1;

	rtems_task_wake_after (3); //Offset inicial

	for ( ; ; ) {
		status = rtems_clock_get( RTEMS_CLOCK_GET_TOD, &time );
		if ( time.second >= 3335 ) {
			puts( "*** END OF CLOCK TICK TEST ***" );
			exit( 0 );
		}
		rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
		leon3_print_string("AdvanceInPath\n");
		rtems_semaphore_release(MutexId);
		//Rutina que permite dormir una tarea durante un número de ticks. La función
		//retorna además el estatus de la operación.
		status = rtems_task_wake_after (4);
	}
}

rtems_task ROBOTCalculatePath(rtems_task_argument unused) {
	rtems_id          tid;
	rtems_time_of_day time;
	uint32_t  task_index;
	rtems_status_code status;

	status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

	task_index = rtems_get_index(tid)-1;

	rtems_task_wake_after (1); //Offset inicial

	for ( ; ; ) {
		status = rtems_clock_get( RTEMS_CLOCK_GET_TOD, &time );
		if ( time.second >= 3335 ) {
			puts( "*** END OF CLOCK TICK TEST ***" );
			exit( 0 );
		}
		rtems_semaphore_obtain(MutexId, RTEMS_WAIT, RTEMS_NO_TIMEOUT);
		leon3_print_string("CalculatePath\n");
		rtems_semaphore_release(MutexId);
		//Rutina que permite dormir una tarea durante un número de ticks. La función
		//retorna además el estatus de la operación.
		status = rtems_task_wake_after (4);
	}
}
