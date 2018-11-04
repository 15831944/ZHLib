#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("������ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹���ʹ���˶�������\n");

        if (me->query_skill("chanhun-suo", 1) < 80)
                return notify_fail("��Ĳ���������̫ǳ��ʹ���˶�������\n");

        if (me->query("neili") < 200)
                return notify_fail("��������������޷�ʹ�ö�������\n");

        msg = HIY "$N" HIY "�����һЦ������" + weapon->name() +
              HIY "���ñ�ֱ������$n" HIY "���󣬿��Ǵ�����;ȴ��ͣ�ͣ�ת��$n"
              HIY "�ؿڻ�ȥ��\n\n" NOR;

        ap = me->query_skill("whip") + me->query_skill("force");
        if(living(target))
              dp = target->query_skill("force") + target->query_skill("parry");
        else  dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                damage = random(ap / 4);
                me->add("neili", -100);
                me->start_busy(1 + random(1));

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           HIR "���$n" HIR "һ���ҽУ�δ�ܿ���$N"
                                           HIR "����ͼ������һ��Ӳ�����ؿڣ���Ѫ��"
                                           "����Ƥ��������\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����һԾ���𣬶�ܿ���"
                       CYN "$P" CYN "�Ĺ�����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
