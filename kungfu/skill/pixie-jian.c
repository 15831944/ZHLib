// pixie-jian.c ��а����
// looo/6/21/2001/update
// modified by Venus Oct.1997
// updated by Doing Lu 4/11/2000
// updated by Haiyan@huaxia 2003.9

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
    "ͻȻ֮�䣬��Ӱ���ϣ�$n��󻬳����࣬��ʱ�ֻص���ԭ�أ������$N��һ�С�\n",
    "$n�ֱۻ�ת����$N������һ�ƣ�˳������һ�ԡ�\n",
    "$n�����������$N������Ѹ���ޱȵ�һ����˳������һ�ԡ�\n",
    "$n����Ʈ����������ȣ�ת�˼�ת���Ʋ���$N����󣬶����$N��һ�С�\n",
    "$Nֻ����ǰһ�����ƺ�����$n����һ�ϣ����漴�ּ�$n�ص�ԭ�أ�ȴ�ƴ�δ�뿪��\n",
    "$N�۾�һ����$n��û����Ӱ��ͻȻ$n���������һ��$N��ͷ������Ծ����\n",
    "$n��ȻһЦ������֮����$N����֪����Ǻã�ͣס�˹�����\n",
});

mapping *action = ({
([  "action":"ͻȻ֮�䣬��Ӱ���ϣ�$N��󻬳����࣬��ʱ�ֻص���ԭ��",
    "force" : 270,
    "attack": 180,
    "parry" : 20,
    "dodge" : 130,
    "damage": 220,
    "lvl" : 0,
    "skill_name" : "��Ӱ����",
    "damage_type":  "����"
]),
([  "action":"$N�����������$n������Ѹ���ޱȵ�һ����$n��Щ�����Լ�С��",
    "force" : 260,
    "attack": 180,
    "parry" : 30,
    "dodge" : 165,
    "damage": 250,
    "lvl" : 12,
    "skill_name" : "�Լ�С��",
    "damage_type":  "����"
]),
([  "action":"�����$N�����ϣ��ڵ�$n�������Ծ��ԭ��",
    "force" : 300,
    "attack": 190,
    "parry" : 35,
    "dodge" : 185,
    "damage": 280,
    "lvl" : 25,
    "skill_name" : "������",
    "damage_type":  "����"
]),
([  "action":"$NͻȻ���з�һ�䣬$w�����������ʽ������ס�$n����֮�з������",
    "force" : 330,
    "attack": 200,
    "parry" : 40,
    "dodge" : 120,
    "damage": 270,
    "lvl" : 5,
    "skill_name" : "�з�һ��",
    "damage_type":  "����"
]),
([  "action":"$N����Ʈ����������ȣ�ת�˼�ת���Ʋ���$n�����",
    "force" : 310,
    "attack": 210,
    "parry" : 50,
    "dodge" : 120,
    "damage": 260,
    "lvl" : 35,
    "skill_name" : "�������",
    "damage_type":  "����"
]),
([  "action":"$Nһ����Ц������Ｒ����ǰ��һ˲֮�䣬��$n����Ѳ���һ�ߣ�$w�漴�ݳ�",
    "force" : 330,
    "attack": 210,
    "parry" : 40,
    "dodge" : 165,
    "damage": 290,
    "lvl" : 45,
    "skill_name" : "������ǰ",
    "damage_type":  "����"
]),
([  "action":"$N�ȵ������ã������㼴�γ�$w�����ִ̳�������ת����ȥ",
    "force" : 300,
    "attack": 220,
    "parry" : 45,
    "dodge" : 180,
    "damage": 300,
    "lvl" : 55,
    "skill_name" : "���ִ̳�",
    "damage_type":  "����"
]),
([  "action":"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪",
    "force" : 300,
    "attack": 230,
    "parry" : 40,
    "dodge" : 150,
    "damage": 280,
    "lvl" : 65,
    "skill_name" : "��ǰһ��",
    "damage_type":  "����"
]),
([  "action":"$N����ˣ�$n��׷������ͻȻ��$N����$n��ǰ������$wֱָ$n��$l",
    "force" : 310,
    "attack": 210,
    "parry" : 50,
    "dodge" : 170,
    "damage": 300,
    "lvl" : 75,
    "skill_name" : "�����",
    "damage_type":  "����"
]),
([  "action":"$N��س嵽$n��ǰ������$wֱ��$n���ۣ�$n��æ�мܣ�����$N��$wͻȻת��",
    "force" : 350,
    "attack": 210,
    "parry" : 55,
    "dodge" : 144,
    "damage": 280,
    "lvl" : 85,
    "skill_name" : "ֱ������",
    "damage_type":  "����"
]),
([  "action":"$N����Ծ��$ņ��һ����������$N����ֱ����£�����$w����$n��$l",
    "force" : 340,
    "attack": 230,
    "parry" : 50,
    "dodge" : 180,
    "damage": 310,
    "lvl" : 94,
    "skill_name" : "����Ծ��",
    "damage_type":  "����"
]),
([  "action":"$N��֦�Ͱڣ�$n��ǰ�·�ͻȻ�������߰˸�$N���߰�ֻ$wһ�����$n",
    "force" : 350,
    "attack": 210,
    "parry" : 60,
    "dodge" : 140,
    "damage": 320,
    "lvl" : 120,
    "skill_name" : "��֦�Ͱ�",
    "damage_type":  "����"
]),
});

int can_not_hubo() {return 1;} 

int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "parry";
}

int double_attack() { return 1; }

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("pixie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if (me->query("gender") == "Ů��")
                return notify_fail("�Թ�����û��˵��Ů�˿�����ϰ�������䡣\n");

        if (me->query("gender") == "����" && !me->query("tianmo_jieti"))
                return notify_fail("�������Ϣ��Ȼ���ң���������\n");

        return 1;
}

mixed hit_by(object ob, object me, int damage)
{
        string result;
        int shang;

        if (me->query("gender") == "����")   return damage;

        if (!living(me) || (me->is_busy() && random(3) == 0))   return damage;

        if (damage <= 0)   return damage;

        if (random(3) == 0)
        {
              shang = damage / 5;
              result = HIR "$n" HIR "Ĭ���а������������Ϣ����ճ�ͣ�" +
                       HIR "�ؿ�����ǧ����ѹ��������������\n" NOR;
              me->receive_damage("qi", shang);
              me->receive_wound("qi", shang / 2 + random(shang / 2));
              return ([ "msg" : result, "damage" : damage ]);
        } else   return damage;
}

/*
mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int) me->query_skill("pixie-jian", 1) < 300)
        return;

        dp = target->query_skill("force", 1) + target->query_skill("dodge",1) / 4;
        ap = me->query_skill("dodge", 1) / 4 +
             me->query_skill("pixie-jian", 1);

        if (ap / 3 + random(ap) > dp)
        {
                me->add("neili", -30);
                msg = dodge_msg[random(sizeof(dodge_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;
                result = ([ "damage": -damage,
                            "msg"   : msg ]);
                return result;
        }
}
*/

int practice_skill(object me)
{
        return notify_fail("��а����ֻ��ͨ����ϰ����а���ס��򡶿���"
                           "���䡷��ѧϰ��\n");
}

string perform_action_file(string action)
{
        return __DIR__"pixie-jian/perform/" + action;
}

int difficult_level()
{
        return 400;
}

