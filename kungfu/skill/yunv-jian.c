// yunv-jian.c ��Ů���Ľ�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ��"+HIG+"������б����������б�ɣ�����$w�������$n��$l",
        "force"  : 40,
        "dodge"  : 20,
        "parry"  : 20,
        "damage" : 25,
        "lvl"    : 0,
        "damage_type" : "����"
]),
([      "action" : "$N��Ծ����"+HIW+"���׺羭�졹"+NOR+"��$w��Ȼ�´�",
         "force"  : 64, 
         "dodge"  : 64, 
         "parry"  : 74, 
         "damage" : 40, 
         "lvl"    : 4,
         "damage_type" : "����"
]),
([      "action" : "$Nʹ��"+HIY+"���˼����ġ�"+NOR+"���ӽ�ֱ���������ɵ�",
        "force"  : 80,
        "attack" : 70,
        "dodge"  : 75,
        "parry"  : 60,
        "damage" : 50,
        "lvl"    : 9,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ"+HIM+"����ǰ���¡�"+NOR+"һ�����϶��²�����ģ����ֺ�ա�����̵صĹ⾰",
        "force"  : 84,
        "attack" : 40,
        "dodge"  : 65,
        "parry"  : 80,
        "damage" : 60,
        "lvl"    : 14,
        "damage_type" : "����"
]),
([      "action" : "$N����$w��������һ�̣�������������ʹ��"+HIG+"��ɨѩ��衹"+NOR+"��",
        "force"  : 70,
        "attack" : 80,
        "dodge"  : 70,
        "parry"  : 65,
        "damage" : 90,
        "lvl"    : 29,
        "damage_type" : "����"
]),
([      "action" : "$N���ƺ����ǰ��������$w����ӷ���ȴ��һ��"+HIC+"�����ٰ�����"+NOR+"",
        "force"  : 80,
        "attack" : 50,
        "dodge"  : 75,
        "parry"  : 85,
        "damage" : 40,
        "lvl"    : 34,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIG+"�����¶��ġ�"+NOR+"��$w���������һ���󻡣�����$n��$l",
        "force"  : 100,
        "attack" : 79,
        "dodge"  : 75,
        "parry"  : 95,
        "damage" : 92,
        "lvl"    : 39,
        "damage_type" : "����"
]),
([      "action" : "$N����������ң�������Ϊ������$n��ȴ��һ��"+HIB+"���رߵ��ס�"+NOR+"",
        "force"  : 110,
        "attack" : 60,
        "dodge"  : 50,
        "parry"  : 70,
        "damage" : 63,
        "lvl" : 44,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIY+"��������Ʈ��NOW��$w����ػ�������Բ������$n��$l��ȥ",
        "force"  : 90,
        "attack" : 65,
        "dodge"  : 85,
        "parry"  : 90,
        "damage" : 65,
        "lvl"    : 49,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIW+"��С԰�վա�"+NOR+"������$wѸ����$n��������������",
        "attack" : 121,
        "force"  : 90,
        "dodge"  : 95,
        "parry"  : 90,
        "damage" : 79,
        "lvl"    : 54,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��"+HIB+"������ҹ����"+NOR+"������$w�й�ֱ�룬����$n��$l",
        "force"  : 130,
        "attack" : 92,
        "dodge"  : 95,
        "parry"  : 90,
        "damage" : 39,
        "lvl"    : 59,
        "damage_type" : "����"
]),
([      "action" : "$N��������ҵͣ�һ��"+HIG+"���������䡹"+NOR+"��$w�ڿ��л���һ���⻷������$n",
        "force"  : 140,
        "attack" : 66,
        "dodge"  : 90,
        "parry"  : 40,
        "damage" : 51,
        "lvl"    : 64,
        "damage_type" : "����"
]),
([      "action" : "$N����$w���¶��Ͼ��������������һ�㣬ȴ��"+HIW+"�������ٳء�"+NOR+"",
        "force"  : 130,
        "attack" : 70,
        "dodge"  : 65,
        "parry"  : 70,
        "damage" : 95,
        "lvl"    : 70,
        "damage_type" : "����"
]),
([      "action" : "$N������״��һ��"+HIM+"��ľ�����㡹"+NOR+"������$wֱ��$n��$l",
        "force"  : 170,
        "attack" : 81,
        "dodge"  : 90,
        "parry"  : 80,
        "damage" : 81,
        "lvl"    : 76,
        "damage_type" : "����"
]),
([      "action" : "$N���ֽ���һ�죬����$wƽƽ����$n��$l����һ��"+HIR+"��˫���Իء�"+NOR+"",
        "force"  : 180,
        "attack" : 73,
        "dodge"  : 80,
        "parry"  : 60,
        "damage" : 45,
        "lvl"    : 82,
        "damage_type" : "����"
]),
([      "action" : "$N����$w�����̣�һ��"+HIW+"�����Ƴ��ԡ�"+NOR+"��ֱָ$n��$l",
        "force"  : 190,
        "attack" : 76,
        "dodge"  : 90,
        "parry"  : 100,
        "damage" : 92,
        "lvl"    : 88,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIB+"�������չȡ�"+NOR+"��$w���������һ�ӣ���$n����˼��ĽǶȹ���",
        "force"  : 240,
        "attack" : 107,
        "dodge"  : 100,
        "parry"  : 95,
        "damage" : 95,
        "lvl"    : 94,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��"+HIC+"���軨��·��"+NOR+"��һʱ����о���$w��Ӱ�ӣ���$n��֪��εֵ�",
        "force"  : 220,
        "attack" : 80,
        "dodge"  : 120, 
        "parry"  : 75,
        "damage" : 93,
        "lvl"    : 100,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIY+"��İ·��ɣ��"+NOR+"��$w�������㣬����$n��$l",
        "force"  : 260,
        "attack" : 93,
        "dodge"  : 110, 
        "parry"  : 95,
        "damage" : 107,
        "lvl"    : 99,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ�̶�������һ��"+HIY+"������������"+NOR+"��$w���¶��ϴ���$n",
        "force"  : 220, 
        "attack"  : 130, 
        "dodge"  : 110, 
        "parry"  : 90, 
        "damage"  : 150, 
        "lvl"    : 106,
        "damage_type" : "����"
]),
([      "action" : "$N���Ų�������$wͻȻ���Լ������´̳���ȴ��һ��"+HIR+"�����Ľ�����"+NOR+"",
        "force"  : 240, 
        "attack"  : 130, 
        "dodge"  : 90, 
        "parry"  : 130, 
        "damage"  : 130, 
        "lvl"    : 112,
        "damage_type" : "����"
]),
([      "action" : "$N������ˮ�滬��һ�㣬һ��"+HIB+"��������ҹ��"+NOR+"��ƽƽ����$n��$l��ȥ",
        "force"  : 260, 
        "attack"  : 150, 
        "dodge"  : 110, 
        "parry"  : 100, 
        "damage" : 125,
        "lvl"    : 118,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIM+"���������"+NOR+"������$w�̵�$n������",
        "force"  : 280, 
        "attack" : 150, 
        "dodge"  : 90, 
        "parry"  : 100, 
        "damage" : 160, 
        "lvl"    : 124,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIW+"��ĵ�����᡹"+NOR+"��$w�Ƴ�������Ȧ��ƽƽ����$n��$l��ȥ",
        "force"  : 270,
        "attack" : 137,
        "dodge"  : 105,
        "parry"  : 95,
        "damage" : 138,
        "lvl"    : 131,
        "damage_type" : "����"
]),
([      "action" : "$N��������棬������ǰһ�ˣ�һ��"+HIR+"����ҩ���项"+NOR+"��$w��$n��$l��ȥ",
        "force"  : 290,
        "attack" : 138,
        "dodge"  : 110, 
        "parry"  : 110, 
        "damage"  : 130, 
        "lvl"    : 138,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��"+HIC+"����ǰ���ࡹ"+NOR+"������Ծ������$wɨ��$n��$l",
        "force"  : 350,
        "attack" : 120, 
        "dodge"  : 114, 
        "parry"  : 90, 
        "damage"  : 164, 
        "lvl"    : 145,
        "damage_type" : "����"
]),

([      "action" : "$N������Ȼ֮ɫ������һ��"+HIG+"������Բԡ�"+NOR+"��$w����$n��$l",
        "force"  : 320, 
        "attack"  : 180, 
        "dodge"  : 120, 
        "parry"  : 160, 
        "damage"  : 170, 
        "lvl"    : 159,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ��Ů���Ľ�����\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�������̫��޷�ѧϰ��Ů���Ľ�����\n");

        if (me->query_skill("sword", 1) < me->query_skill("yunv-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ů������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
	object target;

	if (me->query_temp("yunv_hebi"))
	{
		target = me->select_opponent();
 		me->map_skill("sword", "quanzhen-jian");
        	me->setup();
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		me->map_skill("sword", "yunv-jian");
                me->setup();
	}
        level = (int) me->query_skill("yunv-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 300) return 0;
	if (!stringp(victim->query_skill_mapped("sword"))) return 0;
	if (victim->query_skill_mapped("sword") != "quanzhen-jian") return 0;
	if (!victim->query_temp("weapon")) return 0;
	if (victim->query_temp("weapon")->query("skill_type") != "sword") return 0;

        if (random(10) > 5)
        {
                victim->receive_wound("qi", (damage_bonus - 300) / 5);
                message_vision(HIW "$N����Ʈ�ݣ����$n�ġ�ȫ�潣����������Ů������ʩչ��Խ��������꣬ռ���Ȼ���\n",me,victim);
                return HIR "$nֻ������ǰ�������������Ŀ�ɿڴ�֮�ʣ��Ѿ���$N��" + me->query_temp("weapon")->query("name") + NOR + HIR + "�������£�\n" NOR;
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 65)
                return notify_fail("���������������Ů������\n");

        if ((int)me->query("neili") < 65)
                return notify_fail("�����������������Ů������\n");

        me->receive_damage("qi", 52);
        me->add("neili", -58);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yunv-jian/" + action;
}

