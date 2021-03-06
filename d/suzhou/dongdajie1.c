// Room: /d/suzhou/dongdajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "东大街");
        set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边是东大街的延伸，南面是苏
州城里一个老字号的当铺，北面是一条小胡同。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/dongdajie2",
		"north"     : "/d/suzhou/hutong1",
		"south"     : "/d/suzhou/dangpu",
		"southwest" : "/d/suzhou/baodaiqiao",
		"northwest" : "/d/suzhou/canlangting",
	]));
	set("objects", ([
		"/d/suzhou/npc/kid" : 1,
	]));
	set("coor/x", 210);
	set("coor/y", -210);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

