//Room: nan-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "长安南城门");
        set("long", @LONG
长安城的南城门。这里的护城河既深又阔，而且城高墙厚，有一夫当关，万
夫莫开之势，城内还驻扎了两营士兵，远看军营延绵，旌旗似海，颇具慑人之势，
仰望城楼，只见城楼高处满布哨兵，剑拔驽张，士气昂扬，从这里出去不远就是
兵家要地武功镇。
LONG );
        set("exits", ([ /* sizeof() == 2 */ 
        	"southwest" : "/d/quanzhen/guandao1",
        	"north" : "/d/changan/nanan-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
        	"/d/changan/npc/wujiang" : 1,
        	"/d/changan/npc/guanbing": 2,
        ]));

        set("outdoors", 1);
        set("coor/x", -400);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
