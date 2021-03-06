#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(HIG "神之宝石" NOR, ({ "GRN jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一块闪烁这奇异光芒的绿色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                
                set("enchase/SN", 5);    
                set("can_be_enchased", 1);    // 只有最高等级的宝石才有此标志
		set("magic/type", "magic"); 
		set("magic/power", 15 + random(16)); 
                set("magic/cur_firm", 90);  // 抗磨损度
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "int" : 10,           // 增加智慧

                        ////////////////////     兵器特有属性

                        "suck_jingli"   : 30, // 吸取精力
                        "suck_eff_jing" : 30, // 伤敌精力上限
                        "damage" : 100,       // 兵器伤害：+100

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "int" : 10,           // 增加智慧

                        ////////////////////     防具特有属性

                        "armor"  : 100,       // 防御能力：+100
                        "eff_jing"      : 10, // 精气上限：+10%
                        "max_jingli"    : 30, // 精力上限：+30%

                        "jing_recover_speed"   : 50, // 精气恢复速度: +50%
                        "jingli_recover_speed" : 20, // 精力恢复速度：+20%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

