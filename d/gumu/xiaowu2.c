
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������С��Ůι��ѵ�����ķ��ݣ��ݽ��Ϲ��źܶ����
���εķ䳲����δ���ţ����ŵõ�һ����۵����㡣
LONG
        );

        set("exits", ([
                "west" : __DIR__"xiaoting",
                "east" : __DIR__"xiaowu3",
        ]));

        set("objects", ([
                "/d/gumu/obj/fengjiang" : 3,
                __DIR__"obj/fengmi" : 1,
        ]));

        setup();
        replace_program(ROOM);
}