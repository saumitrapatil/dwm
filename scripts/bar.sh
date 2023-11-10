#!/bin/bash

brightness() {
    printf " "
    printf "%.0f | " $(cat /sys/class/backlight/*/brightness)
}

volume(){
    vol=$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')
    isMuted=$(pactl list sinks | grep -A 10 'State: RUNNING' | grep 'Mute:' | awk '{print $2}')
    if [[ $isMuted == "yes" ]]; then
        echo "Muted shh!! | "
    else
        echo "$vol | "
    fi
}

cpu() {
    cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)
    printf " $cpu_val%% | "
}

mem() {
    printf " "
    printf "$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g) | "
}

clock() {
    printf "󱑆 "
    printf "$(date '+%H:%M') | "
}

battery() {
    get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
    printf " $get_capacity%% "
}

while true; do
    xsetroot -name "$(volume) $(brightness) $(cpu) $(mem) $(clock) $(battery)"
done
