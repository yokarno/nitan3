// ���䶾ҩ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object du;
        int damage;
        int ap, dp;
        string msg;

        if (environment(me)->query("no_fight"))
                return notify_fail("���ﲻ��ս�����㲻����ʹ�ö������ˡ�\n");

        if (! target || me == target)
                return notify_fail("���빥��˭��\n");

        if (target->query_competitor())
                return notify_fail("�����ʱ���������������Ľ�����\n");

        if ((int)me->query_skill("poison", 1) < 80)
                return notify_fail("��Ļ���������򲻹���\n");

        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�������������㣬���ܵ��䶾ҩ��\n");

        if (! objectp(du = me->query_temp("handing")))
                return notify_fail("�����׼��(hand)�ö�ҩ��˵��\n");

        if (! mapp(du->query("poison")))
                return notify_fail(du->name() + "�ֲ��Ƕ�ҩ�����ҵ�ʲô��\n");

        msg = CYN "$N" CYN "��ת��������������һЩ" + du->name() +
              CYN "��׼$n" CYN "���˹�ȥ��\n" NOR;
        me->start_busy(2 + random(2));
        me->add("neili", -300);
        if (living(target))
                dp = target->query("neili");
        else    dp = 0;

        if (me->query("neili") / 2 + random(me->query("neili")) < dp)
        {
                msg += WHT "Ȼ��$n����һ������$N�������" + du->name() +
                       WHT "Ϥ���𿪡�\n" NOR;
        } else
        {
                ap = me->query_skill("poison", 1) / 2 +
                     me->query_skill("force");
                if (ap / 2 + random(ap) < target->query_skill("dodge") * 3 / 2)
                {
                        msg += WHT "$n���Ʋ����æ��Ų���Σ��ܿ���$N�Ĺ�����\n" NOR;
                        target->start_busy(1);
                } else
                {
                        msg += GRN "$n��æ�����������Ȼ����΢΢һ�����顣\n" NOR;
                        target->affect_by(du->query("poison_type"), du->query("poison"));
                        target->start_busy(1);
                }
        }

        du->add_amount(-1);
        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}
