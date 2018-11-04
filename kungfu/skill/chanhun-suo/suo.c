#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int dp;

        if (! target) target = offensive_target(me);

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("chanhun-suo",1) < 50)
                return notify_fail("��Ĳ���������̫ǳ��ʹ�������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹���ʹ�������������\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        msg = HIR "$N" HIR "һ����Ц��ʹ���������������������������Ӱ����$n"
              HIR "ȫȫ���֣�\n\n" NOR;

        if(living(target))
              dp = target->query("combat_exp") / 2;
        else  dp = 0;

        if (random(me->query("combat_exp")) > dp)
        {
                msg += HIY "���$n" HIY "������ɽ������Ĺ������˸����ֲ�����������������ȫ�޷�����\n" NOR;
                target->start_busy((int)me->query_skill("whip") / 22 + 1);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����ͼ������һ�ݣ��ӿ��˹��ơ���\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
