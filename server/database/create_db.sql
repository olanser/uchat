.mode column
.headers on

PRAGMA FOREIGN_KEYS = ON;

drop table IF EXISTS user;
drop table IF EXISTS group_g;
drop table IF EXISTS chat;
drop table IF EXISTS msg;
drop table IF EXISTS group_l;
drop table IF EXISTS cm;
drop table IF EXISTS gou;
drop table IF EXISTS cou;

-- group_g
.print "----------------------------------------------------------------------"
.print "----------------------------------------------------------------------\n"
.print "1. -- CREATING group_g --\n"
create table group_g(
   gg_id integer not null primary key AUTOINCREMENT,
   gg_name varchar(50),
   gg_color integer 
);
--pragma table_info('group_g');
insert into group_g values(NULL, 'Admin', 0);
insert into group_g values(NULL, 'User', 0);
select * from group_g;

-- user

.print "\n2. -- CREATING user --\n"
create table user(
    usr_id integer not null primary key AUTOINCREMENT, 
    usr_frst_name varchar(50),
    usr_scnd_name varchar(50),
    usr_nickname varchar(100) UNIQUE,
    usr_pass varchar(64), -- hased pass --
    usr_group integer,
    foreign key(usr_group) references group_g(gg_id)
);
--pragma table_info('user');
insert into user values(NULL, 'Admin','admin', 'Admin', '1234', 1);
insert into user values(NULL, 'Admin','admin', 'Admin1', '1234', 1);
insert into user values(NULL, 'Admin','admin', 'Admin2', '1234', 1);
insert into user values(NULL, 'Admin','admin', 'Admin3', '1234', 1);
insert into user values(NULL, 'Admin','admin', 'Admin4', '1234', 1);
select * from user;

-- chat
.print "\n3. -- CREATING chat --\n"
create table chat(
    chat_id integer not null primary key AUTOINCREMENT,
    chat_name varchar(100),
    chat_type varchar(1) DEFAULT '2',
    chat_id_creater integer,
    chat_id_user_dialog integer DEFAULT '0',
    chat_time_creation datetime
);

--pragma table_info('chat');
insert into chat values(NULL, 'General', '2', '1' , '0', datetime('now'));
insert into chat values(NULL, 'test_room', '1', '1', '3', datetime('now'));
select * from chat;

-- message
.print "\n4. -- CREATING message --\n"
create table msg(
    msg_id integer not null primary key AUTOINCREMENT,
    msg_creator integer,
    msg_send_time datetime,
    msg_data blob,
    msg_chat_id integer,
    msg_status varchar(1) DEFAULT '2',
    msg_status_see VARCHAR(1) DEFAULT '0',
    msg_file_type INTEGER DEFAULT 0,
    msg_file_name VARCHAR(51),
    msg_file_size INTEGER DEFAULT 0,
    foreign key(msg_creator) references user(usr_id),
    foreign key(msg_chat_id) references chat(chat_id)
);
INSERT INTO msg (msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (1, datetime('now'), "TEST message!", 1, "PIC.png");
INSERT INTO msg (msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (1, datetime('now'), "TEST1 message!", 1, "PIC1.png");

INSERT INTO msg (msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (1, datetime('now'), "TEST2 message!", 1, "PIC2.png");
INSERT INTO msg (msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (2, datetime('now'), "TEST3 message!", 1, "PIC3.png");


select * from msg;
--pragma table_info('msg');

-- group_l

.print "\n5. -- CREATING group_l --\n"
create table group_l(
   gl_id integer not null primary key AUTOINCREMENT,
   gl_name varchar(50),
   gl_color integer,
   gl_owner integer,
   foreign key (gl_owner) references user(usr_id)
);
select * from group_l;
--pragma table_info('group_l');

-- chat_msg
.print "\n6. -- CREATING chat_msg[cm] --\n"

create table cm(
   cm_id integer not null primary key AUTOINCREMENT,
   cm_chat_id integer,
   cm_msg_id integer,
   foreign key (cm_chat_id) references chat(chat_id),
   foreign key (cm_msg_id) references msg(msg_id)
);
select * from cm;
--pragma table_info('cm');

-- groups of user
.print "\n7. -- CREATING local groups of user[gou] --\n"
create table gou(
    gou_id integer not null primary key AUTOINCREMENT,
    gou_group_id integer,
    gou_user_id integer,
    foreign key (gou_group_id) references group_l(gl_id),
    foreign key (gou_user_id) references user(usr_id)
);
select * from gou;
--pragma table_info('gou');
.print "\n8. -- CREATING TRIGGER add_default_chat --\n"

-- group_l
.print "\n9. -- CREATING Chat_of_users[cou] --\n"
create table cou(
   cou_id integer not null primary key AUTOINCREMENT,
   cou_char_id integer,
   cou_usr_id integer,
   cou_premission smallint, -- 0 - user, 1 - admin
   foreign key (cou_char_id) references chat(chat_id),
   foreign key (cou_usr_id) references user(usr_id)
);

CREATE TRIGGER add_default_chat AFTER insert
ON user
BEGIN
insert into cou values(NULL, 1,NEW.usr_id, 0);
END;

CREATE TRIGGER add_chat_user_dialog AFTER insert
ON chat
WHEN NEW.chat_id_user_dialog > 0
BEGIN 
insert into cou values(NULL, NEW.chat_id, NEW.chat_id_user_dialog, '1');
END;

CREATE TRIGGER add_chat_creater AFTER insert
ON chat
BEGIN
insert into cou values(NULL, NEW.chat_id, NEW.chat_id_creater, '1');
END;

insert into cou values(NULL, 1, 1, 1);
    select cou.*, user.usr_frst_name
    from cou
    LEFT JOIN user
    ON cou.cou_usr_id == user.usr_id;
--pragma table_info('cou');

-- process data
.print "\n9. -- CREATING process_data[cou] --\n"
create table pd(
   pd_id integer not null primary key AUTOINCREMENT,
   pd_user_id integer,
   pd_pid integer,
   pd_add_time datetime
);
