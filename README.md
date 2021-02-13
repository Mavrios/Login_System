# Login System 
This project made with Atmega32 , LCD , KEYPAD and BUZZER 

## Project Discription:
- First the LCD Welcome the user.
- Then Asking the user to Enter Valid ID
If the ID is wrong the user has infinite tries to enter valid ID
- The Writen ID Displayed in LCD
- If ID is Valid asking the user to enter Password of Choosen ID
- The Password Displayed in LCD as '*'
The user has only 3 tries to enter the Correct Password
- If the user entered correct password the lcd welcome the ID.
- If the user entered 3 wrong password the lcd Turn off then the buzzer will Work.


**This Project is done with layer Arch** 
- DIO -> MCAL
- LCD -> HAL
- KEYPAD -> HAL
- main.c -> APP
- Libraries -> Services