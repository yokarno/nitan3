// dahuan-dan.c �󻹵�

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("�󻹵�", ({"dahuan dan", "dahuan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���Ϻ쾧���Ĵ󻹵����˵���������ҩ����"
			    "�߹�������Ч�ޱȡ�\n");
		set("value", 10000);
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	int force_limit, neili_limit;

	force_limit = me->query_skill("force")*10;
	neili_limit = me->query("max_neili");
	
	me->start_busy(2);
	if ((int)me->query_condition("bonze_drug" ) > 0)
	{
		me->add("max_neili", -1);
		message_vision(HIR "$N" HIR "����һ�Ŵ󻹵���ֻ����ͷ"
			       "�ؽ��ᣬҡҡ������ԭ����ʳ̫��̫�࣬ҩ"
			       "Ч�ʵ��䷴��\n" NOR, me);
	} else
	if (neili_limit <= force_limit)
	{
		me->add("max_neili", 1);
		message_vision(HIG "$N" HIG "����һ�Ŵ󻹵���ֻ��������"
			       "����ԴԴ���������Ϲ���������͸ʮ����¥��"
			       "�鲼��������ȫ��������Ȼ��ߣ�\n" NOR, me);
	}

	me->apply_condition("bonze_drug", 60);
	destruct(this_object());
	return 1;
}
