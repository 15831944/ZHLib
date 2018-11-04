// xiantian-gong.c ���칦
#include <combat.h>
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "duanshi-xinfa" ||
               force == "quanzhen-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xiantian-gong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("gender") == "����" &&
            (int)me->query_skill("xiantian-qigong", 1) > 49)
                return notify_fail("���޸����ԣ������ѵ����޷�ѧϰ����������칦��\n");

        if ((int)me->query_skill("force", 1) < 110)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("���칦ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
	object weapon1 = me->query_temp("weapon");
	object weapon2 = victim->query_temp("weapon");
	int ap, dp;
	string result;

	if ( (int)victim->query_skill("xiantian-gong", 1) < 200 ) return damage;
	if (victim->query("neili") < 1000) return damage;

	dp = COMBAT_D->skill_power(victim, "force", SKILL_USAGE_DEFENSE);
	if (objectp(weapon2) && (string)weapon2->query("skill_type") == "sword" ) {
		if ( victim->query_skill_mapped("parry") != "quanzhen-jian" )
			return damage;
		dp /= 3;
		dp += COMBAT_D->skill_power(victim, "parry", SKILL_USAGE_DEFENSE)/2;
	} else if (!objectp(weapon2) ) {
		if ( victim->query_skill_prepared("strike") != "haotian-zhang" &&
                     victim->query_skill_prepared("strike") != "chongyang-shenzhang" &&
                     victim->query_skill_prepared("cuff") != "chunyang-quan" &&
                     victim->query_skill_prepared("cuff") != "kongming-quan" )
			return damage;
		dp += COMBAT_D->skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
	} else return damage;

	ap = COMBAT_D->skill_power(me, "force", SKILL_USAGE_ATTACK);
	if (objectp(weapon1))
		ap += COMBAT_D->skill_power(me, weapon1->query("skill_type"), SKILL_USAGE_ATTACK);
	else
		ap *= 2;

	ap /= 100;
	dp /= 100;

	if ( random(ap+dp) > ap ) {
		if ( weapon2 && objectp(weapon2) ) {
			if (damage + damage_bonus > 0)
			{
				me->receive_damage("qi", (damage + damage_bonus)/2, victim);
				result = HIG"ֻ��$n���н������һճһ����$N������ͨͨ���ڿմ���$P�������ͣ�ʧȥƽ�⣬���˸��ӡ�\n"NOR;
				result += "( $N"+ COMBAT_D->status_msg((int)me->query("qi")*100/(int)me->query("max_qi")) + " )\n";
				me->start_busy( 2+random(2) );
				victim->add("neili",-100);
			}
			else
		        {
				result = "ֻ��$n���н������һճһ����$N������������Ϊ���Ρ�\n";
				victim->add("neili",-60);
			}
		}
		else if( victim->query_temp("powerup") || victim->is_busy() )
		{
			if( !weapon1 )
			{
				result = HIM"ֻ��$n���커������Ȼ��Ȼ��������$N����������������$P�Լ���\n"NOR;
				if (damage + damage_bonus > 0)
					me->receive_damage("qi", (damage + damage_bonus)/2, victim);
				result += "( $N"+ COMBAT_D->status_msg((int)me->query("qi")*100/(int)me->query("max_qi")) + " )\n";
				victim->add("neili",-100);
			}
			else
			{
				victim->add("neili",-60);
				result = HIM"ֻ��$n���커������Ȼ��Ȼ��������$N����������һ�ߡ�\n"NOR;
			}
		}
		else return damage;

		damage_bonus = -5000; // just a number negative enough
		return ([ "msg" : result, "damage" : damage_bonus ]);

	} else if( random(ap+dp+dp+dp) > ap ) {

		if (objectp(weapon2)) {
			result = "$n���н�����б����$N�������������˴�롣\n";
			victim->add("neili",-50);
			damage_bonus = 0;
		}
		else if( victim->query_temp("powerup") || victim->is_busy())
		{
			victim->add("neili",-80);
			result = MAG"ֻ��$n���커������Ȼ��Ȼ��������$N�Ĺ�����Ϊ���Ρ�\n"NOR;
			damage_bonus = -5000;
		}
		else return damage;

		return ([ "msg" : result, "damage" : damage_bonus ]);
	} else if( random(ap+dp+dp+dp+dp) > ap ) {

		 if( victim->query_temp("powerup") || victim->is_busy() )
		{
			victim->add("neili",-50);
			result = MAG"ֻ��$n���커������Ȼ��Ȼ�������ֿ�$N�Ĺ�����\n"NOR;
			damage_bonus = 0;
		}
		else return damage;

		return ([ "msg" : result, "damage" : damage_bonus ]);
	} else
		return damage;
}

string exert_function_file(string func)
{
        return __DIR__"xiantian-gong/" + func;
}
 mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name() +"���ڵ��£�ͷ��һ���������������ϣ���������һ�㡣",
"start_self"    : HIY"����ϥ���£��������ˣ������������Ѩ��ת��\n"NOR,
"on_self"       : YEL"�����������񹦣�������ת�����о����ƴ�����ɫ��\n"NOR,
"start_other"   : HIY""+me->name()+"��ɫ��ͣ�ͷ��һ����������������ɫ������ת��\n"NOR,
"finish_self"   : HIY"��е�����������תȫ�����ް���谭��������ȻȬ��������վ��������\n"NOR,
"finish_other"  : me->name()+"΢΢һЦ��վ����������ɫ���󣬾�����ܡ�\n",
"unfinish_self" : "�����˹����˼䣬����������飬�������̣�ֻ���ݻ����ˣ�վ��������\n",
"unfinish_other": me->name()+"����վ��΢΢��������ɫ��Щ�԰ס�\n",
"halt_self"     : "�㽫���������ջص��վ��������\n",
"halt_other"    : me->name() +"����һ������վ�������������ƺ����Ϻ��˲��١�\n",
        ]);
}

