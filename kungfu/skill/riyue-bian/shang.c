// shang.c ���־�

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
                return notify_fail("�����־���ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ�����־�����\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("riyue-bian", 1) < 180)
                return notify_fail("������±޷���Ϊ������Ŀǰ����ʹ�����־���\n");

        if (me->query("neili") < 400)
                return notify_fail("��������������޷�ʹ�����־���\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷�������ʹ�����־���\n");

        msg = HIY "$N" HIY "��Ȼ��Ц�����е�" + weapon->name() +
              HIY "һ����ʱ��ñ�ֱ����ͬ����һ��ɴ���$n" + HIY "��\n" NOR;

        ap = me->query_skill("whip") + me->query_skill("force");
        dp = target->query_skill("force") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = ap + random(ap / 2);
                me->start_busy(1 + random(3));
                me->add("neili", -300);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "ֻ��$p" HIR "һ���ҽУ�" + weapon->name() +
                                           "��Ȼ����$p" + HIR "�����ϣ������Ѿ�"
                                           "�Դ�����Ѫ�ɽ����ߣ��Ҳ����ԣ�\n" NOR);
                target->start_busy(1);
        } else
        {
                me->add("neili", -100);
                me->start_busy(2 + random(3));
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

