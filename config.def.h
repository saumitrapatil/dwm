/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_bg[]			= "#005072";
static const char col_bor[]			= "#caace6";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_bg,    col_bor},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "discord",  NULL,       NULL,       1 << 3,            0,           -1 },
	{ "Chromium", NULL,       NULL,       1 << 0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static int attachbelow = 0;    /* 1 means attach after the currently active window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	// { "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	// { "===",      bstackhoriz },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	// { ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_bg, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun" , NULL };
static const char *termcmd[]  = { "wezterm", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
    /*                                 Applications                             */
	{ MODKEY,                       XK_BackSpace,  spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("chromium --incognito") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("zen-browser --private-window") },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("firefox --private-window") },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("discord") },
	{ MODKEY|ShiftMask|ControlMask, XK_p,      spawn,          SHCMD("feh --bg-fill --randomize /home/saumitra/Pictures/Wallpapers/") },
	{ 0,                            XK_Print,  spawn,          SHCMD("flameshot full") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("thunar") },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("clipmenu") },


    /*                                  Media                                   */
	{ 0,                            XF86XK_AudioPlay,  spawn,          SHCMD("playerctl --player spotify play-pause") },
	{ 0,                            XF86XK_AudioNext,  spawn,          SHCMD("playerctl --player spotify next") },
	{ 0,                            XF86XK_AudioPrev,  spawn,          SHCMD("playerctl --player spotify previous") },
	{ MODKEY,                       XK_KP_Right,	   spawn,          SHCMD("playerctl --player spotify next") },
	{ MODKEY,                       XK_KP_Left,		   spawn,          SHCMD("playerctl --player spotify prev") },
	{ 0,                            XF86XK_TouchpadToggle,  spawn,     SHCMD("playerctl --player spotify prev") },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,   SHCMD("playerctl --player spotify volume 0.01+") },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,   SHCMD("playerctl --player spotify volume 0.01-") },

    

    /*                                  Brightness and Volume                           */
	{ MODKEY,                       XK_F7,      spawn,          SHCMD("brightnessctl s 5-") },
	{ MODKEY,                       XK_F8,      spawn,          SHCMD("brightnessctl s +5") },
	{ MODKEY,                       XK_F1,      spawn,          SHCMD("pamixer -t") },
	{ MODKEY,                       XK_F2,      spawn,          SHCMD("pamixer -d 5") },
	{ MODKEY,                       XK_F3,      spawn,          SHCMD("pamixer -i 5") },
	{ 0|ControlMask|ShiftMask,      XK_z,       spawn,          SHCMD("~/.scripts/switch-sink.sh") },



     /*                                  Layout                                  */
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    toggleAttachBelow,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY|ControlMask,           XK_d,      setlayout,      {.v = &layouts[2]} }, // dwindle
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} }, // bstack 
	{ MODKEY|ControlMask,           XK_h,      setlayout,      {.v = &layouts[4]} }, // horizgrid
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} }, // gaplessgrid
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[6]} }, // centeredmaster
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[7]} }, // floating
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask|ShiftMask,	XK_q,      quit,           {0} }, 
	{ MODKEY|ShiftMask,				XK_q,      quit,           {1} }, 


    /*                              Multi Monitor                               */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },



     /*                              Tags                                        */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

