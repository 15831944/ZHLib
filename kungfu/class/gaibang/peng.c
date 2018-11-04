// sample master.c code
// modified by xxx@xkx 01.01 for shexin quest
//modified by rama for hx

#include <ansi.h>

#define NEED_MONEY 5000000      // need 2k gold!!! ������ʨ�Ӵ󿪿ڡ�
#define ACCEPT_SPECIAL_OBJECT    // For npc accept special object.
#define PENG_EMOTE 13

inherit NPC;
inherit F_MASTER;

string *moreMsg = ({
  "���о�����һ�٣��ֶ�$N��ƤЦ����˵��������������Ӧ�ö�Т��������ҡ���\n",
  "���о����˶٣����ϰ�����������$N˵�������㲻������Т�������˵��𣿡�\n",
  "���о����˸���Ƿ�����ĵض�$N˵����������ô��ôû��"HIY"Ǯ"NOR+CYN";����\n",
  "���о�����$N�̿�������������Ц������ô��Ǯ���㲻�������ȥ��������𣿹�����Ц�����ˣ�\n",
});

string *Pengemote = ({ "kick ", "kick2 ", "kick3 ", "consider ", "slap ", "slap2 ", "slap3", "smash ", "cut ", "hammer ", "sneer ", "hate ", "idle " });

string ask_me();
mixed ask_me2();
string ask_mebook();
int accept_special_object(object ob, object obj); // for GOLD !!!!!
private void notEnough(object);
private void enough(object);
private void teachSheXin(object);
private void pengsResponse(object me);
private void recoverPeng(int pExp, int pSkill, object me);

void create()
{
        set_name("���о�", ({"peng youjing", "peng", "youjing"}));
        set("title", "ؤ��Ŵ�����");
        set("nickname", "�Ʋ���ͷ");
        set("gender", "����");
        set("age", 50);
        set("long", 
                "���о���ؤ���о����ɵ����죬����Ǭ������������л��ӡ�\n"
                "�����Ϲ��Ŵ����Ц�ݣ�һ˫�۾����������ǵ�������\n");

        set("accept_special_object", 1);  // Allow this NPC call accept_special_object().
        set("attitude", "peaceful");
        set("GB_SheXin_OK", 1);
        set("rank",9);
        set("str", 28);
        set("int", 27);
        set("con", 24);
        set("dex", 25);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 70);
        set("shen_type", -1);
        
        set("combat_exp", 850000);
        set("score", 20000);
        
        set_skill("force", 170);
        set_skill("jiaohua-neigong", 170);
        set_skill("unarmed", 165);
        set_skill("changquan", 165);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 160);
        set_skill("parry", 170);
        set_skill("staff", 180);
        set_skill("fengmo-zhang", 180);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("parry", "fengmo-zhang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "fengmo-zhang");
        
        create_family("ؤ��", 18, "�Ŵ�����");
        
        set("inquiry", ([      
        "������"   : (: ask_me() :),
        "������"   : "���Ǿ����ɿɱ�����������ͷ�������ˡ�\n",
        "Ǯ"       : "Ǯ������������������������\n���о������̿�ˮ��\n",
        "����¥"   : "����һ��������ľ�¥����ϧ��Ǯ�ȽϹ�\n",
        "����"     : "���أ����������������\n",
        "����"     : "���������������������\n",
        "�ؼ�"     : "�ҵ��ؼ���������������\n",
        "��ɽ���" : "��ɽ��ᡣ�����Һ�������������\n���о���¶��ɫ��������ʲô��\n",
        "�ƽ�"     : "�ƽ𡣡���������������������\n���о������̿�ˮ��\n",
        "�����ؼ�" : "�ҵĶ����ؼ���ʵ�кܶ�ѽ��\n���о����ٺٺ١���Ц�˼�����",
        "����"     : "�ƽ𡣡���������������������\n���о������̿�ˮ��\n",
        "�¸�����" : "����������ô���ɣ������̫�¸����أ�Ҳ������˼ѧ�ɣ�\n",
        "�ȷ�ͼ��" : (: ask_mebook :),
        "ͼ��" : (: ask_mebook :),
        "�ܼ�" : (: ask_mebook :),
        "����" : (: ask_mebook :),
        "��ħ�ȷ�" : (: ask_me2 :),
        "����"   : (: ask_me2 :),
        "�����" : (: ask_me2 :),
        "����"   : (: ask_me2 :),
        ])); 
        set("book_count", 1);
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
        carry_object("/clone/weapon/tiegun")->wield(); 
}

void init()
{
  ::init();
  add_action("do_kick", "kick");
  add_action("do_kick", "kick2");
  add_action("do_kick", "kick3");
  add_action("do_kick", "kick4");
  add_action("do_kick", "kick5");
  add_action("do_kick", "slap");
  add_action("do_kick", "slap2");
  add_action("do_kick", "slap3");
  add_action("do_kick", "smash");
  add_action("do_kick", "hammer");
  add_action("do_kick", "idle");
  add_action("do_kick", "bored");
  add_action("do_kick", "grin");
  add_action("do_kick", "ugly");
  add_action("do_kick", "cut");
  add_action("do_kick", "bite");
  add_action("do_kick", "rob");
  add_action("do_kick", "slogan");
  add_action("do_kick", "sneer");
  add_action("do_kick", "consider");
}
mixed ask_me2()
{
        object me;

        me = this_player();
        if (me->query("can_perform/fengmo-zhang/qunmo"))
                return "�㲻���Ѿ������𣿴��������Ҵ�ѽ��";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "�γ����ԣ�";

        if (me->query("rank") < 6)
                return "���ڰ���ı���̫���ˣ����㵽�������Ӻ��������Ұɣ�";

        if (me->query_skill("fengmo-zhang", 1) < 150)
                return "��ķ�ħ�ȷ��������ң�Ҫ��������";

        message_vision( HIY "$n" HIY "���˵�ͷ��ͻȻһ�����ȣ�"
                        "��������һ�����裬�����������Ӱ������"
                        "���ȣ������ɵ���\n���Ƿ�ħ�ȷ��ľ�Ҫ���ڣ�\n" NOR,
                        me, this_object());
        command("haha");
        command("say �����ˣ�");
        tell_object(me, HIC "��ѧ���ˡ�Ⱥħ���衹��һ�С�\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 160000);
        me->set("can_perform/fengmo-zhang/qunmo", 1);
        return 1;
}

string ask_mebook()
{
        mapping fam; 
        object ob, me=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "ؤ��")
                return RANK_D->query_respect(this_player())+"�뱾�����ԨԴ����ô�ܿ�������Ҫ����ͼ�⣿";

        if (present("staff book", this_player()))
if (present("staff book", environment(me)))
                return "���ϲ����б�����ͼ��������ȥ���ɡ�";

        if (query("book_count") < 1)
                return "����ͼ���ѱ������ֵܽ��ߣ��´��ٸ������Űɡ�";

        add("book_count", -1);

        ob = new("/d/gaibang/obj/staff_book");
        ob->move(this_player());
        return "����ͼ�����������������ȥ�ú���ϰ�ɡ���ʲô��������ʱ�����ҵ��ˡ�";
}

void attempt_apprentice(object ob)
{
        if( ob->query("family") && ob->query("family/family_name") != "ؤ��" ) {
                command("say �㲻��ؤ����ӣ��Ϸ������㡣" + RANK_D->query_respect(ob) + "������ذɡ�");
                return;
        }

        if( ob->query("combat_exp") < 1000 ) {
                command("say ���ƺ���ûѧ��ʲô����ɡ�");
                command("say �㲻����ȥ��ݻ�����ؤ���������ѧЩ�������ٻ�ͷ�����ҡ�");
                return;
        }

        if( !ob->query("family") ) {
                command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) + "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "ؤ��һ������");
        } 

        else {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }

        return;
}

string ask_me()
{
  object who = this_player();
  int pExp;
  int pSkill;

  if( who->is_busy() ){
    return "";
  }

  if(who->query("GB_SheXin_OK")) {
    command("grin");
    command("congra " + who->query("id") );
    return "�����������绢�����ˣ���";
  }
  
  if( !who->query("GB_SheXin_PAY") && !who->query("GB_SheXin_OK") )
    who->set("GB_SheXin_PAY", 1);
    
  command("hehe " + who->query("id"));
  
  if( ! random(5) ) {
    command("say ���������ã��������ʶ��ʶʲô��������������\n");
    pExp = query("combat_exp");   
    pSkill = query_skill("huntian-qigong");
    set("combat_exp", 10000000);
    set_skill("huntian-qigong", 400);
    command("yun shexin " + who->query("id") );
    call_out("recoverPeng", 2, pExp, pSkill, who);
  }
  
  if( !random(10)) return "���������ҵĶ����ؼ��������Т����������ƽ�Ļ�����������\n";
  else return "��������������֮���񡣵����ڶ�ͥ������¥�����غ͹�����������������\n"+
              "���������������ҵĶ����ؼ�����\n";
}

private void recoverPeng(int pExp, int pSkill, object me)
{
    set("combat_exp", pExp);
    set_skill("huntian-qigong", pSkill);
    command("get gold from " + me->query("id") );
    command("hehe " + me->query("id"));
}

int accept_special_object(object me, object money)
{
  // For ��������
  
  if(!money->query("money_id")) {
    tell_object(me, CYN"���о���Ц��˵�����ٺ٣��Ҷ����û��ʲô��Ȥ����\n"NOR);
    return 0;
  }
  
  if(!me->query("GB_SheXin_PAY") && !me->query("GB_SheXin_OK")) {
    tell_object(me, CYN"���о���Ц��˵�����޶˶˵أ�������������ڣ���\n"NOR);
    return 0;
  }
  
  if(me->query("shen") > 150000) {
    tell_object(me, CYN"���о��ŵò���һ���Ӵ���ڵأ���������������⣬�⣬�⡣����\n"
    "����ô�¸����أ��޶˶˸���Ǯ���ɲ��ǿ���Ц�𣿡� \n"NOR);
    return 0;
  }
  
  if(money->query("id") != "gold") {
    tell_object(me, CYN"���о���Ц��˵�����ٺ٣�"+money->query("name")+
      NOR + CYN"�ĳ�ɫ��ô���������˼����Т���ң���\n"NOR);
    return 0;
  }
   
  if( me->query("GB_SheXin_OK")) {
    if(random(2) )
      say( CYN"���о���ͷ������Ц������" + me->query("name")+ RANK_D->query_respect(me) + 
          "�ĺô����ҽ��������������������������ˣ��Ѿ����ˡ���\n"NOR);
    else {
      say( CYN"���о���ͷ΢Ц��������л�ˣ��������ˣ��Ѿ����ˡ�\n"NOR);
      command("rich");
    }

    return 1;
  }

  if(random(2))
    command("joythank " + me->query("id"));
  else
    say(CYN"���о�����Ǯ����Ľ��ӣ���һ�飬���飬... ��... �� �ƺ����ϵ�ÿһ���ⶼ��Ц��\n"NOR);

  if(!me->query("family/family_name") || me->query("family/family_name") != "ؤ��")
    return 1;
    
  if( me->query("GB_SheXin_PAY") > 10000000 && !random(5) ) 
    say( CYN"���о���ͷ΢Ц�����������һ��ǧ�ƽ����Ⱳ�ӾͲ��ó��ˡ���\n"NOR);
  me->add("GB_SheXin_PAY", money->value());

  if( me->query("GB_SheXin_PAY") < NEED_MONEY) {
    remove_call_out("notEnough");
    call_out("notEnough", 2, me);
  }
  
  else
    call_out("enough", 2, me);
  
  return 1;
}

private void notEnough(object me)
{
  message_vision(CYN + moreMsg[random(4)] + NOR, me);
  return;
}

private void enough(object me)
{
  message_vision(CYN"���о�����һ�٣��ֶ�$N�˸߲��ҵ�˵������������ô��" + 
      HIY"Ǯ"NOR + CYN";������\n"
      "�ã��Ҿʹ������ҵĶ����ؼ�����������\n\n"NOR, me);
  call_out("teachSheXin", 1, me);
  return;
}

private void teachSheXin(object me)
{
  command("whisper " + me->query("id") + " ��Ҫ�����ˣ������㡣����");
  tell_object( me, "\n��ѧ����������������\n"NOR);
  me->delete("GB_SheXin_PAY");
  me->set("GB_SheXin_OK", 1);
  return;
}

int do_kick(string arg)
{
  if (!arg || (arg != "peng youjing" && arg != "peng" && arg != "youjing") )
    return 0;

  call_out("pengsResponse", 1, this_player() );
  return 0;
}

private void pengsResponse(object me)
{
  int pExp, pSkill;
  
  command( Pengemote[random(PENG_EMOTE)] + me->query("id") );

  if(!random(6)) {
    pExp = query("combat_exp");   
    pSkill = query_skill("huntian-qigong");
    set("combat_exp", 10000000);
    set_skill("huntian-qigong", 400);
    command("yun shexin " + me->query("id") );
    call_out("recoverPeng", 2, pExp, pSkill, me);
  }
  return;
}

#include "/kungfu/class/gaibang/promote.h"