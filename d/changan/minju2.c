//Room: minju2.c

inherit ROOM;

void create ()
{
        set ("short", "民居");
        set("long", @LONG
房间里甚是宽敞，里面摆设朴素而自然，左侧是一个古色古色的精雅梳妆台，
前面摆有两张红木圆椅。右侧墙壁上挂有一幅美女抚琴图，上面配有几行笔迹清
秀的隶体小字，内侧则是一张红色帐幔垂挂的低矮木榻。
LONG );
        set("exits", 
        ([ //sizeof() == 1
        	"north" : "/d/changan/huarui2",
        ]));

        set("coor/x", -420);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
