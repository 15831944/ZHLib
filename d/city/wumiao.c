// Room: /city/wumiao.c
// YZC 1995/12/04
#include <ansi.h> 
#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
	set("short", "武庙");
	set("long", @LONG
这里是岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书『还我河山』的
横匾。殿两侧壁上嵌着『尽忠报国』四个大字。武人到此，都放下武器，毕恭
毕敬地上香礼拜。旁边似乎有一道侧门。岳飞乃我华夏著名的民族英雄，不少
江湖中纵横天下，勇不可敌的传奇人物，在初入江湖时，都曾经在这里发下誓
言，虔诚的膜拜(mobai)。 新玩家也可以在这里抽签(chouqian)，明确一下自
己的性格，踏上漫漫江湖路。
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
       create_door("northwest", "竹门", "southeast", DOOR_CLOSED);
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
                return notify_fail("你正对着岳飞像单膝跪下，无比虔诚的膜拜这位武圣，良久才起身。\n");
        write(HIC "你对着岳飞像毕恭毕敬的跪了下去，双手合十开始膜拜。\n" NOR, me);
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
        write(HIC "突然一阵威严的声音在你心头响起：“这是我给你的天资！”\n" NOR, me);
        write(sprintf(HIY "\n你只感觉身体里一道霸气缓缓流转，你的秉性变化了：\n"
                          "膂力：【 " HIG "%d" HIY " 】 "
                          "悟性：【 " HIG "%d" HIY " 】 "
                          "根骨：【 " HIG "%d" HIY " 】 "
                          "身法：【 " HIG "%d" HIY " 】\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        return 1;
}

int do_chouqian(string arg)
{
        object me;
        string *character = ({
		"心狠手辣",
		"光明磊落",
		"狡黠多变",
		"阴险奸诈",
	 });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if (time() - me->query("last_chouqian_time") < 1800)
                return notify_fail("这么频繁的抽签干嘛？心不诚则签不灵，过半个小时再来吧。\n");

        write(HIC "你虔诚的抽了一根签，闭目祈祷了一阵，才睁开眼睛看签上所书文字。\n" NOR, me);
        write(HIC "签上写着：" + CHOUQIAN->query_chouqian() + "。\n" NOR, me);
        me->set("last_chouqian_time",time());
        if (me->query("can_not_change")) return 1;
        me->set("character", character[random(sizeof(character))]);
        write(sprintf(HIY "\n你隐隐听到一阵威严的声音：朝『%s』的方向发展吧。\n" NOR,me->query("character")));
        return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "northwest" && ! userp(me) && ! me->is_chatter())
		return 0;
	return ::valid_leave(me, dir);
}
