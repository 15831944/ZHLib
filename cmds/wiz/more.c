// more.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string file;
	object ob;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

	seteuid(geteuid(me));
	if (! arg) return notify_fail("ָ���ʽ : more <����>|<�����> \n");
	file = resolve_path(me->query("cwd"), arg);
	if (file_size(file) < 0)
        {
		ob = present(arg, me);
		if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("û�����������\n");
             log_file("static/more", sprintf("%s%s more %s (%s)\n", me->query("name"), 
     "(" + me->query("id") + ")", file , ctime(time()) )); 
             CHANNEL_D->do_channel(this_object(),"sys2",me->query("name")+"("+me->query("id")+")"+" Cat "+ 
                      file+"��\n"); 
		file = base_name(ob) + ".c";
	}

	if (! SECURITY_D->valid_read(file, me, "read"))
		return notify_fail("��û��Ȩ�޲鿴����ļ���\n");

	CHANNEL_D->do_channel(me, "sys2", sprintf("����ļ�%s��", file));
        me->start_more_file(file);
	return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : more <������>

���ָ����������Է�ҳ��ʽ����һ���ļ������ݡ�

see also: cat
HELP );
        return 1;
}
