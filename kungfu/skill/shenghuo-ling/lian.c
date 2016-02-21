// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define LIAN "��" HIW "������" NOR "��"

inherit F_SSERVER;
#include <balance.h>

string final(object me, object target, int damage);

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (userp(me) && ! me->query("can_perform/shenghuo-ling/lian"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" LIAN "��\n"); 

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenghuo-ling", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" LIAN "��\n");

        if (skill < 150)
                return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" LIAN "��\n");

        if (me->query("max_neili") < 1600 )
                return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" LIAN "��\n");

        if (me->query("neili") < 350 )
                return notify_fail("�����������������ʹ��ʥ���֮" LIAN "��\n");

        if (me->query_skill_mapped("sword") != "shenghuo-ling") 
                return notify_fail("��û�м���ʥ���������ʹ��ʥ���֮" LIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����ͷ���$n" HIW "��ǰ����Ȼʹ��ʥ��"
              "�֮���������" + weapon->name() + NOR + HIW "����"
              "��������ʽ�����ޱȡ�\n" NOR;

        damage = da_power(me, "sword");
        
        ap = ap_power(me, "sword");
        dp = dp_power(target, "dodge");


        if (ap * 11 / 20 + random(ap) > dp)
        {
                me->add("neili", -300);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,                
                       damage, 0, (: final, me, target, damage :));
                       
        }
        else
        {
                me->add("neili", -100);
                msg += CYN "$n" CYN "����ǰ�����������æ����������ǿ"
                      "�ֵ���������������ò�����������$N" CYN "��"
                      "����Χ֮�⡣\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int damage)
{

       target->receive_damage("jing", damage / 2);
       target->receive_wound("jing", damage / 4);
       target->start_busy(1);

       return HIR "$n" HIR "ֻ����ǰ���������ͻ"
              "Ȼ$N" HIR "˫�ֳ������Լ���ǰ������̫��Ѩ��"
              "ʱһ���ʹ��\n" NOR;
}