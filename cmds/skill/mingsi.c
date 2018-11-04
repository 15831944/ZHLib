// mingsi.c
#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void finish(object me, int pot_gain);
int main(object me, string arg)
{

int busy_time, pot_gain;
int mingsi_lvl;
mapping fam;
object where;
mingsi_lvl = me->query("con");

seteuid(getuid());

where = environment(me);
if(where->query("no_fight") || where->query("no_flee") )
return notify_fail("��ȫ���ڽ�ֹ������\n");
if (!me->query("special_skill/lonely",1))
return notify_fail("�㲻����ɷ���ǲ���ʹ��������\n");

if (me->is_busy() || me->query_temp("pending/exercising")
     || me->query_temp("doing_mingsi"))
    return notify_fail("��������æ���ء�\n");

if( me->is_fighting() )
  return notify_fail("ս����ڤ˼������������\n");

if( (int)me->query("jing") * 100 / (int)me->query("max_jing") < 50 )
  return notify_fail("���������ǲ��壬��������Ҫ�߻���ħ��\n");

if( (int)me->query("qi") * 100 / (int)me->query("max_qi") < 50 )
   return notify_fail("����������������������Ҫ�����ˣ�\n");

pot_gain = mingsi_lvl/20 + random(5);

busy_time = random(120)/pot_gain/10+20;

pot_gain = 1 + random(pot_gain*2);

busy_time *= pot_gain;

pot_gain += (int)me->query("con")*pot_gain/2/busy_time;

message_vision(HIY "$N�����۾�����ϥ���£�����ĬĬ���֪��˵Щʲô��\n" NOR, me);
me->start_busy(busy_time+15);

me->set_temp("doing_mingsi",1);

call_out("finish",busy_time, me, pot_gain);
return 1;
}

void finish(object me, int pot_gain)

{

if(!me) return;

me->delete_temp("doing_mingsi");

message_vision(HIY "$N���������۾�������һ����վ��������\n" NOR, me);

tell_object(me, HIC "���Ǳ�ܡ������������"HIR+"һ�ٵ�"+HIC",���������"HIR+"��ʮ��"+HIC"��\n" NOR);

me->add("combat_exp", 100);
me->add("potential", 100);
me->add("experience", 50);
me->set("jing",me->query("con"));
me->set("qi",me->query("con"));
me->set("neili",me->query("neili")/2);

if (me->query("food") >= pot_gain) me->add("food",-pot_gain);
else me->set("food", 0);

if (me->query("water") >= pot_gain) me->add("water",-pot_gain);
else me->set("water", 0);
me->receive_damage("jing", me->query("con"));
me->receive_damage("qi", me->query("con"));
}
/*

int help(object me)
{
       write(@HELP
ָ���ʽ : mingsi

 ��ɷ�����������Ǳ�ܵ����
  HELP
);
    return 1;
}
*/
