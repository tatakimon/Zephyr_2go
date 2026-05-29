/*
 * Copyright (c) 2026 Antigravity / Google DeepMind
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Size of stack area used by each thread (in bytes) */
#define STACKSIZE 1024

/* Scheduling priority of each thread (lower number = higher priority) */
#define PRIORITY 7

/* Get the GPIO specifications from Devicetree aliases */
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec orange_led = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

/* Thread entry function for the green LED blinker */
void green_led_thread_entry(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    // Verify that the GPIO controller is ready
    if (!gpio_is_ready_dt(&green_led)) {
        printk("Error: Green LED GPIO controller is not ready!\n");
        return;
    }

    // Configure the GPIO pin as output and initialize it to its active state
    int ret = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error configuring Green LED GPIO pin: %d\n", ret);
        return;
    }

    printk("[Thread A] Green LED Blinker Thread started successfully.\n");

    while (1) {
        // Toggle the pin state
        gpio_pin_toggle_dt(&green_led);
        
        // RTOS-aware sleep: yields CPU so other threads (like the orange LED thread) can run
        k_msleep(350); 
    }
}

/* Thread entry function for the orange LED blinker */
void orange_led_thread_entry(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    // Verify that the GPIO controller is ready
    if (!gpio_is_ready_dt(&orange_led)) {
        printk("Error: Orange LED GPIO controller is not ready!\n");
        return;
    }

    // Configure the GPIO pin as output and initialize it to its active state
    int ret = gpio_pin_configure_dt(&orange_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error configuring Orange LED GPIO pin: %d\n", ret);
        return;
    }

    printk("[Thread B] Orange LED Blinker Thread started successfully.\n");

    while (1) {
        // Toggle the pin state
        gpio_pin_toggle_dt(&orange_led);
        
        // RTOS-aware sleep for 800ms
        k_msleep(800); 
    }
}

/* 
 * Define and start the threads statically:
 * K_THREAD_DEFINE(name, stack_size, entry_func, p1, p2, p3, priority, options, delay);
 */
K_THREAD_DEFINE(green_thread_id, STACKSIZE, green_led_thread_entry, NULL, NULL, NULL,
                PRIORITY, 0, 0);

K_THREAD_DEFINE(orange_thread_id, STACKSIZE, orange_led_thread_entry, NULL, NULL, NULL,
                PRIORITY, 0, 0);

/* 
 * The main() function runs in its own default thread.
 * In a Zephyr application, main() is optional, but it's a great place to perform 
 * system initialization or run a primary supervision thread.
 */
int main(void)
{
    printk("\n==================================================\n");
    printk("   STEVAL-STWINBX1 Dual-Blinker Zephyr RTOS Demo  \n");
    printk("==================================================\n");
    printk("The main thread is running and will now go to sleep.\n");
    printk("Watch your green and orange LEDs blink asynchronously!\n\n");

    while (1) {
        k_msleep(5000); // Sleep for 5 seconds and repeat
    }

    return 0;
}
