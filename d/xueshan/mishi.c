inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ��С���䡣ʲô������û�У�ֻ��һ���ں�����С
���ڣ���֪�����涼������Щʲô��
LONG);
        set("exits", ([
                "south" : __DIR__"midao",
                "up" : "/d/city/guangchang",
        ]));
        setup();
        replace_program(ROOM);
}