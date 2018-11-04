// idle.c ������

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
        int lvl, bs;

	if (me->ban_say(0))
		return 0;

	if (! arg || ! objectp(ob = find_player(arg)))
                return notify_fail("��Ҫ���ĸ���ҷ�����\n");

	if (me == ob)
		return notify_fail("�������ˮ��\n");

        if (wizardp(ob))
                return notify_fail("��ķ����񹦵ȼ���û����ô�ߡ�\n");

        lvl = me->query_skill("idle-force", 1);
        if (! lvl)
                return notify_fail("�����ѧ���˷�������˵��\n");

        if (lvl < 50)
                return notify_fail("��ķ�����ˮƽ̫��޷�ʩչ������\n");

        if (me->is_busy())
                return notify_fail("���Լ���æ�������˻����ñ��˷�����\n");
        if (me->is_fighting()) 
                return notify_fail("�����ڰɣ���ս�������˷��������ǵ��������˵�ɣ�\n");
        if (lvl < 300 && environment(ob) != environment(me))
                return notify_fail("��ķ�����ˮƽ���ޣ��޷�ʩչ������ǧ��֮�⣡\n");

        if (me->query("jing") < 20)
                return notify_fail("��ľ���̫�����ʩչ��һ�����񹦡�\n");

        if (me->query("learned_points") + 1 > me->query("potential"))
                return notify_fail("���Ǳ�ܲ������޷�ʩչ��һ�����񹦡�\n");

        me->receive_damage("jing", 20);
        me->add("learned_points", 1);
	me->start_busy(2 + random(4));

        message_vision(HIM "$N" HIM "���������дʣ�!@#$%^&��ʲô��˼��\n", me);
        if (random(lvl * lvl) + lvl * lvl < ob->query("combat_exp") ||
	    random(lvl) + lvl / 2 < ob->query_skill("idle-force", 1))
        {
                write("û���κ�Ч����������ķ�����ʧ���ˣ�\n");
                return 1;
        }

        switch(random(4))
        {
        case 0:
                message_vision(HIM "���ͻȻ������һ����ͷ����ݺݵĶ���$N"
                               HIM "���ŵ�$P" HIM "Ŀ�ɿڴ���һ�仰Ҳ˵��������\n",
                               ob);
                break;
        case 1:
                message_vision(HIM "������ͻȻ�ܳ�����С��һ��ץס$N"
                               HIM "�������ߣ�����ȥ�����ˣ��ŵ�$P"
                               HIM "���°�ĭ���������˹�ȥ��\n",
                               ob);
                break;
        case 2:
                message_vision(HIM "һ���˷�Ҳ�Ƶ����˹���������������" +
                               ob->name() + HIM "��" + ob->name() + HIM "��"
                               "��Ĺ�Ʊ�ֵ��ˣ�$P"
                               HIM "����һ��ˤ���˵��ϣ���ס�ĳ鴤��\n",
                               ob);
                break;
        default:
                message_vision(HIM "��Ȼ�����������Զ������Խ��Խ�죬$N" +
                               HIM "��ʱ��ɫ���ף�˵����������\n",
                               ob);
                break;
        }
        ob->ban_say_until(lvl < 180 ? lvl : 180, "�㱻��ɵ�ˣ�����˵���ϻ���");
        write(HIC "��ķ����񹦳ɹ��ˣ�" + ob->name() +
              HIC "���ڱ��ŵ�˵���ϻ����ˣ�\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" +
                              me->name() + HIM "ʩչ�����񹦣�" +
                              ob->name() + HIM "�޹��ܺ���");
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : idle <player>
 
���ָ���������ʹĳһ����Ҳ���˵��������ķ����񹦵���
���ټ��Ժ����ʹ��������ǰ����ұ��졣���÷����񹦵ĳɹ�
�����Լ��ķ����񹦵ȼ��ͶԷ��ľ����йأ�ÿʹ��һ�η�����
������ķ�һ��Ǳ�ܺ�һЩ����
 
HELP );
        return 1;
}
