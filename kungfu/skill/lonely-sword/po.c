// po.c ���¾Ž�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        string *learned;
        object weapon, weapon2;
        string type,perform_type;
        mapping prepare;
        int n, tp;
        int skill, ap, dp, damage, ss;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("lonely-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("���¾Ž�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("sword") != "lonely-sword") 
                return notify_fail("��û���ö��¾Ž����޷�ʹ�þŽ����У�\n");

        if (skill < 50)
                return notify_fail("��Ķ��¾Ž��ȼ�������������������\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query("neili") < 200)
                return notify_fail("�������������\n");
        weapon2 = target->query_temp("weapon");
        prepare = target->query_skill_prepare();
        if (weapon2) type = weapon2->query("skill_type");
        else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
        else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
        else if (sizeof(prepare) == 2) 
                type = (keys(prepare))[target->query_temp("action_flag")];

        ap = me->query_skill("sword");
        tp = me->query_temp("apply/attack");

        learned = me->query("can_perform/lonely-sword");
        if (arrayp(learned) && member_array(type, learned) != -1)
                ap *= 2;

        ss = 0;

        dp = target->query_skill(type, 1) * 2 + ss * 2;

        switch(type)
        {
                case "sword":
                        perform_type = "����бб�̳�����ʽȫȻ�����·���";  //�ƽ�ʽ
                        break;
                case "blade":
                        perform_type = "ҡҡ�λδ�ȥ�����ϻ�û��־�����";  //�Ƶ�ʽ
                        break;
                case "staff":
                case "strike":
                case "club":
                        perform_type = "ȫ���˶������У�����һ����бб������";  //��ǹʽ
                        break;
                case "hammer":
                case "dagger":
                        perform_type = "�������շ�ײ��������մ����ִ̳���";  //�Ʊ�ʽ
                        break;
                case "unarmed":
                case "finger":
                case "claw":
                case "hand":
                case "cuff":
                        perform_type = "�����������ó�����â��ӭ�Ŷ����Ʒ缲�̶�����";  
//����ʽ
                        break;
                case "throwing":
                        perform_type = "ˢˢˢ������ȫ��ϣ��Źֵķ�λ����������";  //�Ƽ�ʽ
                        break;
                case "whip":
                        perform_type = "�����������������������������������";  //����ʽ
                        break;
                case "force":
                        perform_type = "�����������ȥ��������ָ������Ю�缲�̶�����";  //����ʽ
                        break;
                default:
                        perform_type = "�����һ����裬���к����š������ذ���塻֮�࣬";  
//����ʽ
                        break;
        }

        if (ap / 2 + random(ap) + random(tp * 3 / 2) > dp || !living(target))
        {
                msg = HIC "$N" HIC "���е�" + weapon->name() + HIC
                      "������������дӳ��䲻��ķ�λֱָ$n" HIC +
                      to_chinese(type)[4..<1] + "�е�������\n" NOR;
                n = 3 + random(5);
                if (ap / 3 + random(ap) + random(tp * 3 / 2) > dp || !living(target))
                {
                        msg += HIY "$n" HIY "���һ��������֮������������$N" HIY "������" +
                               chinese_number(n) + "����\n" NOR;
                        message_combatd(msg, me, target);
                        while (n-- && me->is_fighting(target))
                        {
                                if (! target->is_busy() && random(2))
                                        target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        if (weapon2 && type != "pin")
                        {
                                msg = HIW 
"\n����"+me->name()+"����һ������"+weapon->name()+HIW""+perform_type+"\n"NOR;
                                msg += HIY 
"\n$n�����й��죬����Ī������䣬ͻ�������ʹ������"+weapon2->name()+
                                      HIY "��Ҳ����ס�����ַ����գ�\n" NOR;
                                weapon2->move(environment(me));
                                target->reset_action();
                                target->receive_damage("qi", ap + random(ap/2), me);
                                target->receive_wound("qi", ap + random(ap/2), me);
				str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
				msg += "($n"+str+")\n";
                        } else
                        {
                                msg = HIW "\nֻ��"+me->name()+"�����ᶶ������"+
					weapon->name()+HIW""+perform_type+"\n" NOR;
                                msg += HIM "\n$n�;���ʹ���ģ���Ȼ�����Լ����ƾ��ѱ�"+
					weapon->name()+HIM"���������ɵð���ʹ�У�\n"NOR;
                                target->receive_damage("qi", ap + random(ap), me);
                                target->receive_wound("qi", ap + random(ap), me);
				str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
				msg += "($n"+str+")\n";
                        }
			target->start_busy(1);
                } else
                {
                        msg += HIY "$n" HIY 
"�����й��죬��֪�����æ��æ���ҵĳ��еֵ���һʱ����Ͼ������\n" NOR;
                        target->start_busy(4 + random(skill / 100));
                }
                me->start_busy(2 + random(2));
        } else
        {
                msg = HIC "$N" HIC "�������е�" + weapon->name() + HIC "��������ָ��"
                      "����$n" HIC "���ص��쳣���ܣ�$N" HIC "һʱ��Ȼ�޷��ҵ�������\n" NOR;
                me->start_busy(3 + random(2));
                target->start_busy(1);
        }

        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-100);
        return 1;
}


