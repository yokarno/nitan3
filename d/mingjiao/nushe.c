// Room: /d/mingjiao/nushe.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

string look_dui();

void create()
{
    set("short", "����Ů��");
        set("long", @LONG
�߽����Ů�ᣬһ��֬�۵������棬�������ޣ��������ƶ��㣬��õ�壬
��ҹ���㣬��������������λ����б����������ʫ������ȫ�����������ˣ�˭
���뵽�����Ƕ���߳�彭���Ľ���Ů���أ�
LONG );
    set("exits", ([
        "out" : __DIR__"mjdimen1",
    ]));
    set("item_desc",(["dui lian" : (: look_dui :),]));
    set("sleep_room", 1);
    set("no_fight", 1);
    set("no_clean_up", 0);
    setup();
//    replace_program(ROOM);
}

void init()
{
	object me;
	me=this_player();
//    if(me->query("sex")!="Ů��")
	if (me->query("gender")!="Ů��")
	{
		message_vision("$Nֻ���������棬��ǰһ����ѣ����㱼�һŮ���������棬���...\n",me);
		me->move(__DIR__"hsqtan2.c");
	}
}

string look_dui()
{
	return
	"\n"
	"    ����������������������������������������\n"
	"    ����������������������������������������\n"
	"    ����������������ɽ����ˮ����������������\n"
	"    ����������������������������������������\n"
	"    ��������������  ɫ    �⡡��������������\n"
	"    ����������������������������������������\n"
	"    ��������������  ��    ������������������\n"
	"    ����������������������������������������\n"
	"    ��������������  ��    �١���������������\n"
	"    ����������������������������������������\n"
	"    �����������������ꡡ  ��  ��������������\n"
	"    ����������������          ��������������\n"
	"    ������������������    ��  ��������������\n"
	"    ��������������            ��������������\n"
	"    ��������������  �� �� �á���������������\n"
	"    ��������������            ��������������\n"
	"    ����������������������������������������\n";
}