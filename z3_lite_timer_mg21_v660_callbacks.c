/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"
#include "../../platform/emlib/inc/em_cmu.h"
#include "../../platform/emlib/inc/em_timer.h"

#include EMBER_AF_API_NETWORK_CREATOR
#include EMBER_AF_API_NETWORK_CREATOR_SECURITY
#include EMBER_AF_API_NETWORK_STEERING
#include EMBER_AF_API_FIND_AND_BIND_TARGET
#include EMBER_AF_API_ZLL_PROFILE

#define LIGHT_ENDPOINT (1)

EmberEventControl commissioningLedEventControl;
EmberEventControl findingAndBindingEventControl;

void commissioningLedEventHandler(void)
{
  emberEventControlSetInactive(commissioningLedEventControl);

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
    uint16_t identifyTime;
    emberAfReadServerAttribute(LIGHT_ENDPOINT,
                               ZCL_IDENTIFY_CLUSTER_ID,
                               ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                               (uint8_t *)&identifyTime,
                               sizeof(identifyTime));
    if (identifyTime > 0) {
      halToggleLed(COMMISSIONING_STATUS_LED);
      emberEventControlSetDelayMS(commissioningLedEventControl,
                                  LED_BLINK_PERIOD_MS << 1);
    } else {
      halSetLed(COMMISSIONING_STATUS_LED);
    }
  } else {
    EmberStatus status = emberAfPluginNetworkSteeringStart();
    emberAfCorePrintln("%p network %p: 0x%X", "Join", "start", status);
  }
}

void findingAndBindingEventHandler()
{
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
    emberEventControlSetInactive(findingAndBindingEventControl);
    emberAfCorePrintln("Find and bind target start: 0x%X",
                       emberAfPluginFindAndBindTargetStart(LIGHT_ENDPOINT));
  }
}

/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be notified
 * of changes to the stack status and take appropriate action.  The return code
 * from this callback is ignored by the framework.  The framework will always
 * process the stack status after the callback returns.
 *
 * @param status   Ver.: always
 */
bool emberAfStackStatusCallback(EmberStatus status)
{
  // Note, the ZLL state is automatically updated by the stack and the plugin.
  if (status == EMBER_NETWORK_DOWN) {
    halClearLed(COMMISSIONING_STATUS_LED);
  } else if (status == EMBER_NETWORK_UP) {
    halSetLed(COMMISSIONING_STATUS_LED);
    emberEventControlSetActive(findingAndBindingEventControl);
  }

// This value is ignored by the framework.
  return false;
}

/** @brief Main Init
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup.
 * Any code that you would normally put into the top of the application's
 * main() routine should be put into this function.
        Note: No callback
 * in the Application Framework is associated with resource cleanup. If you
 * are implementing your application on a Unix host where resource cleanup is
 * a consideration, we expect that you will use the standard Posix system
 * calls, including the use of atexit() and handlers for signals such as
 * SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If you use the signal()
 * function to register your signal handler, please mind the returned value
 * which may be an Application Framework function. If the return value is
 * non-null, please make sure that you call the returned function from your
 * handler to avoid negating the resource cleanup of the Application Framework
 * itself.
 *
 */
void emberAfMainInitCallback(void)
{
  emberEventControlSetActive(commissioningLedEventControl);
}

/** @brief Complete
 *
 * This callback is fired when the Network Steering plugin is complete.
 *
 * @param status On success this will be set to EMBER_SUCCESS to indicate a
 * network was joined successfully. On failure this will be the status code of
 * the last join or scan attempt. Ver.: always
 * @param totalBeacons The total number of 802.15.4 beacons that were heard,
 * including beacons from different devices with the same PAN ID. Ver.: always
 * @param joinAttempts The number of join attempts that were made to get onto
 * an open Zigbee network. Ver.: always
 * @param finalState The finishing state of the network steering process. From
 * this, one is able to tell on which channel mask and with which key the
 * process was complete. Ver.: always
 */
void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState)
{
  emberAfCorePrintln("%p network %p: 0x%X", "Join", "complete", status);

  if (status != EMBER_SUCCESS) {
    // Initialize our ZLL security now so that we are ready to be a touchlink
    // target at any point.
    status = emberAfZllSetInitialSecurityState();
    if (status != EMBER_SUCCESS) {
      emberAfCorePrintln("Error: cannot initialize ZLL security: 0x%X", status);
    }

    status = emberAfPluginNetworkCreatorStart(false); // distributed
    emberAfCorePrintln("%p network %p: 0x%X", "Form", "start", status);
  }
}

/** @brief Complete
 *
 * This callback notifies the user that the network creation process has
 * completed successfully.
 *
 * @param network The network that the network creator plugin successfully
 * formed. Ver.: always
 * @param usedSecondaryChannels Whether or not the network creator wants to
 * form a network on the secondary channels Ver.: always
 */
void emberAfPluginNetworkCreatorCompleteCallback(const EmberNetworkParameters *network,
                                                 bool usedSecondaryChannels)
{
  emberAfCorePrintln("%p network %p: 0x%X",
                     "Form distributed",
                     "complete",
                     EMBER_SUCCESS);
}

/** @brief On/off Cluster Server Post Init
 *
 * Following resolution of the On/Off state at startup for this endpoint, perform any
 * additional initialization needed; e.g., synchronize hardware state.
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPluginOnOffClusterServerPostInitCallback(uint8_t endpoint)
{
  // At startup, trigger a read of the attribute and possibly a toggle of the
  // LED to make sure they are always in sync.
  emberAfOnOffClusterServerAttributeChangedCallback(endpoint,
                                                    ZCL_ON_OFF_ATTRIBUTE_ID);
}

/** @brief Server Attribute Changed
 *
 * On/off cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffClusterServerAttributeChangedCallback(uint8_t endpoint,
                                                       EmberAfAttributeId attributeId)
{
  // When the on/off attribute changes, set the LED appropriately.  If an error
  // occurs, ignore it because there's really nothing we can do.
  if (attributeId == ZCL_ON_OFF_ATTRIBUTE_ID) {
    bool onOff;
    if (emberAfReadServerAttribute(endpoint,
                                   ZCL_ON_OFF_CLUSTER_ID,
                                   ZCL_ON_OFF_ATTRIBUTE_ID,
                                   (uint8_t *)&onOff,
                                   sizeof(onOff))
        == EMBER_ZCL_STATUS_SUCCESS) {
      if (onOff) {
        halSetLed(ON_OFF_LIGHT_LED);
      } else {
        halClearLed(ON_OFF_LIGHT_LED);
      }
    }
  }
}

/** @brief Hal Button Isr
 *
 * This callback is called by the framework whenever a button is pressed on the
 * device. This callback is called within ISR context.
 *
 * @param button The button which has changed state, either BUTTON0 or BUTTON1
 * as defined in the appropriate BOARD_HEADER.  Ver.: always
 * @param state The new state of the button referenced by the button parameter,
 * either ::BUTTON_PRESSED if the button has been pressed or ::BUTTON_RELEASED
 * if the button has been released.  Ver.: always
 */
void emberAfHalButtonIsrCallback(uint8_t button, uint8_t state)
{
  if (state == BUTTON_RELEASED) {
    emberEventControlSetActive(findingAndBindingEventControl);
  }
}


#define TIMER0_INIT                                                            \
  {                                                                                   \
    true,                 /* Enable timer when initialization completes. */           \
    false,                /* Stop counter during debug halt. */                       \
    timerPrescale1024,       /* No prescaling. */                                        \
    timerClkSelHFPerClk,  /* Select HFPER / HFPERB clock. */                          \
    false,                /* Not 2x count mode. */                                    \
    false,                /* No ATI. */                                               \
    timerInputActionNone, /* No action on falling input edge. */                      \
    timerInputActionNone, /* No action on rising input edge. */                       \
    timerModeUp,          /* Up-counting. */                                          \
    false,                /* Do not clear DMA requests when DMA channel is active. */ \
    false,                /* Select X2 quadrature decode mode (if used). */           \
    false,                /* Disable one shot. */                                     \
    false                 /* Not started/stopped/reloaded by other timers. */         \
  }

#define TIMER0_INITCC                                                      \
  {                                                                          \
    timerEventEveryEdge,    /* Event on every capture. */                    \
    timerEdgeRising,        /* Input capture edge on rising edge. */         \
    0,                      /* Not used by default, select PRS channel 0. */ \
    timerOutputActionNone,  /* No action on underflow. */                    \
    timerOutputActionNone,  /* No action on overflow. */                     \
    timerOutputActionToggle,  /* No action on match. */                        \
    timerCCModeCompare,         /* Enable compare/capture channel. */           \
    false,                  /* Disable filter. */                            \
    false,                  /* No PRS input. */                              \
    false,                  /* Clear output when counter disabled. */        \
    false,                  /* Do not invert output. */                      \
    timerPrsOutputDefault,  /* Use default PRS output configuration. */      \
    timerPrsInputNone       /* No PRS input, so input type is none. */       \
  }


#define TIMER_CLK         cmuClock_TIMER0

 uint32_t freq;
static uint32_t minTicks;
extern  bool timeElapsed;


Ecode_t one_second_timer_Init(void)
{
  TIMER_Init_TypeDef timerInit     = TIMER0_INIT;
  TIMER_InitCC_TypeDef timerCCInit = TIMER0_INITCC;
  uint32_t coreClockScale;
  
  
  timerInit.prescale = timerPrescale8;
  timerInit.enable = false;


  // configure, but do not start timer
  TIMER_Init(TIMER0, &timerInit);

  // Route Timer0 CC0 output to PA6
  GPIO->TIMERROUTE[0].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN;
  GPIO->TIMERROUTE[0].CC0ROUTE = (gpioPortC << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT)
						| (0 << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
  
  GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);
  
  timerCCInit.mode = timerCCModeCompare;
  timerCCInit.cmoa = timerOutputActionToggle;

  TIMER_InitCC(TIMER0, 0, &timerCCInit);

  

 
  freq = CMU_ClockFreqGet(cmuClock_TIMER0)/(timerInit.prescale + 1);
  
  int topValue = freq/2000 - 1;
  
  
  TIMER_TopSet(TIMER0,topValue);
  

  
  TIMER_Enable(TIMER0, true);
  


  /* Run timer at slowest frequency that still gives less than 1 us per tick */
  
 /*
#if defined (_TIMER_CTRL_PRESC_DIV1)
  timerInit.prescale = (TIMER_Prescale_TypeDef)_TIMER_CTRL_PRESC_DIV1;
#endif

#if defined (_TIMER_CFG_PRESC_DIV1)
  timerInit.prescale = (TIMER_Prescale_TypeDef)_TIMER_CFG_PRESC_DIV1;
#endif

  do {
    TIMER_Init(TIMER0, &timerInit);

#if defined(_CMU_HFPERCLKEN0_MASK)
    freq = CMU_ClockFreqGet(cmuClock_HFPER);
#else
    freq = CMU_ClockFreqGet(cmuClock_EM01GRPACLK);
#endif
   
    
#if defined (_TIMER_CFG_PRESC_DIV1)
    freq /= (timerInit.prescale + 1);
#endif
#if defined (_TIMER_CTRL_PRESC_DIV1)
    freq /= 1 << timerInit.prescale;
#endif
    timerInit.prescale++;
  } while ( (timerInit.prescale <= timerPrescale1024)
            && (freq > 2000000) );

   emberAfCorePrintln("frequence:%d",freq);
*/



  return 0;
}




void output_clock()
{
  uint64_t ticks;
  uint32_t cmp;
  

//    CMU_ClkOutPinConfig(0,cmuSelect_EXPCLK,32,gpioPortC,0);
  

  one_second_timer_Init();
  


  
     TIMER_IntDisable(TIMER0, TIMER_IEN_CC0);
  
  NVIC_ClearPendingIRQ(TIMER0_IRQn);
  
  NVIC_EnableIRQ(TIMER0_IRQn);
     
     
    while(!timeElapsed){
       halResetWatchdog();
     }
     
 
}
  

EmberCommandEntry emberAfCustomCommands[] = {
  /* Sample Custom CLI commands */
  // emberCommandEntrySubMenu("sub-menu", customSubMenu, "Sub menu of custom commands"),
  // emberCommandEntryAction("action", actionFunction, "", "Description of action command."),
  emberCommandEntryAction("oc", output_clock, "",  "output clock."),
  emberCommandEntryTerminator()
};





