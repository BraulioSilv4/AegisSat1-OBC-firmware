/**
 * Example of a Queue for inter task communication in RTOS.
 */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#define STACK_SIZE (configMINIMAL_STACK_SIZE + 500)
#define QUEUE_SIZE 10

QueueHandle_t xQueue = NULL;

typedef struct QueueMessage {
    char message[100];
    int msg_id; 
} QueueMessage;

void task_A(void * pvParameter) {
    QueueMessage msg = {.message = "Hello from task A\n", .msg_id = 1};
	TickType_t xLastWakeUpTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(1000);

	xLastWakeUpTime = xTaskGetTickCount();
	while(true) {
		xTaskDelayUntil(&xLastWakeUpTime, xFrequency);
			
		if(xQueueSend(xQueue, &msg, (TickType_t) 0)) {
			msg.msg_id++;
		};
	}
}

void task_B(void * pvParams) {
	QueueMessage msg_received;

	while(true) {
		if(xQueueReceive(xQueue, &msg_received, (TickType_t) pdMS_TO_TICKS(500))) {
			printf("Message Content: %s\nMessage id: %i\n\n", 
				msg_received.message,
				msg_received.msg_id
			);
		}
	}
}

void app_main(void) {
	xQueue = xQueueCreate(QUEUE_SIZE, sizeof(QueueMessage));

	xTaskCreate(
		task_A,
		"task_A",
		STACK_SIZE,
		NULL,
		1,
		NULL
	);


	xTaskCreate(
		task_B,
		"task_B",
		STACK_SIZE,
		NULL,
		1,
		NULL
	);
}