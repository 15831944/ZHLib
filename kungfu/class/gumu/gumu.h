// gumu.h

int permit_recruit(object ob)
{
        if( ob->query("detach/��Ĺ��") ||
            ob->query("betrayer/��Ĺ��") )
        {
                command("say ����ȥ��ȥ�ˣ��������Ǻο�������");
                return 0;
        }
        if (ob->query("detach/ȫ���") ||
            ob->query("betrayer/ȫ���") )
        {
                command("say ������Ȼ����ȫ��ţ�����ˣ�����С����Ҳ�������������ִ�Ӣ�ۡ�");
                return 0;
        }

        if( ob->query("betrayer/times") )
        {
                command("say ���²��Ҳ��ţ��Ҳ�������Ϊͽ��");
                return 0;
        }

        if( ob->query("family/family_name") &&
            ob->query("family/family_name") != "��Ĺ��" )
        {
                command("say ���������ʦָ�㣬��Ҫ���¿๦����Ҫ���Ķ��⣡");
                return 0;
        }

        return 1;
}
