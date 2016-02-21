// po.c ���־�

#include <ansi.h>

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int n;
        int skill, skill2, ap, dp, damage;
        string type;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("never-defeated", 1);

        skill2 = me->query_skill("martial-cognize", 1);

        if (! me->is_fighting(target))
                return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("������ֱֳ��в���ʩչ���־���\n");

        type = weapon->query("skill_type");
        if (me->query_skill(type, 1) < 150)
                return notify_fail("���" + to_chinese(type) + "ˮƽ���ޣ��޷�ʩչ���־���\n");

        if (me->query_skill_mapped(type) != "never-defeated")
                return notify_fail("��û�м��������񹦣��޷�ʩչ���־���\n");

        if (me->query_skill_mapped("force") != "never-defeated") 
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ���־���\n");                 

        if (skill < 100)
                return notify_fail("��Ĳ����񹦵ȼ��������޷�ʩչ���־���\n");

        if (me->query("neili") < 150)
                return notify_fail("����������������\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -100);

        ap = ap_power(me, "force");
        dp = dp_power(target, "parry");

        msg = HIC "$N" HIC "����" + weapon->name() +
              HIC "һ��������ҹ�����ǣ�����ǵصĹ���$n"
              HIC "��û�а���ؿ�ѭ��\n" NOR;
        if (ap * 11 / 20 + random(ap) > dp)
        {
                n = 4 + random(4);
                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "�����м�����׾����ͬ���˼�"
                               "�κ���ʽ��������Ϊ���ң�һʱ����������$N"
                               HIY "��״����" + chinese_number(n) + "�У�\n" NOR;
                        message_combatd(msg, me, target);
                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (random(2) && ! target->is_busy())
					target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        weapon2 = target->query_temp("weapon");
                        if (weapon2 && random(ap) / 2 > dp && weapon2->query("type") != "pin")
                        {
                                msg = HIW "$n" HIW "������ǰ�ۻ����ң����е�" + weapon2->name() +
                                      HIW "һʱ��Ȼ����ס�����ֶ�����\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "$n�����ֵ���һʱ����Ҳ����������\n" NOR;
                        }

                        if (! me->is_fighting(target))
                                // Don't show the message
                                return 1;
                } else
                {
                        msg += HIY "$n" HIY "ֻ���˸������ڵ���ȫȻ�޷�������\n" NOR;
                        target->start_busy(4 + random(skill / 30));
                }
        } else
        {
                msg += HIC "����$n" HIC "һ˿�����������Ż���û��¶�����������\n" NOR;
                me->start_busy(3 + random(2));
        }

        message_combatd(msg, me, target);
        return 1;
}
