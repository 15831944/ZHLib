// pkd.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *obs;
        string msg;
        string sht;
        int i;

	if (PK_D->is_ready())
		return notify_fail("�������ڱ����أ��Ȼ����˵��\n");

        if (! PK_D->is_pking())
                return notify_fail("���ڲ�û���ھ������˴�����\n");

        obs = PK_D->query_all_competitor();
        if (! obs)
                return notify_fail("�޷��� PK DAEMON ������������ϵ��\n");

        obs -= ({ me, 0 });
        msg = HIR "�������˳��г����㻹ʣ��" + chinese_number(sizeof(obs)) +
              "�ˣ������ǣ�\n" NOR;
        msg += HIC "��" HIY "����������������������������������������������������������������������" HIC "��\n" NOR;
        for (i = 0; i < sizeof(obs); i++)
        {
                sht = obs[i]->name(1) + "(" + obs[i]->query("id") + ")";
                msg += (obs[i]->query("gender") == "Ů��" ? HIC : WHT) +
                        sprintf("%-20s", sht) + NOR;
                if (! ((i + 1) % 4))
                        msg += "\n";
        }

        if (i % 4)
                msg += "\n";
        msg += HIC "��" HIY "����������������������������������������������������������������������" HIC "��\n" NOR;
        write(msg);
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : pkd

�����˴�����ʼ��ʱ�򣬿���������ָ��鿴Ŀǰ����˭�����˳��С�
 
HELP );
        return 1;
}