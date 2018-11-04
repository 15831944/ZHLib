// Room: /city/wumiao.c
// YZC 1995/12/04
#include <ansi.h> 
#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
	set("short", "����");
	set("long", @LONG
�����������������������������Ϸ������������顺���Һ�ɽ����
���ҡ����������Ƕ�š����ұ������ĸ����֡����˵��ˣ��������������Ϲ�
�Ͼ���������ݡ��Ա��ƺ���һ�����š��������һ�������������Ӣ�ۣ�����
�������ݺ����£��²��ɵеĴ�������ڳ��뽭��ʱ�������������﷢����
�ԣ��ϵ�Ĥ��(mobai)�� �����Ҳ�����������ǩ(chouqian)����ȷһ����
�����Ը�̤����������·��
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room","1");
       set("valid_startroom","1");
	set("objects", ([
                        __DIR__"obj/box" : 1,
                        "/u/yuchang/npc/bobo" : 1,
                      "/u/yuchang/npc/beichou" : 1, 
	]));
	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
		"northwest": "/d/wizard/guest_room",
	]));
       create_door("northwest", "����", "southeast", DOOR_CLOSED);
	setup();
}

void init()
{
	add_action("do_mobai","mobai");
	add_action("do_chouqian","chouqian");
}

int do_mobai(string arg){
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->query("can_not_change"))
                return notify_fail("��������������ϥ���£��ޱ��ϵ�Ĥ����λ��ʥ�����ò�����\n");
        write(HIC "�����������Ϲ��Ͼ��Ĺ�����ȥ��˫�ֺ�ʮ��ʼĤ�ݡ�\n" NOR, me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpstr = 23;
        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: 
                        if (tmpstr < 30) tmpstr++;
                        else i--; 
                        break;
                case 1: 
                        if (tmpint < 30) tmpint++;
                        else i--;
                        break;
                case 2: 
                        if (tmpcon < 30) tmpcon++;
                        else i--;
                        break;
                case 3:
                        if (tmpdex < 30) tmpdex++;
                        else i--;
                        break;
                }
        }
        my = me->query_entire_dbase();
        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);
        write(HIC "ͻȻһ�����ϵ�����������ͷ���𣺡������Ҹ�������ʣ���\n" NOR, me);
        write(sprintf(HIY "\n��ֻ�о�������һ������������ת����ı��Ա仯�ˣ�\n"
                          "�������� " HIG "%d" HIY " �� "
                          "���ԣ��� " HIG "%d" HIY " �� "
                          "���ǣ��� " HIG "%d" HIY " �� "
                          "������ " HIG "%d" HIY " ��\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        return 1;
}

int do_chouqian(string arg)
{
        object me;
        string *character = ({
		"�ĺ�����",
		"��������",
		"������",
		"���ռ�թ",
	 });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if (time() - me->query("last_chouqian_time") < 1800)
                return notify_fail("��ôƵ���ĳ�ǩ����Ĳ�����ǩ���飬�����Сʱ�����ɡ�\n");

        write(HIC "���ϵĳ���һ��ǩ����Ŀ����һ�󣬲������۾���ǩ���������֡�\n" NOR, me);
        write(HIC "ǩ��д�ţ�" + CHOUQIAN->query_chouqian() + "��\n" NOR, me);
        me->set("last_chouqian_time",time());
        if (me->query("can_not_change")) return 1;
        me->set("character", character[random(sizeof(character))]);
        write(sprintf(HIY "\n����������һ�����ϵ�����������%s���ķ���չ�ɡ�\n" NOR,me->query("character")));
        return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "northwest" && ! userp(me) && ! me->is_chatter())
		return 0;
	return ::valid_leave(me, dir);
}
