'''
* Author: Jeroen Op de Beek
* Date: 2024-08-25
* License: CC0
* Source: me
* Description: Gives a notification every hour of the contest.
* Status: Used, works well
'''
import time 
from os import system
while True: 
    time.sleep(3600)
    system('notify-send "Hourly Reminder" "It has been an hour!" -u critical')
