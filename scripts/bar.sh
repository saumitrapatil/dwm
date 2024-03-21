#!/bin/bash

brightness() {
    printf "BRI: "
    printf "%.0f |" $(cat /sys/class/backlight/*/brightness)
}

sink(){
	current_sink=$(pactl info | grep 'Default Sink' | awk '{print $3}')
	printf "Sink: "
	if [[ "$current_sink" == *"hdmi"* ]]; then
		echo "HDMI |"
	else
		echo "Analog |"
	fi
}

volume(){
    vol=$(pamixer --get-volume)
    isMuted=$(pactl list sinks | grep -A 10 'State: RUNNING' | grep 'Mute:' | awk '{print $2}')
	printf "VOL: "
    if [[ $isMuted == "yes" ]]; then
        echo "Muted shh!! |"
    else
        echo "$vol |"
    fi
}

cpu() {
    cpu_use=$(top -b -n 1 | grep 'Cpu(s)' | awk '{print 100 - $8}')
    printf "CPU: $cpu_use%% |"
}

mem() {
    printf "MEM: "
    printf "$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g) |"
}

clock() {
    printf "TIME: "
    printf "$(date '+%d %b, %A, %R') |"
}

battery() {
    get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
    printf "BAT: $get_capacity%% "
}

while true; do
	xsetroot -name "$(sink) $(volume) $(brightness) $(cpu) $(mem) $(clock) $(battery)"
done
