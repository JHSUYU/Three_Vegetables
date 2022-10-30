-- create table bb (id int, name char);
-- insert into bb values(1, 'czy');
-- insert into bb values(2, 'lzy');
-- insert into aa values(3, 'hsy');
-- insert into aa values(4, 'cxt');
-- insert into aa values(11, 'cxt'), (22, 'cxk'), (33, 'hhh');
-- select * from aa where name = '__y';
-- select * from aa where name like 'czy' and not like 'hsy';

-- create table hhh (id int, age int);
-- insert into aa values(11, 'cxt'), (22, 'cxk'), (33, 'hhh');
-- insert into hhh values(1111, 1111), (2222, 2222), (3333, 3333);
create table dd(id int, id2 int nullable);
insert into dd values(1, null);
-- bison -vdy yacc_sql.y
-- flex lex_sql.l
-- ./build/bin/observer -f ./etc/observer.ini
-- ./build/bin/obclient