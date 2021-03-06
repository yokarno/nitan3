// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
	set("short", "二台");
        set("long", @LONG
四季的景色，都在这一山之中。山顶上，白雪皑皑，尚在严冬；山腰里，苍
松翠柏，秋色浓重；山坡上，山花烂漫，如值仲夏；而从那雪峰直垂下来的溪涧
里，冰雪消融，春意盎然。二台以北，有一石洞，人称仙人洞。
LONG );
	set("exits", ([
                "west" : "/d/xingxiu/guozi",
                "eastdown" : "/d/xingxiu/wuchang3",
		"north" : "/d/xingxiu/xrdong",
        ]));
	set("cost", 2);
     set("fjing", 1);
	set("outdoors", "tianshan");
	set("objects", ([
		"/d/xingxiu/obj/xuesang" : 1,
	]) );

	setup();
	replace_program(ROOM);
}
