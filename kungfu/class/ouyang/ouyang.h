// ouyang.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();

    if( ob->query("detach/ŷ������") || ob->query("betrayer/ŷ������") )
    {
            command("say ��Ȼ�뿪������ŷ���ң��Ͳ�Ҫ������");
            return 0;
    }

    if (ob->query("name") == "ŷ����" ||
        ob->query("name") == "ŷ����")
    {
        message_vision("$N��ŭ���Ҳ٣��������������ʲô��˼����\n",me);
        return 0;
    }

    if (ob->query("purename") == "��" ||
        ob->query("purename") == "��")
    {
        message_vision("$N��ŭ���Ҳ٣��������������ʲô��˼����\n",me);
        return 0;
    }

    if( (ob->query("family/family_name") &&
        ob->query("family/family_name") != "ŷ������") ||
        (ob->query("born_family") != "ŷ������" && 
        ob->query("can_not_change") &&
        !ob->query("tianmo_jieti/times")) )
    {
        message_vision("$N��$n����ŷ���������������壬�������ˣ�����ı��·�ɣ�\n",
                       me, ob);
        return 0;
    }
    return 1;
}

