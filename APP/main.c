/*
 * main.c
 *
 *  Created on: Jan 29, 2021
 *      Author: Kishk
 *
 */

#include "../Services/STD_TYPES.h"
#include "../Services/BIT_MATHS.h"
#include "util/delay.h"
#include "../MCAL/01-DIO/DIO_interface.h"
#include "../HAL/04- CLCD/CLCD_interface.h"
#include "../HAL/05- Keypad/Keypad_interface.h"

#define ID_Length	3
#define ID_Number	3

#define PASS_Length	3
#define PASS_Number	3

#define Tries 		3



#define ID_Flag		7
#define Pass_Flag	6
void voidClearArr(u8 *Copy_u8Ptr);
u8 u8CheckID(u8 *Copy_u8Ptr, u8 Copy_u8ArrID[ID_Number][ID_Length],
		u8 * Copy_PtrFlag);
u8 u8CheckPass(u8 *Copy_u8Ptr, u8 Copy_u8ArrPass[PASS_Number][PASS_Length], u8 * Copy_PtrFlag);

int main(void) {
	u8 LOC_u8ComeData = 0;
	u8 LOC_u8Flags = 0; // --> BIT No.0 Flag for ID and BIT No.1 Flag for Password
	u8 LOC_u8Counter = 0;
	u8 LOC_u8Counter2 = 0;
	u8 LOC_u8arrID[ID_Number][ID_Length] = { { 'A', 'B', 'C' },
			{ 'C', 'B', 'A' }, { 'A', 'C', 'B' } };
	u8 LOC_u8arrPASS[PASS_Number][PASS_Length] = { { '1', '2', '3' },
			{ '3', '2', '1' }, { '1', '3', '2' } };
	u8 LOC_u8Enter[16] = { 0 };

	u8 LOC_u8Iterator = 0;
	u8 LOC_u8Iterator2 = 0;
	DIO_enumSetPinDirection(DIO_PORTD_PIN7,DIO_OUTPUT);

	Keypad_voidInit();
	CLCD_voidInit();
	CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_4);

	while (1) {

		/* 			ID 			*/
		CLCD_voidSendString((u8 *) "Welcome");
		_delay_ms(3000);
		CLCD_voidClearDisplay();
		CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
		CLCD_voidSendString((u8 *) "Plz Enter ur ID:");
		CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
		while (!GET_BIT(LOC_u8Flags, ID_Flag)) {
			LOC_u8ComeData = Keypad_u8GetPressed();
			if (LOC_u8ComeData != 0) {

				if (LOC_u8ComeData == '#') {
					if (LOC_u8Counter > ID_Length) {
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Wrong ID");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Plz Try Again");
						_delay_ms(2000);
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Plz Enter ur ID:");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						continue;
					}

					else if (u8CheckID(LOC_u8Enter, LOC_u8arrID, &LOC_u8Flags)
							== 1) {
						SET_BIT(LOC_u8Flags, ID_Flag);
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						break;
					}

					else {
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Wrong ID");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Plz Try Again");
						_delay_ms(2000);
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Plz Enter ur ID:");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						continue;
					}
				}
				LOC_u8Enter[LOC_u8Counter] = LOC_u8ComeData;
				LOC_u8Counter++;
				CLCD_voidSendData(LOC_u8ComeData);

			}
		}


		/*			PASSWORD		NOT FINISHED	*/
		CLCD_voidClearDisplay();
		CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
		CLCD_voidSendString((u8 *) "Enter Password: ");
		CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
		while (!GET_BIT(LOC_u8Flags, Pass_Flag)) {
			if(LOC_u8Counter2 == Tries){
				DIO_enumSetPinValue(DIO_PORTD_PIN7,DIO_HIGH);
				CLCD_voidClearDisplay();
				CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
				CLCD_voidSendString((u8 *) "Wrong Password");
				CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
				CLCD_voidSendString((u8 *) "No More Tries!!!");
				_delay_ms(2000);
				CLCD_voidDisplayOff();
				while(1);
			}
			LOC_u8ComeData = Keypad_u8GetPressed();
			if (LOC_u8ComeData != 0) {

				if (LOC_u8ComeData == '#') {
					LOC_u8Counter2++;
					if (LOC_u8Counter > PASS_Length) {
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Wrong Password");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Remain Tries:");
						CLCD_voidSendNumber(Tries - LOC_u8Counter2);
						_delay_ms(2000);
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Enter Password: ");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						continue;
					}

					else if (u8CheckPass(LOC_u8Enter, LOC_u8arrPASS, &LOC_u8Flags)
							== 1) {
						SET_BIT(LOC_u8Flags, Pass_Flag);
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);
						CLCD_voidSendString((u8 *)"Welcome ");
						for(LOC_u8Iterator = 0 ; LOC_u8Iterator< ID_Length ; LOC_u8Iterator++){
							if(GET_BIT(LOC_u8Flags,LOC_u8Iterator)){
								for(LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < ID_Length ; LOC_u8Iterator2++){
								CLCD_voidSendData(LOC_u8arrID[LOC_u8Iterator][LOC_u8Iterator2]);
								}
							}
						}
						while(1);
						break;
					}

					else {
						voidClearArr(LOC_u8Enter);
						voidClearArr(LOC_u8Enter);
						LOC_u8Counter = 0;
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Wrong Password");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Remain Tries:");
						CLCD_voidSendNumber(Tries - LOC_u8Counter2);
						_delay_ms(2000);
						CLCD_voidClearDisplay();
						CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
						CLCD_voidSendString((u8 *) "Enter Password: ");
						CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
						continue;
					}
				}
				LOC_u8Enter[LOC_u8Counter] = LOC_u8ComeData;
				LOC_u8Counter++;
				CLCD_voidSendData('*');

			}
		}

	}
	return 0;

}

u8 u8CheckID(u8 *Copy_u8Ptr, u8 Copy_u8ArrID[ID_Number][ID_Length],
		u8 * Copy_PtrFlag) {
	u8 LOC_u8Result = 0;
	for (u8 LOC_u8Iterator = 0; LOC_u8Iterator < ID_Length + 1; LOC_u8Iterator++) {
		if (LOC_u8Result == 1) {
			SET_BIT(*Copy_PtrFlag, LOC_u8Iterator - 1);
			break;
		}
		if (LOC_u8Iterator > 2){
			break;
		}
		for (u8 LOC_u8Iterator2 = 0; LOC_u8Iterator2 < ID_Number;
				LOC_u8Iterator2++) {
			if (Copy_u8ArrID[LOC_u8Iterator][LOC_u8Iterator2]
					!= Copy_u8Ptr[LOC_u8Iterator2]) {
				LOC_u8Result = 0;
				break;
			} else {
				LOC_u8Result = 1;
			}
		}
	}
	return LOC_u8Result;

}

void voidClearArr(u8 *Copy_u8Ptr) {
	for (u8 LOC_u8Iterator = 0; LOC_u8Iterator < ID_Length; LOC_u8Iterator++) {
		Copy_u8Ptr[LOC_u8Iterator] = 0;
	}
}


u8 u8CheckPass(u8 *Copy_u8Ptr, u8 Copy_u8ArrPass[PASS_Number][PASS_Length], u8 * Copy_PtrFlag){
	u8 LOC_u8Result = 1;
	for (u8 LOC_u8Iterator = 0; LOC_u8Iterator < PASS_Length; LOC_u8Iterator++) {
		if(GET_BIT(*Copy_PtrFlag,LOC_u8Iterator)){
			for(u8 LOC_u8Iterator2 = 0; LOC_u8Iterator2 < PASS_Length ; LOC_u8Iterator2++){
				if(Copy_u8ArrPass[LOC_u8Iterator][LOC_u8Iterator2] == Copy_u8Ptr[LOC_u8Iterator2]){
					continue;
				}
				else{
					LOC_u8Result = 0;
					break;
				}
			}
		}
	}
	return LOC_u8Result;
}
