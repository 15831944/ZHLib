// zuida.c ������� �������
//update by cpu 2002
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;	
  	string msg;
	int count, count1,  skill,i;
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

	
	if (! me->is_fighting(target))
	        return notify_fail("���������ֻ����ս����ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_str() < 25)
		return notify_fail("�����ڵı���������Ŀǰ����ʹ�ô˾�����\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

        if ((int)me->query_skill("yijinjing",1) < 150 &&
           (int)me->query_skill("jiuyang-shengong",1) < 150 &&
           (int)me->query_skill("shaolin-xinfa",1) < 150 &&
           (int)me->query_skill("hunyuan-yiqi",1) < 150)
                return notify_fail("������ֱ����ڹ���򲻹�������ʩչ���������\n");	
         
	if ((int)me->query_skill("club") < 100)
		return notify_fail("��Ĺ�����Ϊ����������ʹ�ô��������\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("����������㣡\n");

        if ((int)me->query_condition("drunk") < 10)
                return notify_fail("�����ĳ̶Ȳ���������ʩչ����������ľ��裡\n");

        skill = me->query_skill("club");

        message_vision(HIY "$N������ֵĲ�������ײײ��$n��ȥ���Կ��ƺ����·��Ĺ���һ����һ���ع���$n���������־�����������򡹣�\n\n"NOR,me,target);
        if (skill / 2 + random(skill) > (int)target->query_skill("parry") * 2 / 3 || !living(target))
        {
                message_vision(HIR "$n" HIR "���˹��д��һ�������ڵ��������޿ɱܣ�\n\n"NOR,me,target);
   
	        //message_combatd(msg, me, target);
        
	
	        
	        count = (int)( (int)me->query_condition("drunk") / 5)+((int)me->query_skill("zui-gun",1)/3);
	
	        me->add_temp("apply/attack", count);

                //message_vision(HIR"$N��Ȼ֮���Ѿ����Լ��ı���������"+me->query_temp("apply/str",1)+HIR"����������"+me->query_temp("apply/dex",1)+HIR"��\n\n"NOR,me,target);

                message_vision(HIB"��������򡹵�һʽ���������ɺͣ�����Ȱ�������ʡ�!\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIM"��������򡹵ڶ�ʽ���������ɹã������������ɲ���!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIC"��������򡹵���ʽ�������ܹ��ˣ�ǧ���������ѡ�!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIW"��������򡹵���ʽ�����������ӣ����������������!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIG"��������򡹵���ʽ�����������룬����������������!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(HIW"��������򡹵���ʽ������������ߵ���ɽ����ء�!\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, weapon, 1);

                message_vision(WHT"��������򡹵���ʽ�������Ź��ϣ�����ױ�����¿��!\n"NOR,me,target);
         	COMBAT_D->do_attack(me, target, weapon, 1);
 
                message_vision(CYN"��������򡹵ڰ�ʽ�����������������������ǧ����!\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, weapon, 1);

 	        
                me->add_temp("apply/attack", -count);

                //message_vision(HIR"$N�ı����½���"+me->query_temp("apply/str",1)+HIR"�����½���"+me->query_temp("apply/dex",1)+HIR"��\n\n"NOR,me,target);

//                target->start_busy(2+random(3));
                me->add("neili", -200);
                me->start_busy(1+random(3));
                target->start_busy(1 + random(2));
        }
        else
        {
                me->add("neili", -100);
                message_vision(HIC"$n�ƺ�������$N��ʽ�ı仯����$N�Ľ���һһ���⣡\n\n"NOR,me,target);
                me->start_busy(2+random(3));
        }
        return 1;
}
