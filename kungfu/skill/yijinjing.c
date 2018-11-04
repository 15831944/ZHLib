// yijinjing.c ���� �׽��
// Feb.21 1998 by Java

inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "taiji-shengong" ||
               force == "wudang-xinfa" ||
               force == "shaolin-xinfa"||
               force == "riyue-xinfa"||
               force == "xixing-dafa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("yijinjing", 1);
    return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧϰ�׽�񹦣�\n");

//        if (me->query("gender") != "����")
//                return notify_fail("�㲻�����ԣ��޷���ϰ�׽�񹦡�\n");

        if (me->query("family/family_name") != "������" &&
            me->query("family/family_name") != "�������")
                  return notify_fail("�׽�������־�����������ϰ�к�������\n");

        if (me->query("family/family_name") == "�������" &&
            me->query("family/master_name") != "������")
                  return notify_fail("�׽�������־�����������ϰ�к�������\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("�׽��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijinjing/" + func;
}

