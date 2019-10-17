/* See LICENSE file for copyright and license details. */

/* includes */
#include <X11/XF86keysym.h>
#include "selfrestart.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = {
	"L Sans Mono:pixelsize=14",
	"Material Design Icons:pixelsize=14",
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char *colors[][3]      = {
	/*					fg         bg          border   */
	// [SchemeNorm] =	 { col_gray3, col_gray1,  col_gray2 },
	// [SchemeSel]  =	 { col_gray4, col_cyan,   col_cyan },
	[SchemeNorm] =	 { "#657b83", "#002b36",  "#002b36" },
	[SchemeSel]  =	 { "#002b36", "#93a1a1",  "#93a1a1" },
	[SchemeWarn] =	 { col_black, col_yellow, col_red },
	[SchemeUrgent]=	 { col_white, col_red,    col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	// Display 1, tag 1
	{ "Mailspring",       NULL,       NULL,       1 << 0,       0,            0 },
	{ "MineTime",         NULL,       NULL,       1 << 0,       0,            0 },
	{ "teams-for-linux",  NULL,       NULL,       1 << 0,       0,            0 },
	// Display 1, tag 2
	{ "Skype",            NULL,       NULL,       1 << 1,       0,            0 },
	{ "yakyak",           NULL,       NULL,       1 << 1,       0,            0 },
	{ "discord",          NULL,       NULL,       1 << 1,       0,            0 },
	// Display 1, tag 3
	{ "CherryTree",       NULL,       NULL,       1 << 2,       1,            0 },
	// Display 1, tag 8
	// { "Slack",            NULL,       NULL,       1 << 7,       0,            0 },
	// Any display, tag 9
	{ "firefox",          NULL,       NULL,       1 << 8,       0,           -1 },
	// Any display, force floating
	{ "KeePass2",         NULL,       NULL,       0,            1,           -1 },
	{ "Chatty",           NULL,       NULL,       0,            1,           -1 },
	{ "Gimp",             NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
  { "|M|",      centeredmaster },          /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },                    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ ">M>",      centeredfloatingmaster },
	{ "[⊞]",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask  // Windows key for meta
#define AltMask Mod1Mask  // Alt key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,              KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask,         KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|AltMask,      KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ControlMask|AltMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *surfcmd[]  = { "tabbed", "surf", "-pe", NULL };
static const char *keepasscmd[] = { "keepass", NULL };
static const char *keepassautotypecmd[] = { "keepass", "--auto-type", NULL };
// static const char *suspendcmd[] = { "systemctl", "suspend", NULL };
static const char *vifmcmd[] = { "st", "vifm", NULL };
static const char *screenshotcmd[] = { "scrot", "--select", "~/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
static const char *screenshotfocusedcmd[] = { "scrot", "--focused", "~/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
static const char *screenshotfullcmd[] = { "scrot", "--multidisp", "~/Pictures/Screenshots/screenshot_%Y-%m-%d_%H-%M-%S.png", NULL };
// Media player controls by playerctl command (https://github.com/acrisci/playerctl)
static const char *mediaplaycmd[] = { "playerctl", "play-pause", NULL };
static const char *mediastopcmd[] = { "playerctl", "stop", NULL };
static const char *medianextcmd[] = { "playerctl", "next", NULL };
static const char *mediaprevcmd[] = { "playerctl", "previous", NULL };
// volume media keys
static const char *volupcmd[]  = { "pactl", "set-sink-volume", "0", "+2%", NULL };
static const char *voldowncmd[]  = { "pactl", "set-sink-volume", "0", "-2%", NULL };
static const char *volmutecmd[]  = { "pactl", "set-sink-mute", "0", "toggle", NULL };
// custom scripts for various things
static const char *btheadset[] = { "/home/matt/scripts/bt.sh", "flip", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_bracketleft,  rotatestack, {.i = +1 } },
	{ MODKEY,                       XK_bracketright, rotatestack, {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY|AltMask,               XK_minus,  setmfact,       {.f = -0.05} },
	{ MODKEY|AltMask,               XK_equal,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|AltMask,               XK_o,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|AltMask,               XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|AltMask,               XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|AltMask,               XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|AltMask,               XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|AltMask,               XK_g,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|AltMask,		            XK_bracketleft, cyclelayout, {.i = -1 } },
	{ MODKEY|AltMask,               XK_bracketright, cyclelayout, {.i = +1 } },
	{ MODKEY|AltMask,               XK_0,      setlayout,      {0} },
	{ MODKEY,                       XK_backslash, togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|AltMask,               XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
 	TAGKEYS(                        XK_9,                      8)
	/* Media and special Keyboard Keys */
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volupcmd } },
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = voldowncmd } },
	{ 0,              XF86XK_AudioMute,        spawn,          {.v = volmutecmd } },
	{ 0,              XF86XK_AudioPlay,        spawn,          {.v = mediaplaycmd } },
	{ 0,              XF86XK_AudioPause,        spawn,         {.v = mediaplaycmd } },
	{ 0,              XF86XK_AudioStop,        spawn,          {.v = mediastopcmd } },
	{ 0,              XF86XK_AudioNext,        spawn,          {.v = medianextcmd } },
	{ 0,              XF86XK_AudioPrev,        spawn,          {.v = mediaprevcmd } },
	{ 0,              XF86XK_Tools,            spawn,          {.v = btheadset } },
	/* Custom Commands */
	{ MODKEY,                       XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = surfcmd } },
	{ AltMask|ControlMask,          XK_k,      spawn,          {.v = keepasscmd } },
	{ AltMask|ControlMask,          XK_a,      spawn,          {.v = keepassautotypecmd } },
	{ AltMask,                      XK_F4,     killclient,     {0} }, /* exit client */
	{ AltMask|ControlMask,          XK_Delete, quit,           {0} }, /* quit dwm */
	{ AltMask|ControlMask,          XK_BackSpace, self_restart, {0} }, /* restart dwm */
	{ MODKEY,                       XK_e,      spawn,          {.v = vifmcmd } },
	{ 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },
	{ ControlMask,                  XK_Print,  spawn,          {.v = screenshotfocusedcmd } },
	{ ShiftMask|ControlMask,        XK_Print,  spawn,          {.v = screenshotfullcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

