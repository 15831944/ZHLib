// chan.c ���±޷������ơ���

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int bs;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "whip")
                return notify_fail("��û�����ű��ӡ�\n");
                
        if (me->query_skill_mapped("force") != "hunyuan-yiqi" && 
            me->query_skill_mapped("force") != "yijinjing" && 
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong") 
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ�����ơ�����\n"); 

        if (me->query("neili") < 80)
                return notify_fail("�����������������޷�ʩչ�����ơ�����\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷����޷�ʩչ�����ơ�����\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ�������ʩչ�����ơ�����\n");

        msg = HIC "$N" HIC "ʹ�����±޷������ơ���������������ͼ��$n"
              HIC "��ȫ�����������\n";

        me->start_busy(1);
        bs = (int)me->query_skill("riyue-bian") / 20 + 2;
        if (bs > 8)  bs = 8;

        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2)
        {
                msg += HIR "���$p" HIR "��$P" HIR "���˸����ֲ�����\n" NOR;
                target->start_busy(bs);
        } else {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ��С��Ӧ�ԣ���û���ϵ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

