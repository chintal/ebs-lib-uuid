
#include "application.h"
#include "application_descriptors.h"
#include "bsp/hal/uc.h"
#include "bsp/drivers/led/led.h"
#include "sys/sys.h"

#include "sys/modbus/modbus.h"
#include "test_uuid.h"


static void deferred_exec(void);

static void deferred_exec(void){
    #if APP_ENABLE_MODBUS == 1
        modbus_state_machine();
    #endif
}


static void _initialize_interrupts(void);

static void _initialize_interrupts(void){
    // Needed to ensure linker includes interrupt handlers 
    // in the output.
    __uart_handler_inclusion = 1;
    __usb_handler_inclusion = 1;
    __timer_handler_inclusion = 1;
}


int main(void)
{   
    // Pre-init, and assoicated Housekeeping
    _initialize_interrupts();
    
    led_init(BOARD_GREEN_LED_SELECTOR);
    led_init(BOARD_RED_LED_SELECTOR);
    led_on(BOARD_RED_LED_SELECTOR);
    led_off(BOARD_GREEN_LED_SELECTOR);
    
    // uC Core Initialization
    watchdog_hold();
    power_set_full();

    clock_set_default();
    global_interrupt_enable();
    
    usb_init();
    id_init();
    application_descriptors_init();
    
    // Subsystems Initialization
    #if APP_ENABLE_BCIF == 1
        bc_init();
    #endif
    
    ucdm_init();
    app_tm_init(DMAP_TIME_BASE_ADDRESS);
    
    #if APP_ENABLE_MODBUS == 1
        modbus_init(DMAP_MODBUS_BASE_ADDRESS, MODBUS_DEFAULT_DEVICE_ADDRESS);
        led_off(BOARD_RED_LED_SELECTOR);
        led_on(BOARD_GREEN_LED_SELECTOR);
    #endif
    
    uuid_test_init();
    
    while(1){
        deferred_exec();
    }
    return(0);
}
