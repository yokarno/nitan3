// mtroad4.c  ����

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ï�ܵ�ɭ�֡����ܶ���������ĳ��ݣ�һ����ɭ�ֲ�����
�ա�Զ����ʱ����Ұ�޵ĺ��У���ʵ�ڲ��������������
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : __DIR__"mtroad3",
            "west"  : __DIR__"mtroad5",
            "north" : __DIR__"mtroad6",
            "south" : __FILE__,
        ]));
        setup();
        replace_program(ROOM);
}
