// sanhuang.c  三黄宝腊丹   by sinb

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "三黄" HIR"宝腊丹" NOR, ({"baola dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一颗黄黄的药丸，是武当派的疗伤圣药，珍贵无比。\n");
                set("base_unit", "颗");
                set("base_value", 50000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "niuhuang"   : 1,
                                    "dahuang"   : 1,
                                    "shengdi"  : 1,
                                    "lurong"   : 1,
                                    "xiefen"   : 1,
                                    "honghua"  : 1,
                                    "moyao"    : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 150,
                        "medical" : 250,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if (time() - me->query_temp("last_eat/sanhuang") < 120)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        me->set_temp("last_eat/sanhuang", time());

        message_vision(YEL "$N" YEL "吃下一粒" + name() +
                       YEL "，头上"MAG"紫气"YEL"氤氲升起。\n", me);
        tell_object(me, YEL "不一会儿你只觉得精神饱满，神气完足，内力充沛之极。\n" NOR);

        my = me->query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        if (my["jingli"] < my["max_jingli"])
                my["jingli"] = my["max_jingli"];
        if (my["neili"] < my["max_neili"])
                my["neili"] = my["max_neili"];

        me->start_busy(3);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}

