// linji-zhuang.c �ټ�ʮ��ׯ

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

string *skill_name = ({
  "����ׯ",
  "����ׯ",
  "֮��ׯ",
  "����ׯ",
  "����ׯ",
  "����ׯ",
  "����ׯ",
  "Ʈ��ׯ",
  "����ׯ",
  "С��ׯ",
  "����ׯ",
  "ڤ��ׯ",
  "�ټ�ʮ��ׯ",
});

string *combo_name = ({
  "���",
  "֮��",
  "����",
  "����",
  "��С",
  "��ڤ",
});

int query_neili_improve(object me)
{
        int lvl;

	if (me->query("sex"))
		return 0;

        lvl = (int)me->query_skill("linji-zhuang", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return force == "emei-xinfa";
}

int valid_learn(object me)
{
	int i, np, nf, nh, ns, ts;
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("linji-zhuang", 1);
	np = (int)me->query_skill("mahayana", 1);

        if (me->query("gender") != "Ů��")
                return notify_fail("���Ů�ӣ�������ϰ�ټ�ʮ��ׯ��\n");

        if (np <= nh && np < 200)
                return notify_fail("��Ĵ�����͹���Ϊ�������޷�����������ټ�ʮ��ׯ��\n");

        if (nf < 40)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����ټ�ʮ��ׯ��\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�ټ�ʮ��ׯֻ����ѧ(learn)�������������ȡ�\n");
}

void skill_improved(object me)
{
	int level = me->query_skill("linji-zhuang",1);
	int o_lvl = me->query("linji_lvl");
	int i;

	if ( level > 180 ) return;

	if ( level/15*15 == level ) 
	{
		tell_object(me, HIG "��ԡ�" + skill_name[level/15-1] + "���ѻ�Ȼ��ͨ��\n"NOR);
		if (o_lvl < level) 
		{
			tell_object(me, HIG"��ʱ��Ի����ڹ�������Ҳ�����ߡ�\n"NOR);
			for (i=0; i< level; i++)		
				me->improve_skill("force", level);
 		}
	}

	if ( level/30*30 == level ) 
	if (o_lvl < level) 
	{
		tell_object(me, HIY"��ʱ��" + combo_name[level/30-1] +
			"��ׯ�ڻ��ͨ��һ����͵���������ȫ��������Ϊ��������һ�㡣\n"NOR);
		me->add("max_neili", level);
	}
	
	if ( o_lvl < level ) me->set("linji_lvl", level);
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
	string msg;
	int lvl = victim->query_skill("linji-zhuang", 1);

	if (victim->query("sex/times")) return damage;

	if (lvl < 180) return damage;

	if (victim->query("neili") < lvl*3) return damage;

	if (victim->query("neili")>lvl*10 && random(lvl*lvl + 250000) > 250000) 
	{
		msg = HIB"$n�����ټ�ʮ��ׯ��ȫ���ֵ�$N�Ĺ�����\n"NOR;
        	return ([ "msg" : msg, "damage" : -lvl ]);
  	}
	return damage;
}

string query_skill_name(int level)
{
  if (level < 180) return skill_name[level/15];
  else return skill_name[12];
}

string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}
