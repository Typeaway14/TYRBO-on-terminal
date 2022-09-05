#!/bin/bash
#date: 05-09-2022
#author: Typeaway14
#purpose: enable or disable the keyboard. originally created for TYRBO(https://github.com/inirah02/TYRBO)

VALUE=$1
#echo $1

#use 'xinput list' and find id and slave keyboard number for 'AT Translated Set 2 Keyboard'

if [[ $VALUE == 1 ]];
then
	#xinput float #id
	xinput float 13 
elif [[ $VALUE == 0 ]];
then
	#xinput reattach #id #slave_keyboard_number
	xinput reattach 13 3
fi
