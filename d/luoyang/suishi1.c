inherit ROOM;

void create()
{
	set("short", "��ʯ·");
	set("long", @LONG
һ����ʯС·�����¹��꣬·�濴���������ɾ��ģ�һЩ����������
�Լ��ֵ��߲˵������������˲��Ǻܶ࣬ߺ����������Զ��·������һ��
����ؤ���������޼ҿɹ�������Ĵ��ε�����������Կ�����������һ
�档·�����߶��ǵ��ص�һЩ��լ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"south" : __DIR__"suishi2",
  		"north" : __DIR__"eroad5",
	]));

	set("coor/x", -120);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}