//Room: /d/dali/shijing.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","石径");
        set("long", @LONG
你走在大理镇南王府中的石径上。路边长木遮天，微风习习，十分凉爽。路
南是一个碧绿透亮的小湖，水禽游鱼，映影其间。西边通向大厅，东面好象是个
花园。
LONG );
	set("objects", ([
	   "/d/dali/npc/xianhe": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "east"  : "/d/dali/tingyuan",
	    "west"  : "/d/dali/wfdating",
	]));
	setup();
	replace_program(ROOM);
}

