/*
 *  ECE- 315 WINTER 2021 - COMPUTER INTERFACING COURSE
 *
 *  Created on	: 	15 July, 2021
 *  Author		: 	Shyama M. Gandhi, Mazen Elbaz
 *
 * -----------------------------------------------------------------------------------------------------
 * IMPLEMENTATION OF A SIMPLE CALCULATOR.
 * Inputs Operands from the keypad
 * Output of the arithmetic operation is displayed on the Console
 * This exercise of the lab does not use SSD!!!
 * Operations available : +, -, * and palindrome, selected using the keys A, B, C and D, respectively.
 *
 * The design of this exercise is as follows:
 * Say, you wish to calculate (978 X 4050)
 * So, you enter 9, press 7, press 8 and then F so that the operand will be registered. Do the same for second operand of 4050.
 * In case while entering the operand, if you commit any error, you can press 'E' key any time to enter the operand again.
 * Once you have entered two operands, press any key from A, B, C or D to choose the corresponding operation.
 * So, the sequence of inputs you entered is, enter one operand, enter second operand and then enter the operation using the (A/B/C/D) key.
 * The calculator is designed in a way that you enter the operands first and then select the operation as a third value to the Queue.
 * The corresponding output will be displayed on the console.
 * 32-bit variables are used to store the input as well as output and overflow will generate a wrong output. You must detect the overflow condition for +, - and * operation.
 *
 * For subtraction, you may use store_operands[1]-store_operands[0] or vice versa.
 * For palindrome, two operands are taken as an input. Four results are possible: both operands are palindrome, operand 1 is palindrome but operand 2 is not. Operand 2 is palindrome but
 * operand 1 is not. Both operands are non-palindrome numbers. For any case, display the result on the console. However, for the case when both the operands are palindrome,
 * a White light on RGB led must glow for 1.5 seconds.
 * The initialization and required definitions for RGB led GPIO has been provided as you read along the template.
 * -----------------------------------------------------------------------------------------------------
 *
 */


//Include FreeRTOS Library
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "xparameters.h"
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

#include "pmodkypd.h"
#include "sleep.h"
#include "xil_cache.h"
#include "math.h"

/* The Tx and Rx tasks as described at the top of this file. */
static void prvTxTask( void *pvParameters );
static void prvRxTask( void *pvParameters );

/* Palindrome helper functions */
char isPalindrome(const u32 operand);
void printPalindrome(const u32 opNum, const char result);

void DemoInitialize();
u32 SSD_decode(u8 key_value, u8 cathode);

PmodKYPD myDevice;

static TaskHandle_t xTxTask;
static TaskHandle_t xRxTask;
static QueueHandle_t xQueue = NULL;

//GPIO Variable RGBLED
XGpio RGBInst;

#define DEFAULT_KEYTABLE "0FED789C456B123A"

//GPIO Parameter definitions from xparameters.h
#define RGBLED_DEVICE_ID 	XPAR_AXI_GPIO_RGB_LED_DEVICE_ID

#define WHITE_IN_RGB		7

#define MAX_U32 4294967295

void DemoInitialize() {
   KYPD_begin(&myDevice, XPAR_AXI_GPIO_PMOD_KEYPAD_BASEADDR);
   KYPD_loadKeyTable(&myDevice, (u8*) DEFAULT_KEYTABLE);
}

// MAIN FUNCTION
int main (void)
{
  int status;

  xil_printf("System Ready!\n");

  // Initialize RGB LED
  status = XGpio_Initialize(&RGBInst, RGBLED_DEVICE_ID);
  if(status != XST_SUCCESS){
	  xil_printf("GPIO Initialization for RGB LED unsuccessful.\r\n");
	  return XST_FAILURE;
  }

  // Set RGB LED direction to output
  XGpio_SetDataDirection(&RGBInst, 1, 0x00);

  /* Create the two tasks.  The Tx task is given a higher priority than the
  Rx task. Dynamically changing the priority of Rx Task later on so the Rx task will leave the Blocked state and pre-empt the Tx
  task as soon as the Tx task fills the queue. */

  xTaskCreate( prvTxTask,					/* The function that implements the task. */
    			( const char * ) "Tx", 		/* Text name for the task, provided to assist debugging only. */
    			configMINIMAL_STACK_SIZE, 	/* The stack allocated to the task. */
    			NULL, 						/* The task parameter is not used, so set to NULL. */
    			tskIDLE_PRIORITY+2,			/* The task runs at the idle priority. */
    			&xTxTask );

  xTaskCreate( prvRxTask,
    			( const char * ) "Rx",
				configMINIMAL_STACK_SIZE,
				NULL,
    			tskIDLE_PRIORITY + 1,
    			&xRxTask );

  /* Create the queue used by the tasks. */
  xQueue = xQueueCreate( 3,				/* There are three items in the queue, two operands and then operation using keypad */
		  	  sizeof( unsigned int ) );	/* Each space in the queue is large enough to hold a uint32_t. */

  /* Check the queue was created. */
  configASSERT(xQueue);

  DemoInitialize();

  vTaskStartScheduler();

  while(1);

  return 0;
}

/*-----------------------------------------------------------*/
static void prvTxTask( void *pvParameters )
{
	UBaseType_t uxPriority;

	for( ;; ) {
	   u16 keystate;
	   XStatus status, last_status = KYPD_NO_KEY;
	   u8 key, last_key = 'x';
	   u32 factor = 0, current_value = 0;

	   Xil_Out32(myDevice.GPIO_addr, 0xF);
	   xil_printf("PMOD KYPD demo started. Press any key on the Keypad.\r\n");

	   uxPriority = uxTaskPriorityGet( NULL );

	   while (1) {

	      // Capture state of each key
	      keystate = KYPD_getKeyStates(&myDevice);

	      // Determine which single key is pressed, if any
	      status = KYPD_getKeyPressed(&myDevice, keystate, &key);

	      //this functions returns the number of entries in the queue, so when the queue is full, i.e., 2 entries, decreased the priority of this task and hence receive task
	      //will immediately start to execute.
	      if(uxQueueMessagesWaiting( xQueue ) == 3){

			  /*********************************/
	    	  // enter the function to dynamically change the priority when queue is full. This way when the queue is full here, we change the priority of this task
	    	  // and hence queue will be read in the receive task to perform the operation. If you change the priority here dynamically, make sure in the receive task to do the counter part!!!
	    	  /*********************************/
	    	  vTaskPrioritySet(NULL, tskIDLE_PRIORITY);
	      }

	      // Print key detect if a new key is pressed or if status has changed
	      if (status == KYPD_SINGLE_KEY
	            && (status != last_status || key != last_key)) {
	         xil_printf("Key Pressed: %c\r\n", (char) key);
	         last_key = key;

	         //whenever 'F' is pressed, the aggregated number will be registered as an operand
	         if((char)key == 'F'){
	        	 xil_printf("Final current_value of operand= %d\n",current_value);

	        	 /*******************************/
	        	 //write the logic to enter the updated variable here to the Queue
	        	 /*******************************/
	        	 xQueueSend(xQueue, &current_value, 0);

		         current_value = 0;
	         }
	         //if 'E' is pressed, it resets the current value of the operand and allows the user to enter a new value
	         else if((char)key == 'E'){
	        	 xil_printf("current_value of operand has been reset. Please enter the new value.\n");

	        	 factor = 0;
	        	 current_value = 0;
	         }
	         //case when we consider input key strokes from '0' to '9' (only these are the valid key inputs for all the four operations)
			 //the current_value is aggregated as the user presses consecutive digits
	         //e.g. if the user presses the following digits in this order 4 > 5 > 8  => current_value will end up being 458
	         else if(key>='0' && key<='9'){
	        	 factor = (int)(key - '0');
	        	 current_value = current_value*10 + factor;
	        	 xil_printf("current_value = %d\n",current_value);
	         }
	         else if((uxQueueMessagesWaiting( xQueue ) == 2) &&(
					 (char)key == 'A' ||
					 (char)key == 'B' ||
					 (char)key == 'C' ||
					 (char)key == 'D')){

				 /*****************************************/
	        	 //once two operands are in the queue, enter the third value to the queue to indicate the operation to be performed using A,B,C or D key
	        	 //store the current key value to the queue as the third element
	        	 /*****************************************/
	        	 xQueueSend(xQueue, &key, 0);

		         current_value = 0;
	         }
	      }
	      else if (status == KYPD_MULTI_KEY && status != last_status)
	         xil_printf("Error: Multiple keys pressed\r\n"); //this is valid whenever two or more keys are pressed together

	      last_status = status;
	      usleep(1000);
	   }
	}
}
/*-----------------------------------------------------------*/
static void prvRxTask( void *pvParameters )
{
	UBaseType_t uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );

	const TickType_t xDelay1500ms = pdMS_TO_TICKS(1500UL);

	u32 operandA, operandB;

	for( ;; )
	{
		/***************************************/
		//...Write code here to read the three elements from the queue and perform the required operation.
		//...Display the output result on the console for all the four operations.
		//...If you have dynamically changed the priority of this task in TxTask, you need to change the priority here accordingly, respectively using vTaskPrioritySet(). This can be done after
		//	 you finish calculation part.
		//...This way once the RxTask is done, TxTask will have a higher priority and hence will wait for the next series of inputs from the user
		//...You can write a switch-case statement or if-else statements for each different operation
		//...For the Palindrome check, think of a way to find the reverse of each operand (two loops for each operand!) Compared this reverse operand with the original operand.
		//...For RGB led, look at the function that was used in previous labs for writing the value to the led. Initialization and color definition is already provided to you in this file.
		/***************************************/

		u32 item;
		xQueueReceive(xQueue, &item, 0);

		switch (uxQueueMessagesWaiting( xQueue )) {
			case 2:
				operandA = item;
				break;
			case 1:
				operandB = item;
				break;
			case 0: {
				switch ((char)item) {
					case 'A':
						if (MAX_U32 - operandA < operandB)
							xil_printf("ERROR: Addition overflow for operands: %u, %u\r\n", operandA, operandB);
						else
							xil_printf("%u + %u = %u\r\n", operandA, operandB, operandA + operandB);
						break;
					case 'B':
						// Subtraction of unsigned integers cannot overflow, however we need to be careful of how the sign bit is handled
						if (operandA > operandB)
							xil_printf("%u - %u = %u\r\n", operandA, operandB, operandA - operandB);
						else
							xil_printf("%u - %u = %d\r\n", operandA, operandB, operandA - operandB);
						break;
					case 'C':
						if (MAX_U32 / operandA < operandB)
							xil_printf("ERROR: Multiplication overflow for operands: %u, %u\r\n", operandA, operandB);
						else
							xil_printf("%u * %u = %u\r\n", operandA, operandB, operandA * operandB);
						break;
					case 'D': {
						char opAisP = isPalindrome(operandA);
						char opBisP = isPalindrome(operandB);
						if (!(opAisP && opBisP)) {
							printPalindrome(1, opAisP);
							printPalindrome(2, opBisP);
						} else {
							xil_printf("Both operands are palindromes!\r\n");
							XGpio_DiscreteWrite(&RGBInst, 1, WHITE_IN_RGB);
							vTaskDelay(xDelay1500ms);
							XGpio_DiscreteWrite(&RGBInst, 1, 0);
						}
						break;
					}
				}
				// Here the priority of the RX task is reset
				vTaskPrioritySet(xTxTask, tskIDLE_PRIORITY + 2);
			}
		}
	}
}

void printPalindrome(const u32 opNum, const char result) {
	xil_printf("Operator %u is ", opNum);
	if (!result)
		xil_printf("not ");
	xil_printf("a palindrome!\r\n");
}

char isPalindrome(const u32 operand) {
	u32 buffer = operand, reverse = 0;
	while (buffer > 0) {
		reverse = (reverse * 10) + (buffer % 10);
		buffer /= 10;
	}
	return reverse == operand;
}

