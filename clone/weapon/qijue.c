
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY "�߾���" NOR, ({ "qijue zhen", "zhen", "needle" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���ƽ��Ƴɵ��룬����һ��ָ���ϡ�\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N�ӿڴ������һ��$n����С��ָ�ϡ�\n");
                set("unwield_msg", "$N�����ϵ�$nժ������\n");
        }
        init_sword(40);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int damage;

        if (victim->query_condition("snake_poison",1)< 50)
        {
                victim->apply_condition("snake_poison", 290);   
                return HIR "$nֻ�����˿���һ�飡\n" NOR;
        }
}
