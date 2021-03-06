// Room: /d/suzhou/canlangting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "沧浪亭");
        set("long", @LONG
沧浪亭在苏州的北大街南侧，因为环境相对幽雅，使得男女老少都喜爱在这
里闲庭散步。在亭中放眼望去，四周一片碧绿的草坪，亭子屹然于耸翠之中，飞
檐凌空琵琶形牌科，布满檐口四周，亭上的额匾和石柱上的楹联(lian)使人更加
喜爱这里。
LONG );
	set("outdoors", "suzhou");
	set("item_desc", ([
		"lian" :
"清风明月本无价 近水远山皆有情\n",
	]));
	set("exits", ([
		"southeast" : "/d/suzhou/dongdajie1",
		"southwest" : "/d/suzhou/xidajie1",
		"north"     : "/d/suzhou/beidajie1",
		"south"     : "/d/suzhou/baodaiqiao",
                "east"      : "/d/suzhou/hong-damen",
	]));
	set("objects", ([
		// "/adm/npc/hongniang" :1,
	]));
	set("coor/x", 200);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

