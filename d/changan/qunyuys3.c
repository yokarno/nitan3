//Room: qunyuys3.c

inherit ROOM;

void create()
{
        set("short", "Ⱥ��¥����");
        set("long", @LONG
һ�����ҡ����з���һ�Ŵ󴲣����������廨�Ľ�������ͷ������������£�
�������������һ��Ϸˮԧ�죬��ɫ���ã�����������ϵ���һ�����򣬺�
������һ��������һֻ��ױ���ӡ���ǰ���������廨��Ь��һ���еģ�һ��Ů�ģ�
���Ŷ��á�
LONG );
        set("exits", ([ /* sizeof() == 1 */
        	"east" : "/d/changan/qunyulou2",
        ]));
        set("objects", ([
        	"/d/changan/npc/ziyi" : 1,
        ]) );

	set("coor/x", -400);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}