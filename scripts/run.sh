#! /bin/sh

if xrandr | grep "HDMI-1-0 connected" &> /dev/null;
then
    xrandr --output HDMI-1-0 --primary --mode 2560x1080 --rate 100.00 --rotate normal --output eDP --mode 1920x1080 --rotate normal --right-of HDMI-1-0
elif xrandr | grep "HDMI-0 connected" &> /dev/null;
then
    xrandr --output HDMI-0 --primary --mode 2560x1080 --rate 100.00 --rotate normal --output eDP-1-0 --mode 1920x1080 --rotate normal --right-of HDMI-0
fi

picom -b &
feh --bg-fill --randomize /home/saumitra/Pictures/Wallpapers &

xinput --set-prop 'ELAN1200:00 04F3:30BA Touchpad' 'libinput Tapping Enabled' 1 &
xinput --set-prop 'Logitech Gaming Mouse G402' 'libinput Accel Profile Enabled' 0, 1 &

~/dwm/scripts/bar.sh &
while type dwm >/dev/null; do dwm && continue || break; done
