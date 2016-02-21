#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(RED "神之宝石" NOR, ({ "RED jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一块闪烁这奇异光芒的红色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                
                set("enchase/SN", 7);    
                set("can_be_enchased", 1);    // 只有最高等级的宝石才有此标志
		set("magic/type", "magic"); 
		set("magic/power", 15 + random(16)); 
                set("magic/cur_firm", 90);  // 抗磨损度
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "str" : 10,           // 增加膂力
                        "dex" : 10,           // 增加根骨

                        ////////////////////     兵器特有属性

                        "attack" : 100,        // 攻击等级：+100
                        "damage" : 100,        // 兵器伤害：+100
                        "fire_attack"   : 100, // 火焰攻击
                        "perferm_ap"    : 12,   // 绝招命中：+12%
                        "add_damage"    : 10, // 追加伤害10%

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "str" : 10,            // 增加膂力
                        "dex" : 10,            // 增加根骨
                        ////////////////////     防具特有属性

                        "reduce_fire"   : 90, // 化解火焰：90%
                        "reduce_damage" : 90, // 化解伤害：90%
                        "max_neili"     : 20, // 内力上限：+20%
                        "perform_dp"    : 10,  // 绝招防御：+10%

                        "qi_recover_speed"     : 50, // 气血恢复速度：+50%
                        "neili_recover_speed"   : 5, // 内力恢复速度：+5%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


