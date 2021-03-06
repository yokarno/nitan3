// tianwai.c 天外清音

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
                return notify_fail("「天外清音」只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("bibo-shengong", 1) < 120)
                return notify_fail("你的碧波神功等级不够, 不能使用「天外清音」！\n");

        skill = me->query_skill("yuxiao-jian",1);

        if (skill < 100)
                return notify_fail("你的玉箫剑法等级不够, 不能使用「天外清音」！\n");

        if (me->query("neili") < 200)
                return notify_fail("你的真气不够，无法运用「天外清音」！\n");

        msg = HIC "$N" HIC "一声清啸，剑发琴音" + weapon->name() +
              "闪动不止，剑影如夜幕般扑向$n" HIC "。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("force");
        if (dp < 1) dp = 1;
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -120);
                qi_wound = (int)me->query_skill("sword") +
                           (int)me->query_skill("bibo-shengong", 1);
                qi_wound = qi_wound / 2 + random(qi_wound / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 66,
                                           HIR "$n" HIR "顿时觉得眼前金光乱闪动，双耳嗡嗡"
                                           "内鸣，不知那里一阵刺痛如针扎一般！\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                me->add("neili", -50);
                msg += HIG "可是$n" HIG "宁心静气，随手挥洒，将$N"
                       HIG "的招数撇在一边。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
