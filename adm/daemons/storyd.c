// storyd.c

#include <ansi.h>

inherit F_DBASE;

static string *story_name = ({
#if 1

        "master",
        "huanyin",
        "sanfenjian",
        "bizhen",
        "anthem",
        "baguadao",
        "shenzhao",
        "laojun",
        "zagang",
        "guanzhang",
        "lighting",
        "beihai",
        "hyshan",
        "qishangquan",

#endif
        "challenge",
});

static object  running_story;
static mapping history;
static int step;
int filter_listener(object ob);

void ready_to_start()
{
        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("start_story", 7200 + random(3600));
}

void go_on_process(object ob)
{
        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("process_story", 1, ob);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���¾���");
        CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������");

        history = allocate_mapping(sizeof(story_name));
        ready_to_start();
}

int clean_up()
{
        return 1;
}

object query_running_story()
{
        return running_story;
}

void start_story()
{
        string *all_story;
        string name;
        object ob;

        ready_to_start();
        CHANNEL_D->do_channel(this_object(), "sys", "����ϵͳ��ʼѡ����¡�");

        all_story = filter_array(story_name, (: $1 == "challenge" ||
                                                time() - (int)history[$1] > 14400 :));
        while (sizeof(all_story))
        {
                name = all_story[random(sizeof(all_story))];
                if (undefinedp(history[name]))
                        history += ([ name : 0 ]);
                else
                        history[name] = (int)time();

                CHANNEL_D->do_channel(this_object(), "sys",
                                      "����ϵͳѡ���˹���(" + name + ")��");
 
                all_story -= ({ name });
                name = STORY_DIR + name;
                if (ob = find_object(name))
                        destruct(ob);
        
                catch(ob = load_object(name));
                running_story = ob;
        
                if (objectp(ob))
                {
                        step = 0;
                        go_on_process(ob);
                        break;
                }
        }
}

void remove_story(string story)
{
        story_name -= ({ story });
}

string *query_all_story()
{
        return story_name;
}

void process_story(object ob)
{
        mixed line;
        object *listeners;
        string prompt;

        go_on_process(ob);

        if (! objectp(ob))
        {
                ready_to_start();
                return;
        }

        line = ob->query_story_message(step);
        step++;

        prompt = ob->prompt();
        if (! prompt) prompt = HIG "�����´��š�" NOR;
        if (functionp(line)) catch(line = evaluate(line));
        if (stringp(line))
        {
                listeners = filter_array(users(), (: filter_listener :));
                message( "story",  prompt + WHT + line + "\n" NOR, listeners );
        }

        if (intp(line) && ! line)
        {
                ready_to_start();
                destruct(ob);
        }
}

int filter_listener(object ob)
{
        if (ob->query("env/no_story")) return 0;
        return 1;
}

void give_gift(string gift, int amount, string msg)
{
        int i;
        object ob;
        object env;
        object *players;

        players = users();
        if (sizeof(players) >= 5)
        {
                for (i = 0; i < 12; i++)
                {
                        ob = players[random(sizeof(players))];
                        if (wizardp(ob) || ! ob->query("born") ||
                            ! living(ob) || ! environment(ob) ||
                            environment(ob)->is_chat_room())
                        {
                                continue;
                        }
                                
                        env = environment(ob);
                        while (env && env->is_character())
                                env = environment(env);
                        if (env) break;
                }
                if (i >= 12) return;

                if (objectp(env))
                        tell_room(env, msg);
                for (i = 0; i < amount; i++)
                {
                        ob = new(gift);
                        ob->move(env);
                }
                CHANNEL_D->do_channel( this_object(),
                        "sys", sprintf(NOR WHT "��Ʒ%s" NOR WHT "������"
                                HIC "%s" NOR WHT "(%O" NOR WHT ")��" NOR,
                                ob->name(), env->short(), env));
        }
}

