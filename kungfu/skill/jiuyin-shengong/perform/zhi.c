// zhi.c ������ָ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jiuyin-shengong", 1);

        if (! me->is_fighting(target))
                return notify_fail("������ָֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (skill < 100)
                return notify_fail("��ľ����񹦵ȼ��������޷�ʩչ������ָ��\n");

        if (me->query("neili") < 100)
                return notify_fail("����������������\n");

        ap = skill * 7 / 4 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

        msg = HIY "$N" HIY "���ֳ�ָ�����������ƺ�������$n"
              HIY + "��ʽ�е�������\n" NOR;
        if (ap / 2 + random(ap * 2) > dp)
        {
                n = 4 + random(4);
                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "����ָ�����ޱȣ�ȫȻ�޷��ֵ�������֮������������$N"
                               HIY "��������" + chinese_number(n) + "ָ��\n" NOR;
                        message_combatd(msg, me, target);
                        while (n-- && me->is_fighting(target))
                        {
				if (! target->is_busy())
                                	target->start_busy(1);
                                COMBAT_D->do_attack(me, target, 0, 0);
                        }

                        weapon = target->query_temp("weapon");
                        if (weapon && random(ap) / 2 > dp && weapon->query("type") != "pin")
                        {
                                msg = HIW "\n$n" HIW "������ǰ�ۻ����ң����е�" + weapon->name() +
                                      HIW "һʱ��Ȼ����ס�����ֶ�����\n" NOR;
                                weapon->move(environment(me));
                        } else
                        {
                                msg = HIY "\n$n�����ֵ���һʱ����Ҳ����������\n" NOR;
                                me->start_busy(1);
                                return 1;
                        }
                } else
                {
                        msg += HIY "$n" HIY "�������룬��æ�ֵ���ȫȻ�޷�������\n" NOR;
			if (! target->is_busy())
                        	target->start_busy(4 + random(skill / 20));
                }
                me->start_busy(1);
        } else
        {
                msg += HIC "����$n" HIC "�����Ż�����¶���������\n" NOR;
                me->start_busy(3 + random(2));
		if (! target->is_busy())
                	target->start_busy(1);
        }

        message_combatd(msg, me, target);
        return 1;
}
