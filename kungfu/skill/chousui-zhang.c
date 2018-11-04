// chousui-duzhang.c  ������, based on xianglong-zhang.c
// modified by smallfish

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N����¶�������Ц�ݣ�����΢�ڣ��Իε�$n���������������ɫ��˫��ɨ��$n��$l",
        "dodge" : -30,
        "attack": 49,
        "parry" : -37,
        "dmage" : 32,
        "force" : 100,
        "damage_type": "����",
        "lvl" : 0,
        "skill_name" : "������",
]),
([      "action": "$NͻȻһ���У�������ת��������$n��˫�Ʒ���������$n��$l",
        "dodge" : -22,
        "attack": 56,
        "parry" : -34,
        "dmage" : 47,
        "force" : 140,
        "damage_type": "����",
        "lvl" : 15,
        "skill_name" : "��ɽ��ӥ",
]),
([      "action": "ͻȻ��$N��ɫһ���������з����Ź����죬�������������֣�һ�С���ʬ���������ޱȵ�ץ��$n��$l",
        "dodge": -20,
        "parry" : -35,
        "force": 175,
        "damage": 55,
        "lvl" : 30,
        "damage_type": "����",
        "skill_name" : "��ʬ��",
]),
([      "action": "$N��һת����һת�����ӻ���֮����ת�ۼ��Ѿ��۵�$n��ǰ��˫��Ю��һ���ȳ�֮������$n��$l",
        "dodge": -10,
        "parry" : -15,
        "force": 200,
        "damage": 65,
        "lvl" : 45,
        "damage_type": "����",
        "skill_name": "������",
]),
([      "action": "$N�͵�Ծ�𣬴�����$n��ȥ����$nһ�ǻ���֮�ʣ��������𶾹��͵���$n��ȥ��",
        "dodge": 10,
        "parry" : -5,
        "force": 230,
        "damage": 70,
        "lvl" : 60,
        "damage_type": "����",
        "skill_name": "��ɱ��",
]),
([      "action": "$NͻȻ���˵ض�����˫����$n������ȥ����$n����֮ʱ��˳��ץ�����ʯͷ��$n��$l��ȥ",
        "dodge": 30,
        "parry" : -5,
        "force": 260,
        "damage": 75,
        "lvl" : 80,
        "damage_type": "����",
        "skill_name": "����һ��",
]),
([      "action": "$N˫Ŀ�׹���䣬�ؿڸ߸߹��𣬽����������������У�ƴ������$n��ȥ",
        "dodge": -30,
        "parry" : -5,
        "force": 300,
        "damage": 85,
        "lvl" : 100,
        "damage_type": "����",
        "skill_name": "������",
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }   

int valid_combine(string combo) { return combo=="sanyin-wugongzhao"; }

int valid_learn(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("chousui-zhang", 1);

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 10)
                return notify_fail("��Ļ����󷨻�򲻹����޷��������ơ�\n");

        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷���߳����ơ�\n");

        if ((int)me->query("max_neili") < 60)
                return notify_fail("�������̫�����޷���������");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ĳ����Ʒ���\n");

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
        level = (int)me->query_skill("chousui-zhang", 1);
        
        if (present("huo yan", environment(me))){
	        if (random(me->query_skill("strike")) > 250 && me->query("neili") > 1000 ) {
                	me->add("neili", -100);
			//victim->start_busy(random(3));
                	return ([
        	    		"action":BLU"$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ�������ҧ��⣬"+HIR+"һ����"
                    		"Ѫ���������ȥ��\n�ǻ������һ����"+HIW+"�漴��Ϊ������$N�͵����Ӽ���������"
                    		"�ݰ���ת��ʮ���Ȧ�ӣ�"+HIR+"�����������������Ѷ��ز��𣬱���һ����ǽ����$nѹ��ȥ"NOR,
                		"force": 800,
                		"dodge": 50,
                		"weapon": "����",
                		"damage": 150,
                		"damage_type": "����"]);
        	}
        	if (random(me->query_skill("strike")) > 215 &&
            		me->query("neili") > 800 ) {
                	me->add("neili", -75);
			//victim->start_busy(random(3));
                	return ([
        			"action":HIG"$N������ȣ�������ʢ���̻�ͻȻ����һ��"+HIR+"����Ļ�����$n���������ʹ�����ͣ�ȥ����죬"+HIG+"ֻ��һ���̵Ļ����ڿ��й�µµ��Ѹ��ת��"NOR,
                		"force": 600,
                		"dodge": 25,
                		"weapon": "����",
                		"damage": 100,
                		"damage_type": "����"]);
        	}
        	if (random(me->query_skill("strike")) > 180 &&
            		me->query("neili") > 600 ) {
                	me->add("neili", -50);
                	return ([
        			"action":HIR"$N����һ����һ�ɾ���ֱ�������֮�У�"+HIG+"�������ֳַ�һ��ϸϸ���̻𣬱���һ��ˮ�߰㣬"
                 		+HIW+"$N����Ӷ������ɾ����Ϯ$n����"NOR,
                		"force": 500,
                		"dodge": 10,
                		"weapon": HIG"�̻�"NOR,
                		"damage": 100,
                		"damage_type": "����"]); 
        	}
        	if (random(me->query_skill("strike")) > 150 &&
            		me->query("neili") > 500 ) {
                	me->add("neili", -20);
                	return ([
       				"action":HIR"$N�漴����б�ĳ�һ��"+HIG+"�̻�"+HIR+"��$n��ȥ���������ڣ�"+HIG+"����һ����ɫ���ߺ��Կռʣ�����ڶ���"
                    		+HIR+"��ɫ�������ޣ�"+BLU+"���ǹ��죬��â��˸����"+HIG+"��ӳ��$nͷ���Ա�"NOR,
                		"force": 480,
                		"dodge": 20,
                		"weapon": HIG"�̻�"NOR,
                		"damage": 90,
                		"damage_type": "����"]); 
        	}
        	
         	if (random(me->query_skill("strike")) > 120 &&
            		me->query("neili") > 400 ) {
                	me->add("neili", -10);
                	return ([
        			"action":HIR"$NͻȻ��˫ü����һ��������ʳָ�����㣬������������������죬"+HIG+"��������𻨣���������һ�㣬"
                    		"��$N���������£��ִ�����Ϯ��$n������Ѹ��֮��"NOR,
                		"force": 450,
                		"dodge": 10,
                		"damage": 90,
                		"weapon": "��",
                		"damage_type": "����"]);
        	}
    	}
        
       for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("chousui-zhang", 1);


        if ((int)me->query("qi") < 50)
                return notify_fail("��������������޷���ϰ�����ơ�\n");

        if ((int)me->query("neili") < 50)
                return notify_fail("����������㣬�޷���ϰ�����ơ�\n");

        if ((int)me->query("neili") < 8)
                return notify_fail("������������������ơ�\n");

        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷���߳����ơ�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");

        if (me->query_skill("chousui-zhang", 1) < 50)
                me->receive_damage("qi", 30);
        else
                me->receive_damage("qi", 25);
        me->add("neili", -32);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int neili, neili2, cases, csz;
        string result;
        neili=me->query("neili")/10;
        neili2=victim->query("neili")/10;
        csz=me->query_skill("chousui-zhang",1);

        if (csz < 150 && damage_bonus < 250) return 0;

        if(me->query_skill("strike") + random(neili) > victim->query_skill("force") + random(neili2)){
                result = MAG"$n��Ȼ����һ����Ϯ��������һ�Σ�ͷ��΢΢��Щ���衣\n"NOR;
                victim->affect_by("xx_poison",
                        ([ "level" : csz + random(csz/2),
                           "id"    : me->query("id"),
                           "duration" : csz/50 ]));
		victim->receive_damage("qi",1,me);
        } else result = YEL"$næ�������ֿ�����$N���ϵľ綾�������⡣\n"NOR;

        return result;
}

string perform_action_file(string action)
{
    return __DIR__"chousui-zhang/" + action;
}


