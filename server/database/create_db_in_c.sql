PRAGMA FOREIGN_KEYS = ON;

create table if not exists group_g(
   gg_id integer not null primary key AUTOINCREMENT,
   gg_name varchar(50),
   gg_color integer 
);

insert OR IGNORE into group_g values(1, 'Admin', 0);
insert OR IGNORE into group_g values(2, 'User', 0);

create table if not exists user(
    usr_id integer not null primary key AUTOINCREMENT, 
    usr_frst_name varchar(50),
    usr_scnd_name varchar(50),
    usr_nickname varchar(100) UNIQUE,
    usr_pass varchar(64), -- hased pass --
    usr_group integer,
    user_avatar varchar(1) DEFAULT '0',
    foreign key(usr_group) references group_g(gg_id)
);

insert OR IGNORE into user values(1, 'Admin_name1','admin', 'Admin', '1234', 1, 1);
insert OR IGNORE into user values(2, 'Admin_name2','admin', 'Admin1', '1234', 1, 1);
insert OR IGNORE into user values(3, 'Admin_name3','admin', 'Admin2', '1234', 1, 1);
insert OR IGNORE into user values(4, 'Admin_name4','admin', 'Admin3', '1234', 1, 1);
insert OR IGNORE into user values(5, 'Admin_name5','admin', 'Admin4', '1234', 1, 1);

create table if not exists chat(
    chat_id integer not null primary key AUTOINCREMENT,
    chat_name varchar(100),
    chat_type varchar(1) DEFAULT '2',
    chat_id_creater integer,
    chat_id_user_dialog integer DEFAULT '0',
    chat_time_creation datetime
);

insert OR IGNORE into chat values(1, 'General', '2', '1' , '0', datetime('now'));
insert OR IGNORE into chat values(2, 'test_room', '2', '1', '0', datetime('now'));

create table if not exists msg(
    msg_id integer not null primary key AUTOINCREMENT,
    msg_creator integer,
    msg_send_time datetime,
    msg_data blob,
    msg_chat_id integer,
    msg_status varchar(1) DEFAULT '2',
    msg_avatar VARCHAR(1) DEFAULT '2',
    msg_file_type INTEGER DEFAULT 1,
    msg_file_name VARCHAR(51),
    msg_file_size INTEGER DEFAULT 0,
    foreign key(msg_creator) references user(usr_id),
    foreign key(msg_chat_id) references chat(chat_id)
);

INSERT OR IGNORE INTO msg (msg_id, msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (1, 1, datetime('now'), "TEST message!", 1, "PIC.png");
INSERT OR IGNORE INTO msg (msg_id, msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (2, 1, datetime('now'), "TEST1 message!", 1, "PIC1.png");

INSERT OR IGNORE INTO msg (msg_id, msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (3, 1, datetime('now'), "TEST2 message!", 1, "PIC2.png");
INSERT OR IGNORE INTO msg (msg_id, msg_creator, msg_send_time, msg_data, msg_chat_id, msg_file_name) VALUES (4, 2, datetime('now'), "TEST3 message!", 1, "PIC3.png");

create table if not exists group_l(
   gl_id integer not null primary key AUTOINCREMENT,
   gl_name varchar(50),
   gl_color integer,
   gl_owner integer,
   foreign key (gl_owner) references user(usr_id)
);

create table  if not exists cm(
   cm_id integer not null primary key AUTOINCREMENT,
   cm_chat_id integer,
   cm_msg_id integer,
   foreign key (cm_chat_id) references chat(chat_id),
   foreign key (cm_msg_id) references msg(msg_id)
);

create table if not exists gou(
    gou_id integer not null primary key AUTOINCREMENT,
    gou_group_id integer,
    gou_user_id integer,
    foreign key (gou_group_id) references group_l(gl_id),
    foreign key (gou_user_id) references user(usr_id)
);
create table if not exists  cou(
   cou_id integer not null primary key AUTOINCREMENT,
   cou_chat_id integer,
   cou_usr_id integer,
   cou_premission smallint, -- 0 - user, 1 - admin
   foreign key (cou_chat_id) references chat(chat_id),
   foreign key (cou_usr_id) references user(usr_id)
);

CREATE TRIGGER if not exists add_default_chat AFTER insert
ON user
BEGIN
insert into cou values(NULL, 1,NEW.usr_id, 0);
END;

CREATE TRIGGER if not exists add_chat_user_dialog AFTER insert
ON chat
WHEN NEW.chat_id_user_dialog > 0
BEGIN 
insert into cou values(NULL, NEW.chat_id, NEW.chat_id_user_dialog, '1');
END;

CREATE TRIGGER if not exists add_chat_creater AFTER insert
ON chat
BEGIN
insert into cou values(NULL, NEW.chat_id, NEW.chat_id_creater, '1');
END;

insert OR IGNORE into cou values(1, 1, 1, 1);
insert OR IGNORE into cou values(2, 2, 1, 1);

create table if not exists pd(
   pd_id integer not null primary key AUTOINCREMENT,
   pd_user_id integer,
   pd_pid integer,
   pd_add_time datetime
);
