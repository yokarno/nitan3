#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(BLU "圣之宝石" NOR, ({ "BLU jewel5","jewel5" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", BLU "一块闪烁这奇异光芒的蓝色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 160000);
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


                            "kar" : 6,           // 增加福源

                        ////////////////////     兵器特有属性

                            "light_attack"  : 60, // 闪电攻击
                            "add_damage"    : 14, // 追加伤害14%
                            "suck_eff_qi"   : 18, // 伤敌气血上限

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                            "kar" : 6,           // 增加福源

                        ////////////////////     防具特有属性

                            "reduce_light"  : 60, // 化解闪电：60%
                            "avoid_poison"  : 60, // 毒性回避：60%
                            "reduce_damage" : 30, // 化解伤害：30%

                            "qi_recover_speed"     : 30, // 气血恢复速度：+30%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

