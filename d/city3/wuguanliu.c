// Room: wuguanliu.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "金牛武馆四部");
        set("long", @LONG
这里是「金牛武馆」教授四部，师傅刘虹瑛教授如下技能：基本轻功，基本
内功，基本招架，基本掌法，基本剑法。
LONG );
	set("objects", ([
		"/d/city3/npc/liuhongying" : 1,
	]));
        set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
	set("no_clean_up", 0);
	set("exits", ([
		"south" : "/d/city3/wuguan",
	]));
	set("coor/x", -410);
	set("coor/y", -140);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
