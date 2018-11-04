// inspire.c

#include <ansi.h>

int exert(object me, object target)
{
        string force;

        if (! me->query("breakup"))
                return notify_fail("�㻹û����������������������ľ��ϡ�\n");

        if (me->is_busy())
                return notify_fail("����æ������ͷ��������˵��\n");

	if (me->is_fighting())
		return notify_fail("����������ս���У����ǵȴ�������˵�ɣ�\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("�ȼ�����������ڹ���\n");

	if ((int)me->query_skill(force, 1) < 200)
		return notify_fail("���" + to_chinese(force) + "��Ϊ��������\n");

        if ((int)me->query("eff_jing") >= (int)me->query("max_jing"))
                return notify_fail("�����ھ���������ʲô�ü����ģ�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query("eff_jing") < (int)me->query("max_jing") / 3)
		return notify_fail("��ľ�����̫�أ�������������Լ���\n");

	message_vision(HIW "$N" HIW "��Ŀڤ�񣬻����ĺ������ɣ���ͷ��������㺹�飬�漴�����������ڶ���\n"
                       HIY "$N" HIY "����˫Ŀ������������䣬������ȥ�ö��ˡ�\n" NOR,
		       me);

	me->receive_curing("jing", 5 + (int)me->query_skill("force") / 6);
	me->add("neili", -180);
	me->start_busy(1);

	return 1;
}
