//Room: fufeng2.c

inherit ROOM;

void create ()
{
        set ("short", "扶风道");
        set("long", @LONG
扶风道是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。
LONG );
        set("exits", 
        ([ //sizeof() == 2
        	"south" : "/d/changan/fufeng3",
        	"north" : "/d/changan/fufeng1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -420);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
