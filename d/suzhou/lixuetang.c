// Room: /d/suzhou/lixuetang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "��ѩ��");
        set("long", @LONG
��ѩ�����ԡ�������ѩ���͡��ϱ���ѩ��֮�䡣��ǰСԺ�еĺ�ʯ������ţ��
з��ʨ���ܣ�ν��ʨ�Ӿ���ţ��з������������Ȥ��
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"north"  : "/d/suzhou/wenmeige",
	]));
	set("coor/x", 240);
	set("coor/y", -250);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
