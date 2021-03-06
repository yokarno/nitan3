inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","鳌府大厅");
        set("long", @LONG
这里是鳌拜府的大厅，大厅相当的宽敞明亮，四周的墙上悬挂满了各朝名人
的真迹，正堂坐着一个满面虬须，身材魁梧，身着黄马褂的中年男子，看来那就
是当朝第一大臣，被御封为『满洲第一勇士』的鳌拜了。大厅往北是一条走廊，
那是通往鳌府的后院所在。
LONG );
	set("exits", ([
		"north" :  "/d/beijing/aofu_zoulang2",
		"south" :  "/d/beijing/aofu_dayuan",
	]));
	set("objects", ([
		"/d/beijing/npc/aobai" : 1,
		"/d/beijing/npc/yahuan_a" : 1,
	]));
	set("coor/x", -50);
	set("coor/y", 360);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("ao bai", environment(me))) && dir == "north")
                return notify_fail("鳌拜大声喝道：他奶奶的，你要干嘛？\n\n");
	return ::valid_leave(me, dir);
}