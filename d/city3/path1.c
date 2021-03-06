// Room: path1.c
// Date: Feb.14 1998 by Java

inherit BUILD_ROOM;
string look_gaoshi();
void create()
{
	set("short", "溪岸小路");
        set("long", @LONG
你走在浣花溪岸的小路上，浣花溪水晶莹剔透，岸草如茵，远远就能闻到水
气的清香。许多睡莲散布在溪岸附近，水面飘著数不尽的浮萍，浮萍下有不少艳
红锦鲤穿梭来去。溪岸小路随溪流曲折盘绕，芳草没足，花飘似海，使人不饮自
醉。古人所谓 "如行春郊" ，诚不我欺。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
		"north"  : "/d/city3/path2",
		"east"   : "/d/city3/nanheqiaow",
	]));
        set("max_room", 4);
	set("no_clean_up", 0);
	set("coor/x", -480);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
}
