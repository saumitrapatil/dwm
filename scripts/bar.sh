#!/bin/bash

brightness() {
    printf "BRI: "
    printf "%.0f |" $(cat /sys/class/backlight/*/brightness)
}

volume(){
    vol=$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')
    isMuted=$(pactl list sinks | grep -A 10 'State: RUNNING' | grep 'Mute:' | awk '{print $2}')
	printf "VOL: "
    if [[ $isMuted == "yes" ]]; then
        echo "Muted shh!! |"
    else
        echo "$vol |"
    fi
}

cpu() {
    cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)
    printf "CPU: $cpu_val%% |"
}

mem() {
    printf "MEM: "
    printf "$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g) |"
}

clock() {
    printf "TIME: "
    printf "$(date '+%H:%M') |"
}

battery() {
    get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
    printf "BAT: $get_capacity%% "
}

while true; do
    xsetroot -name "$(volume) $(brightness) $(cpu) $(mem) $(clock) $(battery)"
done
