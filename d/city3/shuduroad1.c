// Room: shuduroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "蜀都大道");
        set("long", @LONG
这里是蜀都大道，向西就可以到提督府了。过往的车马卷起阵阵尘土，来去
的官差阵步如飞，有一些官兵在路上巡哨。你感到一点点害怕，真后悔拐进这里
来。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
	    "east"  : "/d/city3/eastroad2",
	    "west"  : "/d/city3/guangchang",
            "south" : "/d/city3/fomiao",
	]));
	set("objects", ([
	    "/d/city/npc/bing" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -420);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
