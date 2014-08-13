#!/usr/bin/python
# Filenme: if.py
running = True
number = 23
while running:
	guess = int(raw_input("Enter an integer:"))
	if guess == number:
		print 'Congratulations, you guessed it.'#new block starts here
		running = False # this causes the while loop to stop
	elif guess < number:
		print 'No, it is a little lower than that'# Another block
		#You can do whatever you want in a block ...
	else:
		print 'No, it is a little highter than that'
		#you must have guess > number to reach here
else:
	print 'the while loop is over.'
print 'Done'
#This last statement is always executed, after the if statement is executed
