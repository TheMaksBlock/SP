#!/bin/bash

zenity --question --text="Вы хотите открыть вложенный диалог?" --title="Первый диалог"

if [ $? = 0 ]; then
    zenity --question --text="Вы выбрали 'Да'. Продолжить?" --title="Второй диалог"
    if [ $? = 1 ]; then
        zenity --info --text="Вы выбрали 'Нет'. Завершение..." --title="Завершение"
    fi
    
else
    zenity --info --text="Вы выбрали 'Нет'. Завершение..." --title="Завершение"
fi
