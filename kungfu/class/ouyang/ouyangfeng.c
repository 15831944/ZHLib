// ouyangfeng.c

#include <ansi.h>
#include "ouyang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me_2(string name);
mixed ask_me();
mixed ask_music_book();
string ask_lingshe();
int ask_shegu();

void create()
{
	set_name("ŷ����", ({ "ouyang feng", "ouyang", "feng" }));
	set("long", "�����ǰ���ɽׯ�����ųơ���������ŷ���档����������\n"
		    "�����⺷����Ȼ�ܵ�������ƭ��ѧϰ�ˡ������澭������\n"
                    "����ħ��һ�ȱ�þ�����ң�����������Ȼ�ָ���������\n"
                    "ʤ������\n");
	set("title", "����ɽׯ��");
	set("gender", "����");
	set("age", 53);
	set("nickname", HIR "����" NOR);
	set("shen_type",-1);
	set("attitude", "peaceful");

	set("str", 32);
	set("int", 34);
	set("con", 34);
	set("dex", 32);

	set("qi", 6000);
	set("max_qi", 6000);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 7300);
	set("max_neili", 7300);
	set("jiali", 120);

	set("combat_exp", 2500000);

	set_skill("force", 270);
	set_skill("strike", 250);
	set_skill("dodge", 250);
	set_skill("parry", 270);
	set_skill("cuff", 250);
        set_skill("finger", 240);
	set_skill("staff", 270);
	set_skill("training", 270);
        set_skill("poison", 270);
        set_skill("shedu-qiqiao", 270);
	set_skill("hamagong", 270);
	set_skill("chanchu-bufa", 250);
	set_skill("lingshe-quan", 250);
	set_skill("lingshe-zhangfa", 270);
	set_skill("baibian-daxue", 260);
        set_skill("guzheng-jifa", 300);
        set_skill("xiyu-tiezheng", 300);
	set_skill("medical", 280);
	set_skill("baituo-michuan", 280);
        set_skill("shentuo-zhang", 300);

	map_skill("force", "hamagong");
        map_skill("strike","hamagong");
	map_skill("dodge", "chanchu-bufa");
	map_skill("cuff",  "lingshe-quan");
	map_skill("parry", "lingshe-zhangfa");
	map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

	create_family("ŷ������", 5, "����");
        set("chat_chance", 2);
        set("chat_msg",({
                "ŷ���������������������ŷ���ϲ����ذԽ����ء�\n",
                "ŷ��������Ҷ�ŷ���˱��ܹ������Ҽ��۷磡\n",
                "ŷ������������ն����������ģ�\n",
        }));

        set("inquiry", ([
                "��·����"   : (: ask_me_2, "shenshe" :),
                "����"   : (: ask_me :),
                "����"   : (: ask_me :),
 		"����" : (: ask_lingshe :),
		"�߹�": (: ask_shegu :),
                "ǧ�߳���": (: ask_me :),
		"����"   : (: ask_music_book :),
		"���ݼ���": (: ask_music_book :),
        ]));

	set("lingshe_count",3);
	set("music_book", 1);
	setup();
	carry_object("/d/baituo/obj/shezhang")->wield();
	carry_object("/clone/misc/cloth")->wear();
        carry_object("d/baituo/obj/tiezheng");
	add_money("silver",50);
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "guzheng-jifa")
                return 0;

        if (me->query_temp("can_learn/ouyang/guzheng-jifa"))
                return 1;

        command("say �ðɣ���Ը��ѧ�Ҿʹ���һ�����֮����");
        me->set_temp("can_learn/ouyang/guzheng-jifa", 1);
        return 1;
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))
                return;

        if((int)ob->query("combat_exp") < 200000)
        {
                if (random(2))
                        command("smile");
                else
                        command("pat " + ob->query("id"));

                command("say ��ľ��黹�������Ⱥ��ҵ�ֶ��ŷ����ѧϰ�书�ɡ�");
	        return ;
        }

        command("sigh");
        command("pat " + ob->query("id"));
        command("recruit " + ob->query("id"));
        message_vision("ŷ����������������Ǻ�����˰���˵�����ŷ�����۾���������Щʪ���ˡ�\n",
                       this_object());
        return;
}

string ask_me_2(string name)
{
        mapping fam; 
        object ob;
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "ŷ������")
                return RANK_D->query_respect(this_player()) + 
                "���㲢���Ǳ�ɽׯ���ˣ��˻��Ӻ�˵��";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "�����ϲ�������������ô����Ҫ������̰�����ᣡ";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("ŷ�����$Nһ��" + ob->query("name") + "��\n", this_player());
        return "�������˱�ɽׯ���У��мǲ��ɸ������ˣ�"; 
}
mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/lingshe-zhangfa/qianshe"))
                return "�㻹����ȥ����ȥ���úð�����ŷ���ҷ�����";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ�����ô��";

        if (me->query("shen") > -40000)
                return "�������ֶβ����ݶ��������ڻ����ܴ�����У�";

        if (me->query_skill("lingshe-zhangfa", 1) < 120)
                return "���Ⱥúð������ȷ���������˵��";

        message_vision(HIY "$n" HIY "�ȵ�������ϸ�ˣ�˵�ѵ�"
                       "�ۺ�ɨ�����������������Ǳ�������$N"
                       HIY "���۾�����ֱ�ˡ�\n" NOR,
                       me, this_object());
        command("heihei");
        command("say ����ʾ����ô������㿴����û�У�");
        tell_object(me, HIG "��ѧ����ǧ�߳�����\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        me->set("can_perform/lingshe-zhangfa/qianshe", 1);
        return 1;
}

mixed ask_music_book()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "�ҵ������Ѿ����ȥ�ˡ�\n";

        ob = new("/clone/book/zhengpu");
        ob->move(me, 1);
        message_vision("$n�����׸���$N����������ȥ�Լ��ú���ĥ�ɡ�\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

int ask_shegu()
{
	object me, staff;
	int lv;
	me = this_player();

	if( me->query("family/family_name") != "ŷ������" && me->query("combat_exp") > 100000) {
		command("sneer "+me->query("id"));
		command("say ����ɽ�߹ȵ����ܣ�����͸¶������֪����"+RANK_D->query_rude(me)+"����̫�����ˣ�");
		kill_ob(me);
		command("perform bite "+me->query("id")); // has weapon
		command("perform puji "+me->query("id")); // no weapon
		return 1;
	}

	if( me->query("family/family_name") != "ŷ������" ) {
		command("sneer "+me->query("id"));
		message_vision("$Nû�лش�$n��\n", this_object(), me);
		return 1;
	}

	if( me->query("baituo/shegu_permit") ) {
		command("say �߹��е��߶�����������Ⲷ׽���ú�����������ĪҪ����������������");
		return 1;
	}

	lv = (int)me->query_skill("poison", 1);

	if( lv < 80 ) {
		command("say ƾ�����ʹ�����£�����߹Ȼ���úܡ��ԹԵ���ׯ��������");
		return 1;
	}
	
	if( lv < 100 ) {
		command("pat "+me->query("id"));
		command("say ��Ķ������е����ˣ���������߹ȣ����ö��µ㹦����ĥ��");
		return 1;
	}

	command("nod "+me->query("id"));
	command("say ���ö������ͣ��ƺ��ǽ������ˡ��ã��Ϸ��������߹��������졣");
	me->set("baituo/shegu_permit", 1);

        staff = new("/d/baituo/obj/lingshezhang");
	staff->move(me);

	message_vision("$N��һ��"+staff->name()+"����$n��\n",this_object(), me);
	command("say �ӽ����ᣬ��������ɽ����߹ȡ����Ĵ������У���Ķ��������Ը��ϲ�¥��");

	return 1;
}

string ask_lingshe()
{
	mapping fam;
	object obj, me;

	me = this_player();
	if (me->query("family/master_name") != "ŷ����") {
		return ("���޹������������Ǳ�ҪΪ�");
	}
	if (query("lingshe_count") < 1) {
		return ("����ѱ�����ף�����û�У�");
	}
	message_vision(CYN"$N�鴽��Х�����л����γ�һ����ɫС�ߣ�����$nҡͷ��β������ʾ���ʺá�\n"NOR,
	this_object(), me);
        obj = new("/d/baituo/npc/lingshe.c");
	obj->move(environment());
	add("lingshe_count", -1);
		  return ("�������ԣ����޲��������Ƿ���Ե��Ϊ�������ˡ�");
}

void reset()
{
        if (query("lingshe_count") < 3)
        add("lingshe_count",1);
        set("music_book", 1);
}

