inherit ROOM;

void create()
{
        set("short", "���칬");
        set("long", @LONG
�����ѽ��䵱������ֻ��ʯ��ֱ�ʣ�Σ�Ÿ��������Ը���
����������������
LONG);
        set("objects", ([
                CLASS_D("wudang") + "/qingxu": 1,
        ]));

        set("exits", ([
                "northdown" : __DIR__"hutouyan",
                "south" : __DIR__"huixianqiao",
        ]));
        set("outdoors", "wudang");
	set("coor/x", -350);
	set("coor/y", -370);
	set("coor/z", 150);
	setup();
        replace_program(ROOM);
}