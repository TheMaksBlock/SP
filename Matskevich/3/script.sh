#!/bin/bash

selected_currency=$(zenity --entry --title="Выберите валюту" --text="Введите название валюты (dollar или euro):")

if [ "$selected_currency" = "dollar" ]; then
    exchange_rate=3.36
elif [ "$selected_currency" = "euro" ]; then
    exchange_rate=3.55
else
    zenity --info --text="Неверное название валюты. Завершение..."
    exit 1
fi

zenity --info --text="Курс $selected_currency: $exchange_rate Byn"

exit 0
