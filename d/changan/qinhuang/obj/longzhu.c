//mingzhu.c
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIB BLINK "����" NOR, ({ "long zhu" ,"zhu", }) );
        set_weight(100000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���ǿ����ۣ�������ֵ����Ǯ��\n");
                set("value", 1000000);
                set("material", "dainomd");
              }
}
void init()
{
        if (environment()==this_player())
        add_action("do_pushin","pushin");
}
int do_pushin(string arg)
{
        object me=this_player();
        object room=environment(me);
        if(base_name(room) != "/d/changan/qinhuang/dadian3") return 0;
        if (room->query("in_zhu")==2)
                return 0;
        if(!me->query_temp("killer")
        || !me->query_temp("climb")
        || me->query_temp("chan"))
        return 0;
        message_vision("$N����һ��"+query("name")+"������ʯ�ŵĶ��ڡ�\n",me);
        room->add("in_zhu",1);
        if (room->query("in_zhu")==2){
                room->open_door(me,1);
        }
        destruct(this_object());
        return 1;
}
