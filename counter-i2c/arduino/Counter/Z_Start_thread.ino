// setting all threads on + defining threads order of priority.

#define MONITORING_LED 13

NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(1000);

  pinMode(MONITORING_LED, OUTPUT);

  wdt_enable(WDTO_8S);  //activate the watchdog
  while (TRUE) {
    wdt_reset();//reset avoids automatic reboot
    digitalWrite(MONITORING_LED, HIGH);
    nilThdSleepMilliseconds(100);
    digitalWrite(MONITORING_LED, LOW);
    nilThdSleepMilliseconds(100);
  }
}


NIL_THREADS_TABLE_BEGIN()
// the order should be exact, Acquisition has the higher priority ...


#ifdef THR_SERIAL
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadCounter, NULL, waThreadCounter, sizeof(waThreadCounter))

#ifdef LOGGER
NIL_THREADS_TABLE_ENTRY(NULL, ThreadLogger, NULL, waThreadLogger, sizeof(waThreadLogger))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))


NIL_THREADS_TABLE_END()

