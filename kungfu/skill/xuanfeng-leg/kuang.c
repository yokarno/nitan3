// kuangfeng.c  狂风绝技

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i;
        int extra;
i = me->query_skill("bibo-shengong", 1) * 3 / 10;
        if( !target ) target = offensive_target(me);
        if( !me->is_fighting() )
                return notify_fail("「狂风绝技」只能在战斗中对对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("「狂风绝技」开始时不能拿着兵器！\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功水平不够！\n");

        if ((int)me->query_skill("luoying-shenzhang", 1) < 100 ||
            me->query_skill("xuanfeng-leg",1) < 100)
                return notify_fail("你的腿掌功夫还不到家，无法使用狂风绝技！\n");

        if (me->query_skill_prepared("unarmed") != "xuanfeng-leg")
                return notify_fail("你没有准备旋风腿法，无法施展狂风绝技。\n");

        msg = HIY "$N" HIY "使出桃花岛绝技「狂风绝技」，身法飘忽"
              "不定，有若天仙！\n" NOR;
         message_vision(msg, me);
         me->add_temp("apply/attack", i);
        {
                msg = YEL  "\n$N" YEL"聚力于左掌，右腿一脚跟着踢出！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM  "人影中，" HIM "$N" HIM "翻身而起，左掌大力得挥向$n！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = YEL "\n$N" YEL "见" YEL "$n" YEL "门户大开，暗运内力，双腿连环踢向" YEL "$n！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM  "$N" HIM "越战越勇，周围骤起一阵旋风，使得" HIM "$n" CYN "看不清方向！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = YEL "\n$N" YEL "如星光乍现，右掌略带悠然之色轻拍" YEL "$n！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                msg = HIM "$N" HIM "长啸一声，面如赤发，忽然转到" HIM "$n" HIM"身后，反手又是一掌！\n"NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        }
        me->add("neili", -100);
        me->start_busy(1 + random(2));
        me->add_temp("apply/attack", -i);
        return 1;
}
