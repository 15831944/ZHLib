#include <ansi.h>
inherit F_CLEAN_UP;
string get_job(string arg);
mapping wizhood=([
//"(root)":       HIY" ������ "HIB,   
        "(admin)":      HIY"�� ������ ��"HIB,
        "(arch)":       HIG"�� ��  �� ��"HIB,
        "(wizard)":     HIY"�� ��  ʦ ��"HIB,
        "(apprentice)": HIC"�� ѧ  ͽ ��"HIB,
        "(immortal)":   HIB"�� ��  �� ��"HIB,
        "(elder)":      HIM"��������ҡ�"HIB,
]);
mapping wizlevel=([
        //0:      "(root)",
        1:      "(admin)",
        2:      "(arch)",
        3:      "(wizard)",
        4:      "(apprentice)",
        5:      "(immortal)",
        6:      "(elder)",
]);
int main(object me, string arg)
{
        string *list, ch,job;
        int my_level,b, i, j, number,a,mark,lev;
        object ob;
        number = 0;
        job="";
        list = sort_array(SECURITY_D->query_wizlist(), 1);
        write(HIR"��"+HIY+""+MUD_NAME +""HIR"��"HIG"��ʦ�б�:\n"NOR);
        write(HIR"��"HIW"��"HIB"������������������������������������������������������������"HIW"��"HIR"��\n"NOR);
        write(HIB"  ��"HIW" ��  �� "HIB"��  ��"HIW"��ʦID"HIB"��  ��"HIW"״̬"HIB"��     ��"HIW"��������"HIB"��\n"NOR);
        write(HIR"��"HIW"��"HIB"������������������������������������������������������������"HIW"��"HIR"��\n"NOR);
        my_level=wiz_level(me);
if (wizardp(me)) {
lev=7;
}
else{
lev=5;
}
        for (b=0;b<lev;b++)
        {
        mark=0;
        for(i=0, j=0; i<sizeof(list); i++)
        if(SECURITY_D->get_status(list[i])==wizlevel[b]) mark=1;
        if(mark){
        printf(HIB"\n  "+wizhood[wizlevel[b]]+"  "+NOR);
        for(i=0, j=0; i<sizeof(list); i++)
        if(SECURITY_D->get_status(list[i])==wizlevel[b])
        {
                ch = HIR"  ����"NOR;
                a = 0;
                job=get_job(list[i]);
                if(!job) job="�л��ܼ�";
                if(ob=find_player(list[i])&&!find_player(list[i])->query("env/invisibility"))
                {
                ch = HIG"  ����"NOR ;
                a = 1;
                number = number + 1;
                 }
             else if (ob = find_player(list[i]) && wizardp(me) && find_player(list[i])->query("env/invisibility") )
              {
                    ch = HIB"  ����"NOR;
                  a = 1;
                     number = number + 1;
                 }
           if( list[i]=="xhuarong" ) {}
         else printf(HIY"  %-10s"" %s    "HIW"    %s\n                ",list[i],ch,job," " ? "\n " : " ");
        }
        }
        }
        write(HIR"\n��"HIW"��"HIB"������������������������������������������������������������"HIW"��"HIR"��\n"NOR);
                if (wizardp(me)) {
      printf(HIR"��"+HIY+MUD_NAME+HIG"Ŀǰ����:"BLINK HIR"%s"NOR HIG"����ʦ��\n"NOR,chinese_number(sizeof(list)) );
                }
        printf(HIR"��"+HIY+MUD_NAME+HIG"Ŀǰ����:"BLINK HIR"%s"NOR HIG"λ��ʦ������"NOR,chinese_number(number));
        write("\n");
        return 1;
}
string get_job(string arg)
{
        string str;
        switch(arg)
   {
          case "dvunix":   {str=HIM"�龰�߻�"NOR;break;}

            }
        return str;
}
int help(object me)
{
  write(@HELP
ָ���ʽ��wizlist
ָ��˵����
           ��ָ�������鿴Ŀǰ�ܹ��ж��ٸ���ʦ��
HELP
    );
    return 1;
}
