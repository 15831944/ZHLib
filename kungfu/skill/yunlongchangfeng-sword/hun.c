// hun.c ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("yunlongchangfeng-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("sword") != "yunlongchangfeng-sword") 
                return notify_fail("��û�����������罣�����޷�ʹ������������У�\n");

        if (skill < 100)
                return notify_fail("����������罣���ȼ�������������������\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "�������������������$n�;���ȥ������" + weapon->name() + 
               HIY "˲�����������У���ͬ��籩�ꡣ\n" NOR;

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIY "\n���ͻȻ���������������ռ�ž���������������˸е�������\n"
              "$N" HIY "�ڿ���Ʈ�����������Ž�⣬ͻȻ" + weapon->name() + HIY "��һ�����磬������$n��\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "����ʧ�룬���м��æ�ֵ���ȴΪʱ������\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "�������Σ����ձܿ���ȴҲ����һ���亹��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}

