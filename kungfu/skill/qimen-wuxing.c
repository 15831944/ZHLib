// qimen-wuxing

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
	int lvl;
	
	lvl = (int)me->query_skill("qimen-wuxing", 1);

	if ( lvl > 100 && me->query_int()-30 < lvl/10 )
		return notify_fail("�������ж�����˵̫����ˡ�\n");

	return 1;
}


int practice_skill(object me)
{	
	return notify_fail("���������ܿ�ѧ(learn)����ߡ�\n");
}
