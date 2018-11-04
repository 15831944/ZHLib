// ���ɷ�

#include <ansi.h>

int perform(object me)
{
	int skill;
	string msg;

	if (! me->is_fighting())
		return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

	if ((int)me->query_skill("shedao-qigong", 1) < 60)
		return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("���Ѿ����þ�ƣ���ߣ����������ˡ�\n");

	if ((int)me->query_temp("chang"))
		return notify_fail("���Ѿ���ʹ�ó��ɷ��ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -500);

	message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
                        "֮���书�����\n" NOR, me);

	me->add_temp("apply/attack", skill/6);
	me->add_temp("apply/dodge", skill/6);
	me->add_temp("apply/defense", skill/6);
	me->set_temp("chang", 1);

        call_out("remove_effect", skill/10, me, skill/6);

	return 1;
}

void remove_effect(object me, int extra)
{
        if (!me) return;

        me->add_temp("apply/attack", -extra);
        me->add_temp("apply/defense", -extra);
	me->add_temp("apply/dodge", -extra);

        me->delete_temp("chang");
        message_vision(CYN"$Nֻ�������ݽߣ��ڸ������Ҳ�޷�����ȥ�ˡ�\n"NOR,me);
}
