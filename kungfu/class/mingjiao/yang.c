// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yang.c 杨逍

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

string ask_me();
string dagger();

void create()
{
        set_name("杨逍",({"yang xiao","yang","xiao"}));
	set("title",HIG "明教" HIR "逍遥二仙" NOR);
        set("long", "他就是明教的光明左使，和范遥合称逍遥二仙的杨逍。\n"+
                    "他身着一身白衫，虽然已是中年，但看上去还十分英俊潇洒。\n");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen", -15000);
        set("str", 26);
        set("per", 29);
        set("int", 29);
        set("con", 27);
        set("dex", 30);         
        set("max_qi",4000);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 80);
        set("combat_exp", 1600000);
        set("level", 40);
        set("no_get",1);
        set("no_quest", 1);
        set("dagger-book", 1);
        set("ling-book", 1);
        
        set_skill("sword",280); 
        set_skill("blade",280);
        set_skill("literate",250);
        set_skill("claw", 280);
        set_skill("strike", 280);
        set_skill("hanbing-mianzhang", 280);
        set_skill("yingzhua-shou", 280);
        set_skill("dodge",280);
        set_skill("force", 280);
        set_skill("qingfu-shenfa", 280);
        set_skill("lieyan-dao",280);
        set_skill("liehuo-jian",280);
        set_skill("shenghuo-shengong", 280);
        set_skill("parry", 280); 
        set_skill("martial-cognize", 200);      
        
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "lieyan-dao");
        map_skill("claw", "yingzhua-shou");
        map_skill("strike", "hanbing-mianzhang");

        prepare_skill("strike", "hanbing-mianzhang");
        prepare_skill("claw", "yingzhua-shou");
        
        create_family("明教", 35, "光明左使");

        set("inquiry", ([
                "匕法概论" : (: dagger :),
                "book" : (: dagger :),
                "铁焰令" : (: ask_me :),
                "霹雳雷火弹":"听说西域有人从中国学得造火药之法，制出一种暗器。\n"
                        "叫作‘霹雳雷火弹’，中藏烈性火药，以强力弹簧机括发射。\n",
        ]));

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: command("perform strike.jue") :),
                (: command("perform strike.xi") :),                
                (: command("perform claw.xue") :),             
        }));
        
        set("master_ob",4);
	setup(); 
        if (random(10) > 5)
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
}


void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 10000)
        {
                command("say 你行侠仗义的事做得还不够，还是请回吧。");
                return;
        }
                
        if (! fam || fam["family_name"] != "明教")
        {
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 120) 
        {
                command("say 要学更为高深的武功，必须有高深的内功修为。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
        }
        if ((int)ob->query_int() < 30) 
        {
                command("say 逍遥二仙的武功博而杂，要学会这些武功，非得有极高的悟性。");
                command("say 在悟性方面，"+RANK_D->query_respect(ob)+"是否还不够？");
                return;
        }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", this_object()->query("title")+"座下弟子");
}
 
void init()
{
        object me, ob;
        mapping fam;
        
        ::init();
        ob = this_player();
        me = this_object();  
              
        if (interactive(ob) && ! wizardp(ob)
           && base_name(environment(me))=="/d/mingjiao/longwang"
           && ((fam = ob->query("family")) && fam["family_name"] != "明教" ))
        {
                command("say 这里是明教的重地，别说是外人，就是明教中人也不能随意进出，赶快离开此地！");
                command("consider " + ob->query("id"));  
                remove_call_out("kill_ob");
                call_out("kill_ob", 5, ob); 
        }
        
        if (interactive(ob) && ob->query_temp("mj_jiaozhu"))           
                command("nod " + ob->query("id"));   
        else 
                command("hehe " + ob->query("id"));      
}

string dagger()
{
        mapping fam = this_player()->query("family");
        object ob; 
               
        if (! fam || fam["family_name"] != "明教")
                return RANK_D->query_respect(this_player())+"与本教素无来往，不知此话从何谈起？";
                
        if (this_player()->query_skill("dagger", 1) > 101)
                return "你的匕法已经有一定基础了，这本书对你没什么用，还是留给别人吧";    
                    
        if (this_player()->query_skill("shenghuo-shengong", 1) < 100)
                return "你在明教的时日尚短，过段时日再来吧。";
     
        if (this_object()->query("dagger-book") < 1)
                return "你来晚了，我的「匕法概论」已经给别人拿走了。";     
                         
        ob = new("/clone/book/dagger-book");
        ob->move(this_player());
        
        this_object()->add("dagger_book", -1);
        
        return "好吧，教主放在我这的「匕法概论」就送给你了。";
}

string ask_me()
{ 
        mapping fam; 
        object ob, *clone;
        int i, j;

        if (! (fam = this_player()->query("family")) || fam["family_name"] != "明教")
                return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
                
        if (this_player()->query_skill("shenghuo-shengong", 1) < 100)
                return "你在明教的时日尚短，没有权利使用铁焰令。";
                
        if (! this_player()->query_skill("shenghuo-ling"))
                return "你又不使用令法，拿铁焰令干什么？";
                
        ob = present("tieyan ling", this_player());
        if (ob && ob->query_amount() >= 2)
                return "你身上都已经这么多了，还要令干什么？";
                
        if (this_object()->query("ling_book") < 1)       
                return "你来晚了，铁焰令已给全部发出去了。"; 

        ob = new("/d/mingjiao/obj/tieyan-ling");        
        ob->move(this_player());
        
        this_object()->add("ling_book", -1);
        
        return "好吧，这块铁焰令你就拿去吧，望你不要借它为恶，多多发展我明教教众。";
}

void reset()
{
        set("ling-book", 1);
        set("dagger-book", 1);
}
