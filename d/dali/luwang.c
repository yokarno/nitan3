//Room: /d/dali/luwang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","鲁望镇");
        set("long", @LONG
这里是普麽部的鲁望镇，普麽部属台夷，领属还有附近的越州。这是一座建
在山坡上的小镇，东面和北面是高耸的群山，向西和南眺望均可见村庄和城镇。
LONG );
	set("objects", ([
	   "/d/dali/npc/tshangfan": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"    : "/d/dali/feilihu",
	    "east"    : "/d/dali/yulin",
	    "south"   : "/d/dali/shuitian",
	    "north"   : "/d/dali/zhulou3",
	]));
	setup();
	replace_program(ROOM);
}

