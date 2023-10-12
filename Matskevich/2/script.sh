#!/bin/bash

name=$(zenity --entry --text="Введите ваше имя:" --title="Имя")


profession=$(zenity --entry --text="Введите вашу профессию:" --title="Профессия")

zenity --info --text="Ваше имя: $name\nВаша профессия: $profession"

exit 0
