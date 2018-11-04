//sougu.c �ѹ�ӥצ��

inherit SKILL;
#include <combat.h>
#include <ansi.h>

int next_hit(object me, object victim, object weapon, int damage);

mapping *action = ({
([	"action" : "\n$N��צ�����צѸ��ץ��$n��һ��һʵ������һ�С���צʽ��",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "ץ��",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N����Ʈ��������צƮ�������ô�����˷�����$n���仯��ǧ������һ�С�Ʈצʽ��",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "ץ��",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "Ʈצʽ"
]),
([	"action" : "\n$N�������˫צ�繳�����ź�Х�ľ���ֱ��$n��ȥ����������������һ�С���צʽ��",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "ץ��",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N˫��һ£����צֱ��$n���̣���צȴЮ����֮������$n���䣬һ��һʵ������һ�С���צʽ��",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "ץ��",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N���ζ�������ӥ���հ㡰ٿ���ش�$nͷ��Խ����ʹһ�С���צʽ��˫צ����$n�Ժ����",
	"force" : 190,
	"dodge" : 20,
	"damage_type" : "ץ��",
	"damage" : 25,
	"lvl" : 40,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N�͵�һ����ͻȻ����$n��ǰ��ʹһ�С���צʽ������צֱ��$nС��",
	"force" : 225,
	"dodge" : 20,
	"damage_type" : "ץ��",
	"damage" : 35,
	"lvl" : 80,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N��צ���أ���צ�����󷢣�һ�С���צʽ������������$n��$l",
	"force" : 265,
	"dodge" : 5,
	"damage_type" : "ץ��",
	"damage" : 40 ,
	"lvl" : 100,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N���ι��죬����ǰ�ˣ�ʹһ�С���צʽ����ֱ��$n�ɲ�",
	"force" : 310,
	"dodge" : 25,
	"damage_type" : "ץ��",
	"damage" : 45,
	"lvl" : 120,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$N����Ʈ������Ȼת��$n���һ�С���צʽ����˫צֱ��$n�ʺ����",
	"force" : 320,
	"dodge" : 35,
	"damage_type" : "ץ��",
	"damage" : 50,
	"lvl" : 140,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
([	"action" : "\n$Nһ����Х�����ΰ���ʹ����ǧצʽ�����ɰ�������»���$n�پ�����צӰ������ȫ����Ѩ",
	"force" : 335,
	"dodge" : 40,
	"damage_type" : "ץ��",
	"damage" : 55,
	"lvl" : 160,
        "post_action": (: next_hit :),  
	"skill_name" : "ǧצʽ"
]),
([	"action" : "\n$N���γ��������ͬ����ӥ�˫צ�ɳ���һ�С���צʽ�����ٿշɻ���$n",
	"force" : 335,
	"dodge" : 40,
	"damage_type" : "ץ��",
	"damage" : 75,
	"lvl" : 160,
        "post_action": (: next_hit :),  
	"skill_name" : "��צʽ"
]),
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���ѹ�ӥצ��������֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷�ѧ�ѹ�ӥצ����\n");

	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫�����޷�ѧ�ѹ�ӥצ����\n");

	if ((int)me->query_str() < 33)
		return notify_fail("�����ڵ�����̫����޷�ѧ�ѹ�ӥצ����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("sougu",1);

        if( me->query_temp("lzg_lianhuan"))
        {
		return action[me->query_temp("lzg_lianhuan")-1];
        }
	else {
		for(i = sizeof(action); i > 0; i--) 
			if(level > action[i-1]["lvl"])
        	        	return action[NewRandom(i, 20, level/5)];
	}
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�������������ӥצ����\n");

	me->receive_damage("qi", 55);
	me->add("neili", -57);
	return 1;
}

int next_hit(object me, object victim, object weapon, int damage)
{
        string *msg;
        msg = ({
                HIR"\n$Nһץ���У���ץ���������Ƹ���Ѹ�ݸ��ͣ�" NOR,
                HIR"\n$N�ѹǷ�ӥצԴԴ������һ����գ��ּ�����������" NOR,
                HIR"\n$n�Ŷ�����У�$N����������ץ���켫�ݼ���"NOR,
        });

        if(damage==RESULT_DODGE 
        && (int)me->query_skill("sougu",1) > 100 
        && 2>random(3)
        && !me->query_temp("lzg_lianhuan")
        && !me->query_temp("next_hit")) {
        message_vision(msg[random(sizeof(msg))] , me,victim );
        me->add("neili", -20);
        me->add_temp("next_hit",1);
        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
        me->delete_temp("next_hit");
        }
        
}

string perform_action_file(string action)
{
	return __DIR__"sougu/" + action;
}
