//Room: /d/dali/cangshanlu1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","苍山山路");
        set("long", @LONG
此处正当河边，两侧山壁几乎是直上直下，面前是一条大河自北滔滔而来，
在此折向东咆哮而去，河水奔腾汹涌，拍击河岸，发出一阵阵骇人的轰响。这里
恰缝河湾，河床较窄，河谷上并无桥梁，只有三根粗藤条横跨两岸，这端绑在一
棵大树上，似可攀援而过。
LONG );
	set("objects", ([
	   "/d/dali/npc/lieren": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "northeast"  : "/d/dali/cangshanzhong",
	    "west"       : "/d/dali/heshang",
	]));
	setup();
	replace_program(ROOM);
}

