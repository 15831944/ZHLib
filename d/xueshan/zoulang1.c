//      zoulang1.c ����
//      97/04/09

inherit ROOM;

void create()
{
        set("short","����");
        set("long",@LONG
������ѩɽ���ڵ����ȡ������е��İ����컨������
һЩ��֪��ȷ�к���ĵ�̣�ǽ�������Ǻ�ͨ�׵ķ𾭹�
�±ڻ��ˡ����ϵ��ż���󺣵�������
LONG );
        set("exits",([
                "down"   : __DIR__"cedian1",
                "east"   : __DIR__"dumudian",
                "west"   : __DIR__"dating",
                "westup" : __DIR__"zoulang3",
        ]));
        setup();
}

void init()
{
        add_action("do_watch", "watch");
        add_action("do_watch", "kan");
        add_action("do_watch", "mianbi");
        add_action("do_watch", "face");
}

int do_watch()
{
        object ob = this_player();
        int lvl = this_player()->query_skill("yujiamu-quan",1);

        if ((int)ob->query_skill("force") < 100)
        {
                write("����ڹ��������޷��������̵���ʲô��\n");
                return 1;
        }

        if ((int)ob->query_skill("yujiamu-quan", 1) > 120)
        {
                write("��Ľ�����ĸȭ��Ϊ�Ѿ���Խ���������ˡ�\n");
                return 1;
        }
	if ((int)ob->query_skill("yujiamu-quan", 1) < 10)
	{
		write("��Խ�����ĸ����һ����֪���޷�����������̵����ݡ�\n");
		return 1;
	}

        if (! ob->can_improve_skill("yujiamu-quan"))
        {
                write("���ʵս���鲻�㣬�޷�����������ݡ�\n");
                return 1;
        }
        if (ob->query("jing") < 20)
        {
                 write("��̫���ˣ������޷���������������ݡ�\n");
                 return 1;
        }
        message_vision("$N����ű���ͼ����Ħ���ã���������\n",ob);
        ob->improve_skill("yujiamu-quan", random(ob->query("int")));
        ob->receive_damage("jing", 20);
        return 1;
}

