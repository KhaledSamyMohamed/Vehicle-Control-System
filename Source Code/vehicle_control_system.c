/*
 * Name: vehicle_control_system.c
 *
 * Created on: Jan 17, 2024
 *
 * Author: KhaledSamyMohamed
 */

#include <stdio.h>

// Define WITH_ENGINE_TEMP_CONTROLLER to enable or disable the Engine Temperature Controller code
#define WITH_ENGINE_TEMP_CONTROLLER 1
#define TRUE 1

// Enumerations for states
typedef enum {
	ENGINE_OFF, ENGINE_ON
} EngineState;
typedef enum {
	AC_OFF, AC_ON
} ACState;
typedef enum {
	TEMP_CONTROLLER_OFF, TEMP_CONTROLLER_ON
} TempControllerState;

// Global variables
int vehicleSpeed = 0;
int roomTemperature = 0;
int engineTemperature = 0;
EngineState engineState = ENGINE_OFF;
ACState acState = AC_OFF;
TempControllerState tempControllerState = TEMP_CONTROLLER_OFF;

// Function prototypes
void DisplayMainMenu();
void DisplaySensorsMenu();
void TurnOnEngine();
void TurnOffEngine();
void SetTrafficLight();
void SetRoomTemperature();
void SetEngineTemperature();
void DisplayVehicleState();

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while (TRUE) {
		DisplayMainMenu();

		// Get user input
		printf("Enter your choice (a, b, c): ");
		char userChoice;
		scanf(" %c", &userChoice);

		switch (userChoice) {
		case 'A':
		case 'a':
			TurnOnEngine();
			break;
		case 'B':
		case 'b':
			TurnOffEngine();
			break;
		case 'C':
		case 'c':
			printf("Quitting the system. Goodbye!\n");
			return 0;
		default:
			printf("Invalid choice. Please enter a, b, or c.\n");
		}
	}

	return 0;
}

void DisplayMainMenu() {
	printf("\nPlease choose an option:\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
}

void DisplaySensorsMenu() {
	printf("\nSystem State: Engine is ON\n");
	printf("Sensors set menu:\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
}

void TurnOnEngine() {
	if (engineState == ENGINE_ON) {
		printf("The engine is already ON.\n");
	} else {
		printf("Vehicle engine is turned on.\n");
		engineState = ENGINE_ON;

		// Display the system state and enter the sensors set menu loop
		while (engineState == ENGINE_ON) {
			DisplaySensorsMenu();

			// Get user input for the sensors set menu
			printf("Enter your choice (a, b, c, d): ");
			char userChoice;
			scanf(" %c", &userChoice);

			switch (userChoice) {
			case 'A':
			case 'a':
				TurnOffEngine();
				break;
			case 'B':
			case 'b':
				SetTrafficLight();
				break;
			case 'C':
			case 'c':
				SetRoomTemperature();
				break;
			case 'D':
			case 'd':
				SetEngineTemperature();
				break;
			default:
				printf("Invalid choice. Please enter a, b, c, or d.\n");
			}
		}
	}
}

void TurnOffEngine() {
	if (engineState == ENGINE_ON) {
		printf("Turning off the vehicle engine.\n");
		engineState = ENGINE_OFF;
	} else {
		printf("The engine is already OFF.\n");
	}
}

void SetTrafficLight() {
	printf("Setting the traffic light color.\n");
	char trafficLight;
	printf("Enter the traffic light color (G, O, R): ");
	scanf(" %c", &trafficLight);

	switch (trafficLight) {
	case 'G':
	case 'g':
		vehicleSpeed = 100;
		break;
	case 'O':
	case 'o':
		vehicleSpeed = 30;
		// Handle condition 7.d when vehicle speed becomes 30 km/h
		if (vehicleSpeed == 30) {
			acState = AC_ON;  // Turn on AC
			roomTemperature = (int) (roomTemperature * 1.25) + 1; // Adjust room temperature
#if WITH_ENGINE_TEMP_CONTROLLER
			tempControllerState = TEMP_CONTROLLER_ON; // Turn on engine temperature controller
			engineTemperature = (int) (engineTemperature * 1.25) + 1; // Adjust engine temperature
#endif
		}
		break;
	case 'R':
	case 'r':
		vehicleSpeed = 0;
		break;
	default:
		printf("Invalid traffic light color.\n");
	}

	DisplayVehicleState();
}

void SetRoomTemperature() {
	printf("Setting the room temperature (Temperature Sensor).\n");
	printf("Enter the room temperature: ");
	scanf("%d", &roomTemperature);

	// Adjust AC and Engine Temperature Controller based on room temperature
	if (roomTemperature < 10 || roomTemperature > 30) {
		acState = AC_ON;
#if WITH_ENGINE_TEMP_CONTROLLER
		tempControllerState = TEMP_CONTROLLER_ON;
#endif
	} else {
		acState = AC_OFF;
#if WITH_ENGINE_TEMP_CONTROLLER
		tempControllerState = TEMP_CONTROLLER_OFF;
#endif
	}

	DisplayVehicleState();
}

void SetEngineTemperature() {
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Setting the engine temperature (Engine Temperature Sensor).\n");
	printf("Enter the engine temperature: ");
	scanf("%d", &engineTemperature);

	// Adjust Engine Temperature Controller based on engine temperature
	if (engineTemperature < 100 || engineTemperature > 150) {
		tempControllerState = TEMP_CONTROLLER_ON;
	} else {
		tempControllerState = TEMP_CONTROLLER_OFF;
	}

	DisplayVehicleState();
#endif
}

void DisplayVehicleState() {
	printf("\nCurrent Vehicle State:\n");
	printf("Engine state: %s\n", (engineState == ENGINE_ON) ? "ON" : "OFF");
	printf("AC: %s\n", (acState == AC_ON) ? "ON" : "OFF");
	printf("Vehicle Speed: %d km/hr\n", vehicleSpeed);
	printf("Room Temperature: %d\n", roomTemperature);
	printf("Engine Temperature Controller State: %s\n",
			(tempControllerState == TEMP_CONTROLLER_ON) ? "ON" : "OFF");
	printf("Engine Temperature: %d\n", engineTemperature);
}

