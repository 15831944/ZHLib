// count.c

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        object ob;

        if( (int)me->query_skill("literate",1) < 50 )
                return notify_fail("����Ļ�֪ʶ̫��޷�����������Եİ��\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}
