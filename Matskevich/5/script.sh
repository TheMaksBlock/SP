#!/bin/bash

while true; do
    selected_currency=$(zenity --list --title="Выберите валюту" --text="Выберите валюту из списка или 'exit' для выхода:" --column="Валюта" dollar euro exit)

    if [ "$selected_currency" = "exit" ]; then
        break
    fi

    if [ "$selected_currency" = "dollar" ]; then
        exchange_rate=3.36
    elif [ "$selected_currency" = "euro" ]; then
        exchange_rate=3.55
    else
        zenity --info --text="Неверное название валюты. Попробуйте снова или выберите 'exit' для выхода."
        continue
    fi

    zenity --info --text="Курс $selected_currency: $exchange_rate"
done

exit 0
