//Room: zubaohang.c

inherit ROOM;

void create ()
{
        set ("short", "珠宝行");
        set("long", @LONG
珠宝行中珠光宝气四射，眩的人有些睁不开眼睛。精致的长柜中陈设着各类
首饰珠宝玉器，几个老行家正陪着客人挑选所需珠宝。一个雕花木架上摆着颗三
尺多高的玉树，珍贵之外又透着淡雅秀丽，曲折含蓄之气。
LONG );
        set("exits", ([
        	"south" : "/d/changan/yongtai-beikou",
        ]));
        set("objects", ([
        	"/d/changan/npc/jinfuhuan"  : 1,
        ]));

        set("coor/x", -440);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
