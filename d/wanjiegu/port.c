// Room: /t/wanjiegu/port.c

inherit ROOM;

void create()
{
        set("short", "���˶�");
        set("long", @LONG
�����ǰ�����׽���һ���ɿڣ������������ڴ�����һ������
�ţ����Ǳ㲻���ٳ˴������ˡ��ű�ʯ����������ؿ�����������
�����˶ɡ���
LONG
        );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"bridge",
            "east" : __DIR__"riverside3",
        ]));

        setup();
        replace_program(ROOM);
}