// murong.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();

    if (ob->query("purename") == "��" ||
        ob->query("purename") == "��" ||
        ob->query("purename") == "����")
    {
	message_vision("$N����˼�����������ǡ�" + ob->query("purename") + "������ô��������Ľ�ݼҺ����ǳ��ˡ�Ľ��" + ob->query("purename") + "����\n", me);
        message_vision("$N��Ȼ��ŭ���ߣ����������������ʲô��˼��\n",me);
	return 0;
    }        

    if (ob->query("name") == "Ľ�ݲ�" ||
        ob->query("name") == "Ľ�ݸ�" ||
        ob->query("name") == "Ľ������")
    {
        message_vision("$N��Ȼ��ŭ���ߣ����������������ʲô��˼��\n",me);
        return 0;
    }

    if (ob->query("born_family") != "Ľ������" && 
         ob->query("can_not_change") &&
         !ob->query("tianmo_jieti/times"))
    {
        message_vision("$N��$n�����㲻������Ľ�ݼҵ��ˣ�ʦͽ�����˰ɣ�\n",
                       me, ob);
        return 0;
    }

    if (ob->query("detach/Ľ������") ||
        ob->query("betrayer/times"))
    {
        message_vision("$Nҡҡͷ��$n˵���㷴���޳�����Ľ�ݼҲ��������ˣ�\n",
                       me, ob);
        return 0;
    }

    if (ob->query("family/family_name") &&
        ob->query("family/family_name") != me->query("family/family_name"))
    {
        message_vision("$N��$n�������Ȼ��Ľ�ݼҵ��ˣ�ȴ�����������ɣ�ʵ���Ǵ��治����\n",
                       me, ob);
        return 0;
    }

    return 1;
}
