// kuai.c ����ȭ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����ȭ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ȭ��ֻ�ܿ���ʹ�á�\n"); 

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
                
        if ((int)me->query_skill("hujia-quan", 1) < 80)
                return notify_fail("��ĺ���ȭ��������죬����ʹ�á���ȭ����\n");

        if (me->query("neili") < 80)
                return notify_fail("�����������������޷�ʹ�á���ȭ����\n");

        msg = HIG "$N" HIG "�ݲ���ǰ��ȭ�е�������ʱ��$n"
              HIG "��������ʮ�С�\n" NOR;

        me->add("neili", -40);

        if (living(target))
                dp = target->query("combat_exp") / 3;
        else    dp = 0;

        if (random(me->query("combat_exp")) > dp)
        {
                msg += HIR "���$p" HIR "�޷�����$P" HIR "��ʽ�е���ʵ��"
                       "������æ���ң������ֵ���\n" NOR;
                target->start_busy((int)me->query_skill("cuff") / 25 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "�����У�����һ����"
                       "�ܿ����Ⱪ������һ��ȭӰ��\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

