/** @file hal/host/micro-common.h
 * See @ref host and micro specific modules for documentation.
 *
 * <!-- Copyright 2010 by Ember Corporation. All rights reserved.        *80*-->
 */

/** @addtogroup host
 * @brief HAL functions common across all microcontroller-specific files.
 * 
 * @note The micro specific definitions, @ref stm32f103ret_host, is
 * chosen by the build include path pointing at the appropriate directoy.
 *
 * See micro-common.h for source code.
 *@{
 */

#ifndef __MICRO_COMMON_H__
#define __MICRO_COMMON_H__


/** @brief Initializes microcontroller-specific peripherals.
*/
void halInit(void);

/** @brief Restarts the microcontroller.
*/
void halReboot(void);

/** @brief Powers up microcontroller peripherals.
*/
void halPowerUp(void);

/** @brief Powers down microcontroller peripherals.
*/
void halPowerDown(void);

/** @brief The value that must be passed as the single parameter to 
 *  ::halInternalDisableWatchDog() in order to sucessfully disable the watchdog 
 *  timer.
 */ 
#define MICRO_DISABLE_WATCH_DOG_KEY 0xA5

/** @brief Enables the watchdog timer, if there is one and it is reasonable
 * to be enabled.
 */
void halInternalEnableWatchDog(void);

/** @brief Disables the watchdog timer, if there is one  and it can be
 * disabled.
 *
 * @note To prevent the watchdog from being disabled accidentally, 
 * a magic key must be provided.
 * 
 * @param magicKey  A value (::MICRO_DISABLE_WATCH_DOG_KEY) that enables
 * the function.
 */
void halInternalDisableWatchDog(int8u magicKey);

/** @brief Blocks the current thread of execution for the specified
 * amount of time, in microseconds.
 *
 * The function is implemented with either cycle-counted busy loops or
 * a convenient timer.  It is intended to create the short blocking delays
 * such as when interfacing with hardware peripherals.
 *
 * The accuracy of the timing provided by this function is not specified,
 * but a best faith effort is obtain an accurate delay.  The implementation
 * may be changed, but this function should be reasonably accurate.
 *
 * @param us  The specified time, in microseconds.  Values should be
 * between 1 and 65535 microseconds.
 */
void halCommonDelayMicroseconds(int16u us);

/** @brief Blocks the current thread of execution for the specified
 * amount of time, in milliseconds..
 *
 * This function depends on halCommonDelayMicroseconds().
 *
 * @param ms  The specified time, in milliseconds. 
 */
void halCommonDelayMilliseconds(int16u ms);

/** @brief Called implicitly through the standard C language assert() macro. 
 * An implementation where notification is, for instance, sent over the
 * serial port can provide meaningful and useful debugging information. 
 * 
 * @note Liberal usage of assert() consumes flash space.
 * 
 * @param filename   Name of the file throwing the assert.
 * 
 * @param linenumber Line number that threw the assert.
 */
void halInternalAssertFailed(PGM_P filename, int linenumber);

/** @brief Gets information about what caused the microcontroller to reset. 
 *
 * @return A code identifying the cause of the reset.
 */
int8u halGetResetInfo(void);

/** @brief Calls ::halGetResetInfo() and supplies a string describing it.
 *
 * @return A pointer to a program space string.
 */
PGM_P halGetResetString(void);

/** @brief Seeds the ::halCommonGetRandom() pseudorandom number
 * generator.
 *
 * @param seed  A seed for the pseudorandom number generator.
 */
void halStackSeedRandom(int32u seed);

/** @brief Generate pseudorandom numbers.  Implementation is host specific.
 */
int16u halCommonGetRandom(void);


#ifdef DOXYGEN_SHOULD_SKIP_THIS
/** @brief Enumerations for the possible microcontroller sleep modes.
 *
 * NOTE: Refer to a specific micro's implementation of halSleep()
 *       to see what modes are actually supported.
 * 
 * - SLEEPMODE_RUNNING
 *     Everything is active and running.  In practice this mode is not
 *     used, but it is defined for completeness of information.
 *
 * - SLEEPMODE_IDLE
 *     Only the CPU is idled.  The rest of the chip continues runing
 *     normally.  The chip will wake from any interrupt.
 *
 * - SLEEPMODE_WAKETIMER
 *     The sleep timer clock sources remain running.  The RC is always
 *     running and the 32kHz XTAL depends on system timer config.  Wakeup
 *     is possible from both GPIO and the sleep timer.  System time
 *     is maintained.  The sleep timer is assumed to be configured
 *     properly for wake events.
 *
 * - SLEEPMODE_MAINTAINTIMER
 *     The sleep timer clock sources remain running.  The RC is always
 *     running and the 32kHz XTAL depends on the board header.  Wakeup
 *     is possible from only GPIO.  System time is maintained.
 *
 * - SLEEPMODE_NOTIMER
 *     The sleep timer clock sources (both RC and XTAL) are turned off.
 *     Wakeup is possible from only GPIO.  System time is lost.
 *
 * - SLEEPMODE_RESERVED
 *     Reserved/Unused
 * - SLEEPMODE_POWERDOWN
 *     Deprecated
 * - SLEEPMODE_POWERSAVE
 *     Deprecated
 */
enum SleepModes
#else
typedef int8u SleepModes;
enum
#endif
{
  SLEEPMODE_RUNNING = 0,
  SLEEPMODE_IDLE = 1,
  SLEEPMODE_WAKETIMER = 2,
  SLEEPMODE_MAINTAINTIMER = 3,
  SLEEPMODE_NOTIMER = 4,
  
  //The following SleepModes are deprecated.  Each micro's halSleep()
  //function will remap these modes to the appropriate replacement, as
  //necessary.
  SLEEPMODE_RESERVED = 6,
  SLEEPMODE_POWERDOWN = 7,
  SLEEPMODE_POWERSAVE = 8,
};

/** @brief Puts the microcontroller to sleep in a specified mode.
 * 
 * @note This routine always enables interrupts.
 *
 * @param sleepMode  A microcontroller sleep mode 
 */
void halSleep(SleepModes sleepMode);


//Pull in the micro specific micro definitions.  The specific header is chosen
//by the build include path pointing at the appropriate directory.
#include "micro-specific.h"


#endif //__MICRO_COMMON_H__


/**@} //END addtogroup 
 */

