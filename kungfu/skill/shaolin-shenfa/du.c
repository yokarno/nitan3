#include <ansi.h>

#define FEI "��" HIY "һέ�ɽ�" NOR "��"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if (userp(me) && ! me->query("can_perform/shaolin-shenfa/du"))
                return notify_fail("��û���ܵ�����ָ�㣬��ʱ������ʩչ" FEI "��\n");

        if ((int)me->query_temp("dujiang"))
                return notify_fail("���Ѿ�����" FEI "�ˡ�\n");

        if ((int)me->query_skill("shaolin-shenfa", 1) < 150)
                return notify_fail("������������ȼ�����������ʩչ" FEI "��\n");

        if ((int)me->query_dex() < 33)
                return notify_fail("�����������������ʩչ" FEI "��\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ" FEI "��\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" FEI "��\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ����������ʩչ" FEI "��\n");

        if ((int)me->query("neili") < 250)
                return notify_fail("���ʱ���������㣬����ʩչ" FEI "��\n");

        msg = HIY "$N" HIY "��������棬ʩչһέ�ɽ������Ծ�����ζ�ʱ����������硣\n\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("shaolin-shenfa", 1);
        cnt = (int)((int)me->query_condition("drunk") / 3);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->set_temp("dujiang", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        me->add("neili", -200);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("dujiang"))
        {
                me->add_temp("dex", -amount);
                me->delete_temp("dujiang");
                tell_object(me, "���" FEI "������ϣ��������ջص��\n");
        }
}
