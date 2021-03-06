#include <ansi.h>
inherit ITEM;
int is_enchase_ob() { return 1; }
void create()
{
        set_name(RED "宝石碎片" NOR, ({ "RED jewel1","jewel1" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一片红色的宝石碎片。\n" NOR);
                set("unit", "片");
                set("value", 80000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                    
                set("enchase/type", "all");   // 可镶嵌的道具类型"all"或"sword"或"blade"或"cloth"等
                set("enchase/cur_firm", 90);  // 抗磨损度
                set("enchase/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "str" : 1,           // 增加膂力

                        ////////////////////     兵器特有属性

                        "attack" : 10,       // 攻击等级：+10
                        "damage" : 10,       // 兵器伤害：+10
                        "fire_attack"   : 10, // 火焰攻击

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "str" : 1,           // 增加膂力

                        ////////////////////     防具特有属性

                        "reduce_fire"   : 5, // 化解火焰：5%
                        "reduce_damage" : 5, // 化解伤害：5%
                        "max_neili"     : 2, // 内力上限：+2%

                        "qi_recover_speed"     : 2, // 气血恢复速度：+2%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


