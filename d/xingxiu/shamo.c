// Room: /d/xingxiu/shamo4.c

#include <room.h>
inherit ROOM;

void create()
{
       set("short","��ɳĮ");
       set("long", @LONG
����һƬһ���޼ʵĴ�ɳĮ����һ��������ʧ�˷���
����Ҫ�߳����ɳĮ�������¡�
LONG );
	set("outdoors", "xingxiuhai");
	set("exits", ([
		"east" : __FILE__,
		"west" : __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
	]));
	setup();
}

void init()
{
        object ob;
        int water, food;
        int qi, jing;

        if (interactive(ob = this_player()))
        {
                water = ob->query("water");
                food = ob->query("food");
                water -= (random(2) + 1) * water / 20 + 5;
                food -= (random(2) + 1) * food / 20 + 5;
                if (water < 0) water = 0;
                if (food < 0) food = 0;
                ob->set("water", water);
                ob->set("food", food);

                qi = ob->query("max_qi") * 5 / 100 + random(10);
                jing = ob->query("max_jing") * 5 / 100 + random(10);
                ob->receive_damage("qi", qi);
                ob->receive_damage("jing", jing);
        }
}

int valid_leave(object me, string dir)
{
        string dest;

        dest = sprintf("/d/xingxiu/shamo%d", random(10) + 1);
        me->move(dest);
        switch (random(3))
        {
        case 0:
                write("�㶥�ŷ�ɳ�߰��ߣ�����û���߳�ɳĮ��\n");
                break;

        case 1:
                write("�����������Ұ�Ļ�ɳ��̾�˿������޾���ɵ����š�\n");
                break;

        case 2:
                write("��һ��������ǰŲ�ţ����ѷֲ�������\n");
                break;
        }
        return -1;
}
